#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e4 + 7;
const int MAXE = 1e5 + 7;

// Find Cut Vertex in Undirected Graph
// Time Complexity: O(N)
int n, m;
struct Edge {
    int v, nxt;
} e[MAXE << 1];

int cnt = 2, head[MAXN];

void add(int u, int v) { 
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt++;
}

int ts = 0;
int dfn[MAXN], low[MAXN];
bool cut[MAXN];

void tarjan(int u, int root) { 
    dfn[u] = low[u] = ++ts;
    int son = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (!dfn[v]) {
            tarjan(v, root);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != root) cut[u] = true;
            if (u == root) son += 1;
        } else
            low[u] = min(low[u], dfn[v]);
    }
    if (u == root && son >= 2) cut[root] = true;
}

signed main(void) {
    // Problem ID: Luogu P3388
    // Link: https://www.luogu.com.cn/problem/P3388
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    int u, v;
    for (int i = 1; i <= m; ++i) { 
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    int tot = 0;
    for (int i = 1; i <= n; ++i) { 
        if (!dfn[i]) tarjan(i, i);
        if (cut[i]) ++tot;
    }
    cout << tot << endl;
    for (int i = 1; i <= n; ++i) { 
        if (cut[i]) cout << i << " ";
    }
    return 0;
}