#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 5e4 + 7;
const int MAXE = 6e5 + 7;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Edge {
    int v, nxt;
} e[MAXE];

int cnt = 2, head[MAXN];

void add(int u, int v) {
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt++;
}

int ts = 0;
int dfn[MAXN], low[MAXN];
bool bridge[MAXE];

void tarjan(int u, int eid) {
    dfn[u] = low[u] = ++ts;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (!dfn[v]) {
            tarjan(v, i);
            if (low[v] > dfn[u]) bridge[i] = bridge[i ^ 1] = true;
            low[u] = min(low[v], low[u]);
        } else if (i != (eid ^ 1)) {
            low[u] = min(low[u], dfn[v]);
        } 
    } 
}

int tot = 0;
int bcc[MAXN];

void dfs(int u, int id) {
    bcc[u] = id;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (bcc[v] || bridge[i]) continue;
        dfs(v, id);
    }
}

int n, m, u, v;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    cnt = 2;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    ts = 0;
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) tarjan(i, 0);
    }
    tot = 0;
    for (int i = 1; i <= n; ++i) {
        if (!bcc[i]) dfs(i, ++tot);
    }
    cout << tot << endl;
    return 0;
}