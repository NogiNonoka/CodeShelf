/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/GraphTheory/TwoSAT_Tarjan.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  2-SAT (2-Satisfiability)
 *  Tarjan SCC based
 *  Time Complexity: O(N+M)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e6 + 7;

struct TwoSAT {
    struct Edge { int to, nxt; } edge[MAXN];
    int head[MAXN], cntEdge;
    int dfn[MAXN], low[MAXN], stk[MAXN], top, idx;
    bool inStk[MAXN];
    int scc[MAXN], sccCnt;
    int n;

    void init(int _n) {
        n = _n;
        cntEdge = -1; idx = 0; top = 0; sccCnt = 0;
        for (int i = 0; i <= 2 * n; ++i) {
            head[i] = -1;
            dfn[i] = low[i] = scc[i] = 0;
            inStk[i] = false;
        }
    }

    void addEdge(int u, int v) {
        edge[++cntEdge] = {v, head[u]};
        head[u] = cntEdge;
    }

    // x = val: node id = x * 2 + val
    void addImplication(int x, int vx, int y, int vy) {
        addEdge(x * 2 + vx, y * 2 + vy);
    }

    void addOr(int x, int vx, int y, int vy) {
        // (x=vx) OR (y=vy)
        addImplication(x, vx ^ 1, y, vy);
        addImplication(y, vy ^ 1, x, vx);
    }

    void addXor(int x, int y) {
        addOr(x, 0, y, 0);
        addOr(x, 1, y, 1);
    }

    void addEqual(int x, int y) {
        addOr(x, 0, y, 1);
        addOr(x, 1, y, 0);
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++idx;
        stk[++top] = u; inStk[u] = true;
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            int v = edge[i].to;
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (inStk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            ++sccCnt;
            while (true) {
                int x = stk[top--];
                inStk[x] = false;
                scc[x] = sccCnt;
                if (x == u) break;
            }
        }
    }

    bool satisfiable() {
        for (int i = 0; i < 2 * n; ++i)
            if (!dfn[i]) tarjan(i);
        for (int i = 0; i < n; ++i)
            if (scc[i * 2] == scc[i * 2 + 1]) return false;
        return true;
    }

    vector<int> getAssignment() {
        vector<int> ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = scc[i * 2] > scc[i * 2 + 1] ? 0 : 1;
        return ans;
    }
} tsat;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    tsat.init(n);
    while (m--) {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        --i; --j;
        tsat.addOr(i, a, j, b);
    }
    if (!tsat.satisfiable()) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << "POSSIBLE\n";
        auto ans = tsat.getAssignment();
        for (int i = 0; i < n; ++i) cout << ans[i] << " \n"[i + 1 == n];
    }
    return 0;
}
