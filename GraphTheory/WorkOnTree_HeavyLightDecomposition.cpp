/*
 * @Author              : NogiNonoka
 * @Date                : 2020-12-09 21:49:25
 * @FilePath            : /CodeShelf/GraphTheory/WorkOnTree_HeavyLightDecomposition.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Work On Tree
 *  Heavy Light Decomposition
 *  Get Lowest Common Ancestor
 *  Time Complexity: O(NlogN+M(logN)^2)
 */

#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 5e6 + 7;

struct HeavyLightDecomposition
{
    // Get Lowest Common Ancestor
    // with Unrooted Tree, Add Edge Twice
    // Time Complexity: O(NlogN+M(logN)^2)
    int n;

    struct Edge
    {
        int v;
        int w;
        int nxt;
    }edge[MAXN];

    int cntEdge;
    int head[MAXN];

    void addEdge(int u, int v, int w)
    {
        ++cntEdge;
        edge[cntEdge].v = v;
        edge[cntEdge].w = w;
        edge[cntEdge].nxt = head[u];
        head[u] = cntEdge;
    }

    int fa[MAXN]; // Node's Father
    int dep[MAXN]; // Depth
    int siz[MAXN]; // Num of Nodes in Tree
    int son[MAXN]; // Heavy Son

    int ts; // Time Stamp
    int top[MAXN]; // Top Node in Link
    int dfn[MAXN]; // Dfs Order
    int rnk[MAXN]; // rnk[dfn[x]] = x

    void init(int n)
    {
        this->n = n;
        this->cntEdge = 0;
        memset(head, 0, sizeof(head));
        memset(son, 0, sizeof(son));
        this->ts = 0;
    }

    void dfs1(int pre, int now)
    {
        fa[now] = pre; dep[now] = dep[pre] + 1; siz[now] = 1; son[now] = 0; 
        for (int i = head[now]; i; i = edge[i].nxt)
        {
            int nxt = edge[i].v;
            if (nxt == pre)
                continue; // Undirected Graph (Unrooted Tree)
            dfs1(now, nxt);
            siz[now] += siz[nxt]; // val[nxt] = val[now] + edge[i].w;
            if (son[now] == 0 || siz[nxt] > siz[son[now]])
                son[now] = nxt;
        }
    }

    void dfs2(int pre, int now)
    {
        top[now] = pre; dfn[now] = ++ts; rnk[ts] = now;
        if (son[now] == 0)
            return;
        dfs2(pre, son[now]);
        for (int i = head[now]; i; i = edge[i].nxt)
        {
            int nxt = edge[i].v;
            if (nxt != son[now] && nxt != fa[now])
                dfs2(nxt, nxt);
        }
    }

    int lca(int x, int y)
    {
        while (top[x] != top[y])
        {
            if (dep[top[x]] > dep[top[y]])
                x = fa[top[x]];
            else 
                y = fa[top[y]];
        }
        return (dep[x] > dep[y] ? y : x);
    }
}hld;

int main(void)
{
    // Problem ID: Luogu P3379
    // Link: https://www.luogu.com.cn/problem/P3379
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, r;
    cin >> n >> m >> r;
    hld.init(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        hld.addEdge(u, v, 0);
        hld.addEdge(v, u, 0);
    }
    hld.dfs1(r, r);
    hld.dfs2(r, r);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        cout << hld.lca(x, y) << "\n";
    }
    return 0;
}