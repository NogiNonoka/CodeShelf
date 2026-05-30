/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/GraphTheory/VirtualTree.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Virtual Tree
 *  Compress k key nodes on a tree using LCA
 *  Time Complexity: O(k log k)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 7;
const int LOG = 20;

struct VirtualTree {
    int n, root;
    vector<int> adj[MAXN];
    int dep[MAXN], fa[MAXN][LOG + 1];
    int dfn[MAXN], tim;

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int f) {
        dfn[u] = ++tim;
        dep[u] = dep[f] + 1;
        fa[u][0] = f;
        for (int i = 1; i <= LOG; ++i)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (int v : adj[u]) {
            if (v == f) continue;
            dfs(v, u);
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = LOG; i >= 0; --i)
            if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        if (u == v) return u;
        for (int i = LOG; i >= 0; --i)
            if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }

    int stk[MAXN], top;
    vector<pair<int, int>> vt[MAXN]; // virtual tree edges
    int key[MAXN], m;

    void buildVT() {
        sort(key + 1, key + 1 + m, [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        static int tmp[MAXN];
        int sz = m;
        for (int i = 1; i < m; ++i) tmp[++sz] = lca(key[i], key[i + 1]);
        sort(tmp + 1, tmp + 1 + sz, [&](int a, int b) {
            return dfn[a] < dfn[b];
        });
        sz = unique(tmp + 1, tmp + 1 + sz) - tmp - 1;
        for (int i = 1; i <= sz; ++i) vt[tmp[i]].clear();
        top = 0;
        stk[++top] = tmp[1];
        for (int i = 2; i <= sz; ++i) {
            int u = tmp[i];
            while (top > 1 && dep[lca(stk[top], u)] < dep[stk[top]]) --top;
            vt[stk[top]].push_back({u, dep[u] - dep[stk[top]]});
            stk[++top] = u;
        }
    }

    void init(int _n, int _root) {
        n = _n; root = _root;
        tim = 0;
        dfs(root, 0);
    }
} vt;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        vt.addEdge(u, v);
    }
    vt.init(n, 1);
    int q;
    cin >> q;
    while (q--) {
        cin >> vt.m;
        for (int i = 1; i <= vt.m; ++i) cin >> vt.key[i];
        vt.buildVT();
        // run DP on vt.vt[...]
    }
    return 0;
}
