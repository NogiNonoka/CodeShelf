/*  Author: zyy@nju
    Date: 2021.1.12
    Time Complexity: O(V^2E)
    Usage: Modify Init();   */

#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXE = 5e3 + 7;
const int MAXN = 5e2 + 7;

class FlowEdge {
  public:
    int u, v;
    int cap, flow = 0;
    FlowEdge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
};

int n = 0, m = 0, tot = 0;
int s = 0, t = 0;
vector<FlowEdge> edges;
vector<int> adj[MAXN]; // SAVE EDGE ID!
int level[MAXN];
int ptr[MAXE];
queue<int> q;

void addEdge(int u, int v, int cap) {
    edges.push_back({u, v, cap});
    edges.push_back({v, u, 0});
    adj[u].push_back(tot++);
    adj[v].push_back(tot++);
}

bool bfs() {
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int id : adj[u]) {
            FlowEdge e = edges[id];
            if (e.cap - e.flow < 1) continue;
            if (level[e.v] != -1) continue;
            level[e.v] = level[u] + 1;
            q.push(e.v);
        }
    }
    return level[t] != -1;
}

int dfs(int u, int pushed) {
    if (!pushed) return 0;
    if (u == t) return pushed;
    for (int& cid = ptr[u]; cid < (int)adj[u].size(); ++cid) {
        int id = adj[u][cid];
        FlowEdge e = edges[id];
        int v = e.v;
        if (level[v] != level[u] + 1 || e.cap - e.flow < 1) continue;

        int delta = dfs(v, min(pushed, e.cap - e.flow));
        if (!delta) continue;

        edges[id].flow += delta;
        edges[id ^ 1].flow -= delta;
        return delta;
    }
    return 0;
}

int maxFlow() {
    int ret = 0;
    while (true) {
        memset(level, -1, sizeof(level));
        level[s] = 0;
        q.push(s);

        if (!bfs()) break;

        memset(ptr, 0, sizeof(ptr));
        while (true) {
            int pushed = dfs(s, INF);
            if (!pushed) break;
            ret += pushed;
        }
    }
    return ret;
}

void init() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i) {
        int u, v, cap;
        scanf("%d%d%d", &u, &v, &cap);
        addEdge(u, v, cap);
    }
}

int main() {
    init();
    printf("%d\n", maxFlow());
    return 0;
}