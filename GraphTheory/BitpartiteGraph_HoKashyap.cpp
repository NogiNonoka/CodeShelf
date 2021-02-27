/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-22 20:56:18
 * @FilePath            : /CodeShelf/GraphTheory/BitpartiteGraph_HoKashyap.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Bitpartite Graph (Maximum Matching)
 *  Ho Kashyap
 *  Time Complexity: O(V^(1/2)E)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e5 + 7;
// const int MAXE = ;
// const int MOD = ;
const int INF = 0x3f3f3f3f;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct HoKashyap
{
    // Find Maximum Matching on Unweighted Bitpartite Graph
    // Time Complexity: O(V^(1/2)E)
    int cntx, cnty; // Num of Set 1 && Set 2
    vector<int> graph[MAXN]; // Edge Set 1 to Set 2
    int matchx[MAXN], matchy[MAXN];
    int depx[MAXN], depy[MAXN]; // Depth
    int dep;
    bool vis[MAXN];

    void init()
    {
        memset(matchx, -1, sizeof(matchx));
        memset(matchy, -1, sizeof(matchy));
    }

    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
    }

    bool bfs()
    {
        queue<int> q;
        dep = INF;
        memset(depx, -1, sizeof(depx));
        memset(depy, -1, sizeof(depy));
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= cntx; ++i)
        {
            if (matchx[i] == -1)
            {
                q.push(i);
                depx[i] = 0;
            }
        }
        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            if (depx[now] > dep)
                break;
            for (int i = 0; i < graph[now].size(); ++i)
            {
                int nxt = graph[now][i];
                if (depy[nxt] == -1)
                {
                    depy[nxt] = depx[now] + 1;
                    if (matchy[nxt] == -1)
                        dep = depy[nxt];
                    else
                    {
                        depx[matchy[nxt]] = depy[nxt] + 1;
                        q.push(matchy[nxt]);
                    }
                }
            }
        }
        return dep != INF;
    }

    bool dfs(int now)
    {
        for (int i = 0; i < graph[now].size(); ++i)
        {
            int nxt = graph[now][i];
            if (!vis[nxt] && depy[nxt] == depx[now] + 1)
            {
                vis[nxt] = true;
                if(matchy[nxt] != -1 && depy[nxt] == dep)
                    continue;
                if(matchy[nxt] == -1 || dfs(matchy[nxt]))
                {
                    matchy[nxt] = now;
                    matchx[now] = nxt;
                    return true;
                }
            }
        }
        return false;
    }

    int hokashyap()
    {
        int ans = 0;
        while (bfs())
            for (int i = 1; i <= cntx; ++i)
                if (matchx[i] == -1 && dfs(i))
                    ans++;
        return ans;
    }
}hk;

int32_t main(void)
{
    // Problem ID: Luogu P3386
    // Link: https://www.luogu.com.cn/problem/P3386
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, e;
    cin >> n >> m >> e;
    hk.init();
    hk.cntx = n; hk.cnty = m;
    for (int i = 1; i <= e; ++i)
    {
        int u, v;
        cin >> u >> v;
        hk.addEdge(u, v);
    }
    cout << hk.hokashyap() << endl;
    return 0;
}