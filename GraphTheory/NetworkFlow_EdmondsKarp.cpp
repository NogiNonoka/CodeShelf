/*
 * @Author              : NogiNonoka
 * @Date                : 2021-01-14 16:41:37
 * @FilePath            : /CodeShelf/GraphTheory/NetworkFlow_EdmondsKarp.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Network Flow
 *  Edmonds Karp (Adjacency Matrix)
 *  Time Complexity: O(VE^2)
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
const int MAXN = 1e3 + 7;
const int INF = 0x3f3f3f3f;

struct EdmondsKarp
{
    // Edmonds Karp Algorithm
    // Find Max Flow in nonnegative Graph
    // Time Complexity: O(VE^2)
    int s, t; // Start && End
    int num;  // Num of Nodes
    int capacity[MAXN][MAXN]; // Adjacency Matrix
    int flow[MAXN][MAXN];

    int res[MAXN]; // flow in augmenting path
    int pre[MAXN]; // predecessor

    void init()
    {
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
    }

    void addEdge(int u, int v, int w)
    {
        capacity[u][v] += w; // may have Multiple Edge
    }

    bool bfs()
    {
        queue<int> q;
        memset(res, 0, sizeof(res));
        res[s] = INF;
        pre[s] = -1;
        q.push(s);
        while (!q.empty())
        {
            int now = q.front(); q.pop();
            for (int i = 1; i <= num; ++i)
            {
                if (!res[i] && flow[now][i] < capacity[now][i])
                {
                    q.push(i);
                    res[i] = min(res[now], capacity[now][i] - flow[now][i]);
                    pre[i] = now;
                    if (i == t)
                        return true; // find augmenting path
                }
            }
        }
        return false;
    }

    int edmondskarp()
    {
        // add Reverse Edge in Adjacency List
        int ans = 0;
        while (bfs())
        {
            for (int i = t; i != -1; i = pre[i])
            {
                flow[pre[i]][i] += res[t];
                flow[i][pre[i]] -= res[t];
            }
            ans += res[t];
        }
        return ans;
    }
}ek;

int32_t main(void)
{
    // Problem ID: Luogu P3376
    // Link: https://www.luogu.com.cn/problem/P3376
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ek.init();
    int m;
    cin >> ek.num >> m >> ek.s >> ek.t;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        ek.addEdge(u, v, w);
    }
    cout << ek.edmondskarp();
    return 0;
}