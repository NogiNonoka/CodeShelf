/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/GraphTheory/CentroidDecomposition.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Centroid Decomposition
 *  Count paths with specific property on tree
 *  Time Complexity: O(NlogN)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 7;

struct CentroidDecomposition {
    struct Edge {
        int to, w;
    };
    vector<Edge> adj[MAXN];
    bool del[MAXN];
    int sz[MAXN];
    int n;
    int ans;

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void calcSize(int u, int f) {
        sz[u] = 1;
        for (auto &e : adj[u]) {
            int v = e.to;
            if (v == f || del[v]) continue;
            calcSize(v, u);
            sz[u] += sz[v];
        }
    }

    int findCentroid(int u, int f, int total) {
        for (auto &e : adj[u]) {
            int v = e.to;
            if (v == f || del[v]) continue;
            if (sz[v] * 2 > total) return findCentroid(v, u, total);
        }
        return u;
    }

    void collect(int u, int f, int dist, vector<int> &vec) {
        vec.push_back(dist);
        for (auto &e : adj[u]) {
            int v = e.to;
            if (v == f || del[v]) continue;
            collect(v, u, dist + e.w, vec);
        }
    }

    void solve(int u) {
        calcSize(u, 0);
        int c = findCentroid(u, 0, sz[u]);
        del[c] = true;

        // count paths passing through centroid
        // customize by problem
        // example: count pairs with sum <= K
        vector<int> all;
        all.push_back(0);
        for (auto &e : adj[c]) {
            int v = e.to;
            if (del[v]) continue;
            vector<int> tmp;
            collect(v, c, e.w, tmp);
            // process tmp
            for (int x : tmp) all.push_back(x);
        }

        for (auto &e : adj[c]) {
            int v = e.to;
            if (del[v]) continue;
            solve(v);
        }
    }

    void init(int _n) {
        n = _n;
        ans = 0;
        for (int i = 1; i <= n; ++i) {
            del[i] = false;
            adj[i].clear();
        }
    }
} cd;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    cd.init(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        cd.addEdge(u, v, w);
    }
    cd.solve(1);
    cout << cd.ans << endl;
    return 0;
}
