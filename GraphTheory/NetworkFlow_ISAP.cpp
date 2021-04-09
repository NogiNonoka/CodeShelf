/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-15 00:37:49
 * @FilePath            : /CodeShelf/GraphTheory/NetworkFlow_ISAP.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Network Flow (Maximum Flow)
 *  ISAP (Improved Shortest Augumenting Path)
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e2 + 7;
const int MAXE = 1e5 + 7;
const int INF = 0x3f3f3f3f;

struct ISAP
{
    // ISAP Algorithm
    // BFS once
    // Edge add twice for Reverse Edge
    struct Edge
    {
        int to;
        int val;
        int nxt;
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
        edge[cntEdge].to = v;
        edge[cntEdge].val = w;
        edge[cntEdge].nxt = head[u];
        head[u] = cntEdge;
    }

    int n; // num of nodes
    int s, t; // source & sink
    int dep[MAXN]; // depth in BFS dep[t] = 1;
    int arc[MAXN]; // arc optimization
    int gap[MAXN]; // gap (num of dep) optimization

    void bfs()
    {
        memset(dep, -1, sizeof(dep));
        memset(gap, 0, sizeof(gap));
        queue<int> q;
        q.push(t);
        dep[t] = 0;
        arc[t] = head[t];
        ++gap[0];
        while (!q.empty())
        {
            int now = q.front(); q.pop();
            for (int i = head[now]; ~i; i = edge[i].nxt)
            {
                int to = edge[i].to;
                if (dep[to] == -1)
                {
                    dep[to] = dep[now] + 1;
                    arc[to] = head[to];
                    ++gap[dep[to]];
                    q.push(to);
                }
            }
        }
    }

    int dfs(int now, int flow)
    {
        if (now == t)
            return flow;
        int res = 0;
        for (int i = arc[now]; ~i; i = edge[i].nxt)
        {
            arc[now] = i;
            int to = edge[i].to;
            if (dep[to] + 1 == dep[now] && edge[i].val > 0)
            {
                int nxtFlow = dfs(to, min(flow, edge[i].val));
                if (nxtFlow)
                {
                    edge[i].val -= nxtFlow;
                    edge[i ^ 1].val += nxtFlow;
                    flow -= nxtFlow;
                    res += nxtFlow;
                }
                if (flow == 0)
                    return res;
            }
        }
        if (--gap[dep[now]] == 0)
            dep[s] = n;
        ++dep[now];
        ++gap[dep[now]];
        return res;
    }

    int isap()
    {
        int ans = 0;
        bfs();
        while (dep[s] < n)
        {
            memcpy(arc, head, sizeof(head));
            ans += dfs(s, INF);
        }
        return ans;
    }
} isap;

int32_t main(void)
{
    // Problem ID: Luogu P3376
    // Link: https://www.luogu.com.cn/problem/P3376
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    isap.init();
    int n, m, s, t;
    cin >> isap.n >> m >> isap.s >> isap.t;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        isap.addEdge(u, v, w);
        isap.addEdge(v, u, 0);
    }
    cout << isap.isap() << endl;
    return 0;
}