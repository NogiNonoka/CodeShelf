/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/GraphTheory/MaxMatching_Blossom.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Blossom Algorithm (Edmonds)
 *  Maximum matching in general graph
 *  Time Complexity: O(N^3)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

struct Blossom {
    int n;
    int g[MAXN][MAXN];
    int match[MAXN], p[MAXN], base[MAXN];
    bool used[MAXN], blossom[MAXN];
    int lca, qh, qt, q[MAXN];

    void init(int _n) {
        n = _n;
        memset(g, 0, sizeof(g));
    }

    void addEdge(int u, int v) {
        g[u][v] = g[v][u] = 1;
    }

    int findLCA(int a, int b) {
        bool usedLCA[MAXN] = {};
        while (true) {
            a = base[a];
            usedLCA[a] = true;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (usedLCA[b]) return b;
            b = p[match[b]];
        }
    }

    void markPath(int v, int b, int children) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    }

    int findPath(int root) {
        memset(used, 0, sizeof(used));
        memset(p, -1, sizeof(p));
        for (int i = 1; i <= n; ++i) base[i] = i;
        used[root] = true;
        qh = qt = 0;
        q[qt++] = root;
        while (qh < qt) {
            int v = q[qh++];
            for (int to = 1; to <= n; ++to) {
                if (g[v][to] && base[v] != base[to] && match[v] != to) {
                    if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                        int curbase = findLCA(v, to);
                        memset(blossom, 0, sizeof(blossom));
                        markPath(v, curbase, to);
                        markPath(to, curbase, v);
                        for (int i = 1; i <= n; ++i)
                            if (blossom[base[i]]) {
                                base[i] = curbase;
                                if (!used[i]) {
                                    used[i] = true;
                                    q[qt++] = i;
                                }
                            }
                    } else if (p[to] == -1) {
                        p[to] = v;
                        if (match[to] == -1) return to;
                        to = match[to];
                        used[to] = true;
                        q[qt++] = to;
                    }
                }
            }
        }
        return -1;
    }

    int maxMatching() {
        memset(match, -1, sizeof(match));
        int matching = 0;
        for (int v = 1; v <= n; ++v)
            if (match[v] == -1) {
                int to = findPath(v);
                if (to != -1) {
                    ++matching;
                    while (to != -1) {
                        int pv = p[to], nv = match[pv];
                        match[to] = pv;
                        match[pv] = to;
                        to = nv;
                    }
                }
            }
        return matching;
    }
} blossom;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    blossom.init(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        blossom.addEdge(u, v);
    }
    cout << blossom.maxMatching() * 2 << endl;
    for (int i = 1; i <= n; ++i)
        if (blossom.match[i] > i)
            cout << i << " " << blossom.match[i] << endl;
    return 0;
}
