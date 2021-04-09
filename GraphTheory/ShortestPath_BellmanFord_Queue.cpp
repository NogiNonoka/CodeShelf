/*
 * @Author              : NogiNonoka
 * @Date                : 2020-11-13 20:11:53
 * @FilePath            : /CodeShelf/GraphTheory/ShortestPath_BellmanFord_Queue.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Shortest Path
 *  Bellman Ford (Queue Ver)
 *  Time Complexity: O(VE)
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define int long long
#define endl "\n"
const int MAXN = 1e4 + 7;
const int MAXE = 5e5 + 7;

struct BellmanFordQ
{
    // Shortest Path in Directed Graph
    // Edge in Undirected Graph should add twice
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
        ++cntEdge;
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
                    if (cnt[nxt] >= n)
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
                    if (cnt[nxt] >= n)
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
} bfq;

int32_t main(void)
{
    // Problem ID: Luogu P3371
    // Link: https://www.luogu.com.cn/problem/P3371
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    bfq.init();
    cin >> bfq.n >> bfq.m >> bfq.s;
    for (int i = 1; i <= bfq.m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        bfq.addEdge(u, v, w);
    }
    bfq.bellmanford();
    for (int i = 1; i <= bfq.n; ++i)
    {
        if (bfq.dis[i] > (1LL << 31) - 1)
            bfq.dis[i] = (1LL << 31) - 1;
        cout << bfq.dis[i] << " ";
    }
    cout << endl;
    return 0;
}