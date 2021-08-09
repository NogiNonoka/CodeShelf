## Network Flow - Maximum Flow 最大流

### 相关概念

- 网络 Network
- 流 Flow
- 源点 s (source) 汇点 t (sink)
- 增广路 Augmenting Path
- 割与割集 Cut & Cut Set
- 增广路定理 Augmenting Path Theorem：网络达到最大流当且仅当残留网络中没有增广路。

### 解决问题

#### 最小割

- 最大流最小割定理 Maximum Flow Minimum Cut Theorem：最大流 = 最小割

#### 最大权闭合子图

- 定义：有向图中，任一点都有权值，包含每个点的后继且权值和最大的子图。
- 解法：
  - 转化为最小割（最大流）问题；
  - 建图：
    - 正权点建边 $s \rightarrow i$；
    - 负权点建边 $j \rightarrow t$；
  - 边的含义：
    - $s \rightarrow i$ 表示选择 $i$；
    - $j \rightarrow t$ 表示不选择 $j$；
  - 闭合子图：当 $s$ 与 $t$ 不连通时，才能得到闭合子图。
    - 假设 $s$ 与 $t$ 连通，则存在路径 $s \rightarrow i \rightarrow j \rightarrow t$ 使得子图中选择 $i$ 未选择其后继 $j$。
    - 假设 $s$ 与 $t$ 不连通，若存在路径 $s \rightarrow i$，对于所有的负权后继节点 $j$ 不存在 $j \rightarrow t$ 此时选择 $j$，对于所有正权后继节 $j$，由于存在 $s \rightarrow i$，最小割不会把 $s \rightarrow j$ 割掉 此时选择 $j$。
  - 最大权闭合子图权值计算：
    - 最大权闭合子图权值 $=$ 正权节点权值和 $-$ 未选正权节点权值和 $-$ 已选负权节点权值和（绝对值）；
    - 最小割 $=$ 最大流 $=$ 未选正权节点权值和 $+$ 已选负权节点权值和（绝对值）；
    - 最大权闭合子图权值 $=$ 正权节点权值和 $-$ 最小割。

### 算法思路

#### Edomonds-Karp 算法

- BFS 找增广路
- 时间复杂度：$O(VE^2)$

##### Template

```C++
struct EdmondsKarp
{
    // Edmonds Karp Algorithm
    // Find Max Flow in nonnegative Graph
    // Time Complexity: O(VE^2)
    int s, t; // Start && End
    int n;  // Num of Nodes
    int capacity[MAXN][MAXN]; // Adjacency Matrix
    int flow[MAXN][MAXN];

    int res[MAXN]; // flow in augmenting path
    int pre[MAXN]; // predecessor

    void init()
    {
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
    }

    void addEdge(int u, int v, int w)
    {
        capacity[u][v] += w; // may have Multiple Edge
    }

    bool bfs()
    {
        queue<int> q;
        memset(res, 0, sizeof(res));
        res[s] = INF;
        pre[s] = -1;
        q.push(s);
        while (!q.empty())
        {
            int now = q.front(); q.pop();
            for (int i = 1; i <= num; ++i)
            {
                if (!res[i] && flow[now][i] < capacity[now][i])
                {
                    q.push(i);
                    res[i] = min(res[now], capacity[now][i] - flow[now][i]);
                    pre[i] = now;
                    if (i == t)
                        return true; // find augmenting path
                }
            }
        }
        return false;
    }

    int edmondskarp()
    {
        // add Reverse Edge in Adjacency List
        int ans = 0;
        while (bfs())
        {
            for (int i = t; i != -1; i = pre[i])
            {
                flow[pre[i]][i] += res[t];
                flow[i][pre[i]] -= res[t];
            }
            ans += res[t];
        }
        return ans;
    }
}ek;
```

#### Dicnic 算法

- 时间复杂度：$O(V^2E)$
- 多路增广：在一次 DFS 中找出多条增广路。
- 当前弧优化：如果一条边已经被增广过，那么它就没有可能被增广第二次。我们下一次进行增广的时候，就可以不必再走那些已经被增广过的边。每次增广时，记录链式前向星中当前节点访问到的位置。

##### Template

