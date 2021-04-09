/*
 * @Author              : Tilnel
 * @Date                : 2020-12-09 10:22:57
 * @FilePath            : /CodeShelf/GraphTheory/StronglyConnectedComponents_Tarjan.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Strongly Connected Components in Directed Graph
 *  Tarjan
 *  Time Complexity: O(V+E)
 */

#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 7;

struct Tarjan
{
    // Strongly Connected Components in Directed Graph
    // In Undirected Graph Use Pre for Check father
    // Use dfn[] to traverse Disconnected Graph
    // Time Complexity: O(V+E)
    int n; // Num of Node
    int ts = 0;   // Time Stamp
    int dfn[MAXN]; // Dfs Order
    int low[MAXN];
    int belong[MAXN]; // Componet ID
    bool vis[MAXN];
    vector<int> edges[MAXN];
    stack<int> s;
    int cnt = 0;

    void init(int n)
    {
        this->n = n;
        this->cnt = 0;
        this->ts = 0;
        memset(vis, 0, sizeof(vis));
    }
    
    void addEdge(int u, int v)
    {
        edges[u].push_back(v); // add Twice in Undirected Graph
    }
    
    void dfs(int pre, int now) 
    {
        vis[now] = true;
        s.emplace(now);
        low[now] = dfn[now] = ++ts;
        for (auto &nxt : edges[now]) 
        {
            if (dfn[nxt] == 0) 
            {
                dfs(now , nxt);
                low[now] = min(low[now], low[nxt]);
            } 
            else if (vis[nxt]) // && nxt != pre) in undirected graph, add this
            {   
                low[now] = min(low[now], dfn[nxt]);
            }
        }
        if (low[now] == dfn[now] && vis[now]) 
        {
            ++cnt;
            while (!s.empty() && s.top() != now) 
            {
                belong[s.top()] = cnt; vis[s.top()] = false; s.pop();
            }
            if (!s.empty()) 
                s.pop();
            belong[now] = cnt; vis[now] = false;
        }
    }

    void traverse()
    {
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i, i);
    }
} trj;

bool flg[MAXN];

int main(void)
{
    // Problem ID: Luogu P2002
    // Link: https://www.luogu.com.cn/problem/P2002
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m;
    int ans = 0;
    cin >> n >> m;
    trj.init(n);
    memset(flg, 0,sizeof(flg));
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        cin >> x >> y;
        trj.addEdge(x, y);
    }
    trj.traverse();
    for (int i = 1; i <= n; ++i)
    {
        for (auto nxt : trj.edges[i])
        {
            if (trj.belong[i] != trj.belong[nxt])
            {
                flg[trj.belong[nxt]] = true;
            }
        }
    }
    for (int i = 1; i <= trj.cnt; ++i)
    {
        if (!flg[i])
            ans++;
    }
    cout << ans << endl;
}