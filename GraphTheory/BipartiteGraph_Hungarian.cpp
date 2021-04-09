/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-21 21:04:10
 * @FilePath            : /CodeShelf/GraphTheory/BipartiteGraph_Hungarian.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Bipartite Graph (Maximum Matching)
 *  Hungrian
 *  Time Complexity: O(VE)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e5 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Hungarian
{
    // Find Maximum Matching on Unweighted Bipartite Graph
    // Time Complexity: O(VE)
    int n, m; // cnt of set1 and set2
    vector<int> graph[MAXN]; 
    int match[MAXN]; // partner of set2
    bool vis[MAXN];

    void init(int n, int m)
    {
        this->n = n;
        this->m = m;
        for (int i = 1; i <= n; ++i)
            graph[i].clear();
        memset(match, 0, sizeof(int) * m);
    }

    void addEdge(int x, int y)
    {
        graph[x].push_back(y);
    }

    bool dfs(int x)
    {
        for (auto i : graph[x])
        {
            if (vis[i] == false)
            {
                vis[i] = true;
                if (match[i] == 0 || dfs(match[i]))
                {
                    match[i] = x;
                    return true;
                }
            }
        }
        return false;
    }

    int hungarian()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            memset(vis, 0, sizeof(bool) * n);
            if (dfs(i))
                ans++;
        }
        return ans;
    }
} hg;

int32_t main(void)
{
    // Problem ID: Luogu P3386
    // Link: https://www.luogu.com.cn/problem/P3386
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, e;
    cin >> n >> m >> e;
    hg.init(n, m);
    for (int i = 1; i <= e; ++i)
    {
        int u, v;
        cin >> u >> v;
        hg.addEdge(u, v);
    }
    cout << hg.hungarian() << endl;
    return 0;
}