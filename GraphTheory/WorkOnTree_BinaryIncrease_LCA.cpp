/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-12 11:49:52
 * @FilePath            : \CodeShelf\GraphTheory\WorkOnTree_BinaryIncrease_LCA.cpp
 * @LastEditTime        : 2021-03-12 12:50:47
 * @Forward Declaration : None
 * @Discription         : 
 *  Least Common Ancestor (Binary Increase)
 *  Time Complexity: O(NlogN)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
#define endl "\n"
const int MAXN = 5e5 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct LCA
{
    struct Edge
    {
        int to;
        int nxt;
    } edge[MAXN * 2];

    int cntEdge, head[MAXN];

    int dep[MAXN];
    int fa[MAXN][33];

    void init()
    {
        cntEdge = -1;
        memset(head, -1, sizeof(head));
        dep[0] = 0;
    }

    void addEdge(int u, int v)
    {
        ++cntEdge;
        edge[cntEdge].to = v;
        edge[cntEdge].nxt = head[u];
        head[u] = cntEdge;
    }

    void dfs(int pre, int now)
    {
        dep[now] = dep[pre] + 1;
        fa[now][0] = pre;
        for (int i = 1; (1 << i) <= dep[now]; ++i)
            fa[now][i] = fa[fa[now][i - 1]][i - 1];
        for (int i = head[now]; ~i; i = edge[i].nxt)
            if (edge[i].to != pre)
                dfs(now, edge[i].to);
    }
    
    int lca(int x, int y)
    {
        if (dep[x] > dep[y])
            swap(x, y);
        for (int i = 30; i >= 0; --i)
            if (dep[x] <= dep[y] - (1 << i))
                y = fa[y][i];
        if (x == y)
            return x;
        for (int i = 30; i >= 0; --i)
        {
            if (fa[x][i] == fa[y][i])
                continue;
            else 
                x = fa[x][i], y = fa[y][i];
        }
        return fa[x][0];
    }
} solver;

int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, s;
    cin >> n >> m >> s;
    solver.init();
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        solver.addEdge(u, v);
        solver.addEdge(v, u);
    }
    solver.dfs(0, s);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        cout << solver.lca(x, y) << endl;
    }
    return 0;
}