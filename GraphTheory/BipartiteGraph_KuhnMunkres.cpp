/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-23 14:00:31
 * @FilePath            : /CodeShelf/GraphTheory/BipartiteGraph_KuhnMunkres.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Bitpartite Graph (Perfect Matching's Maximum Matching)
 *  Time Complexity: O(V^3)
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e3 + 7;
// const int MAXE = ;
// const int MOD = ;
const int INF = 0x3f3f3f3f3f3f3f3f;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct KuhnMunkres {
    // Bitpartite Graph (Perfect Matching's Maximum Matching)
    // add 0 weight Edge for Perfect Matching exsist
    // add -w weight Edge for Minimum Matching
    // add log(w) weight for Multiple Maximum Matching
    // Time Complexity: O(V^3)
    // index from 0 to n - 1
    // add Edge (u - 1, v - 1, w)
    int n;
    int cntx;
    int cnty;
    int pre[MAXN]; // 连接右集合的左点
    bool visx[MAXN];
    bool visy[MAXN];
    int lx[MAXN];
    int ly[MAXN];
    int g[MAXN][MAXN];
    int slack[MAXN];
    int matchx[MAXN];
    int matchy[MAXN];
    queue<int> q;
    int res;

    void init(int cntx, int cnty) {
        this->cntx = cntx;
        this->cnty = cnty;
        n = max(cntx, cnty);
        res = 0;
        for (int i = 0; i < n; ++i) fill(g[i], g[i] + n, -INF);
        memset(matchx, -1, sizeof(int) * n);
        memset(matchy, -1, sizeof(int) * n);
        fill(lx, lx + n, -INF);
    }

    void addEdge(int u, int v, int w) {
        // g[u][v] = max(0, w); // 负值还不如不匹配 因此设为 0不影响
        g[u][v] = max(g[u][v], w); // 考虑重边
    }

    bool check(int v) {
        visy[v] = true;
        if (matchy[v] != -1) {
            q.push(matchy[v]);
            visx[matchy[v]] = true; // in S
            return false;
        }
        // 找到新的未匹配点 更新匹配点 pre 数组记录着"非匹配边"上与之相连的点
        while (v != -1) {
            matchy[v] = pre[v];
            swap(v, matchx[pre[v]]);
        }
        return true;
    }

    void bfs(int i) {
        while (!q.empty()) q.pop();
        q.push(i);
        visx[i] = true;
        while (true) {
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; v++) {
                    if (!visy[v]) {
                        int delta = lx[u] + ly[v] - g[u][v];
                        if (slack[v] >= delta) {
                            pre[v] = u;
                            if (delta)
                                slack[v] = delta;
                            else if (check(v))
                                // delta=0 代表有机会加入相等子图 找增广路
                                // 找到就 return 重建交错树
                                return;
                        }
                    }
                }
            }
            // 没有增广路 修改顶标
            int a = INF;
            for (int j = 0; j < n; j++)
                if (!visy[j]) a = min(a, slack[j]);
            for (int j = 0; j < n; j++) {
                if (visx[j]) // S
                    lx[j] -= a;
                if (visy[j]) // T
                    ly[j] += a;
                else // T'
                    slack[j] -= a;
            }
            for (int j = 0; j < n; j++)
                if (!visy[j] && slack[j] == 0 && check(j)) return;
        }
    }

    void solve() {
        // 初始顶标
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) lx[i] = max(lx[i], g[i][j]);
        for (int i = 0; i < n; i++) {
            memset(slack, 0x3f, sizeof(int) * n);
            memset(visx, false, sizeof(bool) * n);
            memset(visy, false, sizeof(bool) * n);
            bfs(i);
        }
        for (int i = 0; i < n; i++) {
            // if add extra Edge
            // if (g[i][matchx[i]] > 0)
            // res += g[i][matchx[i]];
            // else
            // matchx[i] = -1;
            res += g[i][matchx[i]];
        }
        cout << res << "\n";
        for (int i = 0; i < cnty; i++) cout << matchy[i] + 1 << " ";
        cout << "\n";
    }
} km;

signed main(void) {
    // Problem ID: P6577
    // Link: https://www.luogu.com.cn/problem/P6577
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    km.init(n, n);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        km.addEdge(u - 1, v - 1, w);
    }
    km.solve();
    return 0;
}