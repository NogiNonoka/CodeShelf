/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-31
 * @FilePath            : /CodeShelf/GraphTheory/DirectedMST_ChuLiuEdmonds.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Chu-Liu/Edmonds Algorithm
 *  Minimum spanning arborescence in directed graph
 *  Time Complexity: O(VE)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 0x3f3f3f3f;

struct Edge {
    int u, v, w;
};

int in[MAXN], pre[MAXN], id[MAXN], vis[MAXN];

int directedMST(int root, int n, vector<Edge>& edges) {
    int res = 0;
    while (true) {
        for (int i = 0; i < n; ++i) in[i] = INF;
        for (auto& e : edges) {
            if (e.u != e.v && e.w < in[e.v]) {
                in[e.v] = e.w;
                pre[e.v] = e.u;
            }
        }
        in[root] = 0;
        for (int i = 0; i < n; ++i)
            if (i != root && in[i] == INF) return -1;
        int cnt = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        for (int i = 0; i < n; ++i) {
            res += in[i];
            int v = i;
            while (vis[v] != i && id[v] == -1 && v != root) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != root && id[v] == -1) {
                for (int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if (cnt == 0) break;
        for (int i = 0; i < n; ++i)
            if (id[i] == -1) id[i] = cnt++;
        vector<Edge> newEdges;
        for (auto& e : edges) {
            int u = id[e.u], v = id[e.v];
            if (u != v) newEdges.push_back({u, v, e.w - in[e.v]});
        }
        n = cnt;
        root = id[root];
        edges = newEdges;
    }
    return res;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, root;
    cin >> n >> m >> root;
    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    cout << directedMST(root, n, edges) << endl;
    return 0;
}
