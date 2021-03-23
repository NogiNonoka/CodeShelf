/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-23 15:59:31
 * @FilePath            : /CodeShelf/GraphTheory/DifferenceConstraints.cpp
 * @Forward Declaration : Bellman - Ford (Queue)
 * @Discription         : 
 *  Difference Constraints
 *  Time Complexity: O(VE)
 *  For Minimum Solution:
 *      x - y >= c, (x, y, -c);
 *      x - y <= c, (y, x, c);
 *      x == y, (a, b, 0) && (b, a, 0);
 *  For Maximum Solution:
 *      x - y >= c, (y, x, c);
 *      x - y <= c, (x, y, -c);
 *      x == y, (a, b, 0) && (b, a, 0);
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 5E3 + 7;
const int MAXE = 1E4 + 7;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct BellmanFordQ
{
    // Difference Constraints
    // Add a source node to each other node (0, i, 0)
    // Time Complexity: O(VE)
    struct Edge
    {
        int nxt;
        int to;
        int val;
    }edge[MAXE];

    int cntEdge;
    int head[MAXN];

    void init()
    {
        cntEdge = -1;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int u, int v, int w)
    {
        /* For Minimum Solution
            x - y >= c, (x, y, -c);
            x - y <= c, (y, x, c);
            x == y, (a, b, 0) && (b, a, 0);
        */
        /* For Maximum Solution
            x - y >= c, (y, x, c);
            x - y <= c, (x, y, -c);
            x == y, (a, b, 0) && (b, a, 0);
        */ 
        cntEdge++;
        edge[cntEdge].nxt = head[u];
        edge[cntEdge].to = v;
        edge[cntEdge].val = w;
        head[u] = cntEdge;
    }

    int n; // num of Nodes
    int dis[MAXN]; // dis from s to each node
    bool vis[MAXN]; // in Queue
    int cnt[MAXN]; // cnt edge of shortest path

    bool bellmanford(int s)
    {
        memset(dis, 0x3f, sizeof(dis)); // For Longest Path, Initial to minimum dis
        memset(vis, false, sizeof(vis));
        queue<int> que;
        dis[s] = 0; que.push(s); vis[s] = true; cnt[s] = 0;
        while (!que.empty())
        {
            int now = que.front(); que.pop();
            vis[now] = false;
            for (int i = head[now]; ~i; i = edge[i].nxt)
            {
                int nxt = edge[i].to;
                int val = edge[i].val;
                if (val + dis[now] < dis[nxt])
                {
                    dis[nxt] = val + dis[now];
                    cnt[nxt] = cnt[now] + 1;
                    if (cnt[nxt] >= n) // add a source node
                        return false; // exist negitive-weight circle
                    if (!vis[nxt])
                    {
                        que.push(nxt);
                        vis[nxt] = true;
                    }
                }
                /* For Longest Path
                if (val + dis[now] > dis[nxt])
                {
                    dis[nxt] = val + dis[now];
                    cnt[nxt] = cnt[now] + 1;
                    if (cnt[nxt] >= n) // add a source node
                        return false; // exist positive-weight circle
                    if (!vis[nxt])
                    {
                        que.push(nxt);
                        vis[nxt] = true;
                    }
                }
                */
            }
        }
        return true;
    }

#ifdef DEBUG
    void showDis()
    {
        cout << s << endl;
        for (int i = 1; i <= n; ++i)
        {
            cout << dis[i] << " ";
        }
    }
#endif
}bfq;

signed main(void)
{   // Problem ID: Luogu P5960
    // Link: https://www.luogu.com.cn/problem/P5960
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    bfq.init();
    bfq.n = n + 1; // add a source node 0
    for (int i = 1; i <= n; ++i)
    {
        bfq.addEdge(0, i, 0);
    }
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        cin >> u >> v >> w;
        bfq.addEdge(v, u, w);
    }
    if (bfq.bellmanford(0))
    {
        for (int i = 1; i <= n; ++i)
        {
            cout << bfq.dis[i] << " ";
        }
        cout << endl;
    }
    else 
    {
        cout << "NO" << endl;
    }
    return 0;
}