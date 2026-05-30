/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/GraphTheory/NetworkFlow_MCMF.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : claude-opus-4-8
 *  Minimum Cost Maximum Flow (MCMF)
 *  SPFA + EK
 *  Time Complexity: O(VE * flow)
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 5e3 + 7;
const int MAXE = 5e4 + 7;
const int INF = 0x3f3f3f3f;

struct MCMF {
    struct Edge {
        int to, nxt;
        int cap, cost;
    } edge[MAXE << 1];

    int head[MAXN], cntEdge;
    int dis[MAXN], pre[MAXN], preEdge[MAXN];
    bool inq[MAXN];
    int n, s, t;
    int maxFlow, minCost;

    void init(int _n) {
        n = _n;
        cntEdge = -1;
        for (int i = 0; i <= n; ++i) head[i] = -1;
    }

    void addEdge(int u, int v, int cap, int cost) {
        edge[++cntEdge] = {v, head[u], cap, cost};
        head[u] = cntEdge;
        edge[++cntEdge] = {u, head[v], 0, -cost};
        head[v] = cntEdge;
    }

    bool spfa() {
        for (int i = 0; i <= n; ++i) {
            dis[i] = INF;
            inq[i] = false;
        }
        queue<int> q;
        dis[s] = 0; inq[s] = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = false;
            for (int i = head[u]; ~i; i = edge[i].nxt) {
                int v = edge[i].to;
                if (edge[i].cap > 0 && dis[v] > dis[u] + edge[i].cost) {
                    dis[v] = dis[u] + edge[i].cost;
                    pre[v] = u;
                    preEdge[v] = i;
                    if (!inq[v]) {
                        inq[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    void run(int _s, int _t) {
        s = _s; t = _t;
        maxFlow = minCost = 0;
        while (spfa()) {
            int flow = INF;
            for (int u = t; u != s; u = pre[u])
                flow = min(flow, edge[preEdge[u]].cap);
            for (int u = t; u != s; u = pre[u]) {
                edge[preEdge[u]].cap -= flow;
                edge[preEdge[u] ^ 1].cap += flow;
            }
            maxFlow += flow;
            minCost += flow * dis[t];
        }
    }
} mcmf;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    mcmf.init(n);
    for (int i = 1; i <= m; ++i) {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        mcmf.addEdge(u, v, cap, cost);
    }
    mcmf.run(s, t);
    cout << mcmf.maxFlow << " " << mcmf.minCost << endl;
    return 0;
}