```C++
struct Dicnic
{
    // Dicnic Algorithm
    // Find Max Flow in nonnegative Graph
    // Time Complexity: O(V^2E)
    // Edge add twice for Reverse Edge
    struct Edge
    {
        int to;
        int val;
        int nxt;
    }edge[MAXE * 2];

    int cntEdge;
    int head[MAXN];

    void init()
    {
        cntEdge = -1; // edge 0 ^ 1 = reverse edge 1
        memset(head, -1, sizeof(head));
    }

    void addEdge(int u, int v, int w)
    {
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

    bool bfs()
    {
        memset(dep, -1, sizeof(dep));
        queue<int> q;
        dep[s] = 0;
        arc[s] = head[s];
        q.push(s);
        while (!q.empty())
        {
            int now = q.front(); q.pop();
            for (int i = head[now]; ~i; i = edge[i].nxt)
            {
                int to = edge[i].to;
                if (dep[to] == -1 && edge[i].val > 0)
                {
                    dep[to] = dep[now] + 1;
                    arc[to] = head[to];
                    q.push(to);
                    if (to == t)
                        return true;
                }
            }
        }
        return false;
    }

    int dfs(int now, int flow)
    {
        if (now == t)
            return flow;
        int res = 0;
        for (int i = arc[now]; (~i) && flow; i = edge[i].nxt)
        {
            arc[now] = i;
            int to = edge[i].to;
            if (dep[to] == dep[now] + 1 && edge[i].val > 0)
            {
                int nxtFlow = dfs(to, min(flow, edge[i].val));
                if (nxtFlow == 0)
                    dep[to] = -1;
                edge[i].val -= nxtFlow;
                edge[i ^ 1].val += nxtFlow;
                flow -= nxtFlow;
                res += nxtFlow;
            }
        }
        return res;
    }

    int dicnic()
    {
        int ans = 0;
        while (bfs())
            ans += dfs(s, INF);
        return ans;
    }
}dic;
```

#### ISAP (Improved Shortest Augment Path)

- 多路增广
- 当前弧优化
- GAP 优化
  - 通过一次 BFS 给图中所有节点分层，并统计深度相同的节点个数；
  - 当某一层节点个数为 0 时增广结束。

##### Template

```C++
struct ISAP
{
    // ISAP Algorithm
    // BFS once
    // Edge add twice for Reverse Edge
    struct Edge
    {
        int to;
        int val;
        int nxt;
    }edge[MAXE];

    int cntEdge;
    int head[MAXN];

    void init()
    {
        cntEdge = -1;
        memset(head, -1, sizeof(head));
    }

    void addEdge(int u, int v, int w)
    {
        ++cntEdge;
        edge[cntEdge].to = v;
        edge[cntEdge].val = w;
        edge[cntEdge].nxt = head[u];
        head[u] = cntEdge;
    }

    int n; // num of nodes
    int s, t; // source & sink
    int dep[MAXN]; // depth in BFS dep[t] = 1;
    int arc[MAXN]; // arc optimization
    int gap[MAXN]; // gap (num of dep) optimization

    void bfs()
    {
        memset(dep, -1, sizeof(dep));
        memset(gap, 0, sizeof(gap));
        queue<int> q;
        q.push(t);
        dep[t] = 0;
        arc[t] = head[t];
        ++gap[0];
        while (!q.empty())
        {
            int now = q.front(); q.pop();
            for (int i = head[now]; ~i; i = edge[i].nxt)
            {
                int to = edge[i].to;
                if (dep[to] == -1)
                {
                    dep[to] = dep[now] + 1;
                    arc[to] = head[to];
                    ++gap[dep[to]];
                    q.push(to);
                }
            }
        }
    }

    int dfs(int now, int flow)
    {
        if (now == t)
            return flow;
        int res = 0;
        for (int i = arc[now]; ~i; i = edge[i].nxt)
        {
            arc[now] = i;
            int to = edge[i].to;
            if (dep[to] + 1 == dep[now] && edge[i].val > 0)
            {
                int nxtFlow = dfs(to, min(flow, edge[i].val));
                if (nxtFlow)
                {
                    edge[i].val -= nxtFlow;
                    edge[i ^ 1].val += nxtFlow;
                    flow -= nxtFlow;
                    res += nxtFlow;
                }
                if (flow == 0)
                    return res;
            }
        }
        if (--gap[dep[now]] == 0)
            dep[s] = n;
        ++dep[now];
        ++gap[dep[now]];
        return res;
    }

    int isap()
    {
        int ans = 0;
        bfs();
        while (dep[s] < n)
        {
            memcpy(arc, head, sizeof(head));
            ans += dfs(s, INF);
        }
        return ans;
    }
}isap;
```

