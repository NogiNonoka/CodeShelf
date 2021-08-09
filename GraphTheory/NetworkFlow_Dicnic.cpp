/*
 * @Author              : NogiNonoka
 * @Date                : 2021-01-24 15:41:54
 * @FilePath            : /CodeShelf/GraphTheory/NetworkFlow_Dicnic.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Network Flow (Maximum Flow)
 *  Dicnic
 *  Time Complexity: O(V^2E)
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

#define int long long
using namespace std;
const int MAXN = 5E2 + 7;
const int MAXE = 5E3 + 7;
const int INF = 0x3f3f3f3f;

struct Dicnic {
    // Dicnic Algorithm
    // Find Max Flow in nonnegative Graph
    // Time Complexity: O(V^2E)
    // Edge add twice for Reverse Edge
    struct Edge {
        int to;
        int val;
        int nxt;
    } edge[MAXE * 2];

    int cntEdge;
    int head[MAXN];

    void init() {
        cntEdge = -1; // edge 0 ^ 1 = reverse edge 1
        memset(head, -1, sizeof(head));
    }

    void addEdge(int u, int v, int w) {
        ++cntEdge;
        edge[cntEdge].to = v;
        edge[cntEdge].val = w;
        edge[cntEdge].nxt = head[u];
        head[u] = cntEdge;
    }

    int n;
    int s, t;
    int dep[MAXN]; // depth in BFS
    int arc[MAXN]; // arc optimization

    bool bfs() {
        memset(dep, -1, sizeof(dep));
        queue<int> q;
        dep[s] = 0;
        arc[s] = head[s];
        q.push(s);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i = head[now]; ~i; i = edge[i].nxt) {
                int to = edge[i].to;
                if (dep[to] == -1 && edge[i].val > 0) {
                    dep[to] = dep[now] + 1;
                    arc[to] = head[to];
                    q.push(to);
                    if (to == t) return true;
                }
            }
        }
        return false;
    }

    int dfs(int now, int flow) {
        if (now == t) return flow;
        int res = 0;
        for (int& i = arc[now]; (~i) && flow; i = edge[i].nxt) {
            int to = edge[i].to;
            if (dep[to] == dep[now] + 1 && edge[i].val > 0) {
                int nxtFlow = dfs(to, min(flow, edge[i].val));
                if (nxtFlow == 0) dep[to] = -1;
                edge[i].val -= nxtFlow;
                edge[i ^ 1].val += nxtFlow;
                flow -= nxtFlow;
                res += nxtFlow;
            }
        }
        return res;
    }

    int dicnic() {
        int ans = 0;
        while (bfs()) ans += dfs(s, INF);
        return ans;
    }
} dic;

signed main(void) {
    // Problem ID: Luogu P3376
    // Link: https://www.luogu.com.cn/problem/P3376
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    dic.init();
    int m;
    cin >> dic.n >> m >> dic.s >> dic.t;
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dic.addEdge(u, v, w);
        dic.addEdge(v, u, 0);
    }
    cout << dic.dicnic();
    return 0;
}