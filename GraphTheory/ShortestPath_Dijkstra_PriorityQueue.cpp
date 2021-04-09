/*
 * @Author              : NogiNonoka
 * @Date                : 2020-11-13 19:16:05
 * @FilePath            : /CodeShelf/GraphTheory/ShortestPath_Dijkstra_PriorityQueue.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Shortest Path
 *  Dijkstra (Priority_Queue Ver.)
 *  Time Complexity: O(ElogE)
 */

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define int long long
#define endl "\n"
const int MAXN = 1e5 + 7;
const int MAXE = 2e5 + 7;

struct DijkstraPQ
{
    // Shortest Path in Non-negtive Directed Graph
    // Edge in Undirected Graph should add twice
    // Time Complexity: O(ElogE)
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
        cntEdge++;
        edge[cntEdge].nxt = head[u];
        edge[cntEdge].to = v;
        edge[cntEdge].val = w;
        head[u] = cntEdge;
    }

    int n; // num of Nodes
    int dis[MAXN]; // dis from s to each node

    void dijkstra(int s)
    {
        memset(dis, 0x3f, sizeof(dis));
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
        // priority_queue greater<>() top is smallest
        que.push({0, s});
        dis[s] = 0;
        while (!que.empty())
        {
            int now = que.top().second;
            int nowval = que.top().first;
            que.pop();
            if (nowval > dis[now])
                continue;
            for (int i = head[now]; ~i; i = edge[i].nxt)
            {
                int nxt = edge[i].to;
                int nxtval = edge[i].val;
                if (nxtval + dis[now] < dis[nxt])
                {
                    dis[nxt] = dis[now] + nxtval;
                    que.push({dis[nxt], nxt});
                }
            }
        }
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
} dij;

int32_t main(void)
{
    // Problem ID: Luogu P4779
    // Link: https://www.luogu.com.cn/problem/P4779
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    dij.init();
    int n, m, s;
    cin >> n >> m >> s;
    dij.n = n;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dij.addEdge(u, v, w);
    }
    dij.dijkstra(s);
    for (int i = 1; i <= n; ++i)
        cout << dij.dis[i] << " ";
    cout << endl;
    return 0;
}