### 例题

#### Luogu P3376

链接：[Luogu P3376](https://www.luogu.com.cn/problem/P3376)

模板题 (Edmonds Karp 161ms / Dicnic 42ms / ISAP 32ms)

#### Codeforces 1473F - Strange Set

链接：[CF1473F - Strange Set](https://codeforces.com/contest/1473/problem/F)

##### Problem

- 给定长度为 $n$ 的数组 $a$ 与其权值 $b$;
- 定义一个 Strange Set，若选择 $i$ ，则需要选择 $\forall j \in [1,\ i - 1] ,\ a_i \% a_j = 0$。

##### Analysis

- 网络流 最大权闭合子图
- 使用最大流 Dicnic 算法解题，复杂度 $O(V^2E)$；
- 建图时注意对于数值相同的结点，只连一条边，减少边数。

##### Code

```C++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e3 + 7;
const int MAXE = 1e5 + 7;
const int INF = 0x3f3f3f3f;


struct Dicnic
{
    // Dicnic Algorithm
    // Find Max Flow in nonnegative Graph
    // Time Complexity: O(V^2E)
    // Edge add twice for Reverse Edge
    struct Edge
    {
        int to;
        int val;
        int nxt;
    }edge[MAXE * 2];

    int cntEdge;
    int head[MAXN];

    void init()
    {
        cntEdge = -1; // edge 0 ^ 1 = reverse edge 1
        memset(head, -1, sizeof(head));
    }

    void addEdge(int u, int v, int w)
    {
        ++cntEdge;
        edge[cntEdge].to = v;
        edge[cntEdge].val = w;
        edge[cntEdge].nxt = head[u];
        head[u] = cntEdge;
    }

    int dep[MAXN]; // depth in BFS 
    int arc[MAXN]; // arc optimization

    bool bfs(int s, int t)
    {
        memset(dep, 0, sizeof(dep));
        queue<int> q;
        dep[s] = 1;
        arc[s] = head[s];
        q.push(s);
        while (!q.empty())
        {
            int now = q.front(); q.pop();
            for (int i = head[now]; ~i; i = edge[i].nxt)
            {
                int to = edge[i].to;
                if (dep[to] == 0 && edge[i].val > 0)
                {
                    dep[to] = dep[now] + 1;
                    arc[to] = head[to];
                    q.push(to);
                    if (to == t)
                        return true;
                }
            }
        }
        return false;
    }

    int dfs(int now, int flow, int t)
    {
        if (now == t)
            return flow;
        int res = 0;
        for (int i = arc[now]; (~i) && flow; i = edge[i].nxt)
        {
            arc[now] = i;
            int to = edge[i].to;
            if (edge[i].val && dep[to] == dep[now] + 1)
            {
                int nxtFlow = dfs(to, min(flow, edge[i].val), t);
                if (nxtFlow == 0)
                    dep[to] = 0;
                edge[i].val -= nxtFlow;
                edge[i ^ 1].val += nxtFlow;
                flow -= nxtFlow;
                res += nxtFlow;
            }
        }
        return res;
    }

    int dicnic(int s, int t)
    {
        int ans = 0;
        while (bfs(s, t))
            ans += dfs(s, INF, t);
        return ans;
    }
}dic;

int n;
int a[MAXN];
bool vis[100 + 7];
int ans;

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    dic.init();
    ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        memset(vis, false, sizeof(vis));
        for (int j = i - 1; j; --j)
        {
            if (a[i] % a[j] == 0 && vis[a[j]] == false)
            {
                dic.addEdge(i, j, INF);
                dic.addEdge(j, i, 0);
                vis[a[j]] = true;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int val;
        cin >> val;
        if (val > 0)
        {
            dic.addEdge(0, i, val);
            dic.addEdge(i, 0, 0);
            ans += val;
        }
        else
        {
            dic.addEdge(i, n + 1, -val);
            dic.addEdge(n + 1, i, 0);
        }
    }
    ans -= dic.dicnic(0, n + 1);
    cout << ans << endl;
    return 0;
}
```