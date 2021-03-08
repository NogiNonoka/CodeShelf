## Bipartite Graph

### 相关概念

- 二分图：顶点集 $V$ 可分割为两个**互不相交**的子集，并且图中每条边依附的两个顶点都分属于这两个互不相交的子集，两个子集内的顶点不相邻。
   - 判定定理：一个图是二分图当且仅当没有长度为奇数的圈。
- 二分图匹配
   - 匹配：任意两条边都没有公共顶点的边的集合称为匹配。
   - 最大匹配：包含边的个数最多的一组匹配。
   - 完美匹配：如果一个匹配中，图中的**每个顶点**都和图中某条边相关联，则称此匹配为**完全匹配**，也称作**完备匹配**。
   - 增广路：一个连接两个**非匹配点**的路径 $path$， 使得非匹配边和匹配边在 $path$ 上交替出现(第一条边和最后一条边都是未匹配边)，称 $path$ 是一个增广路。
     - 增广路的长度为奇数。
     - 不属于匹配的边比匹配中的边多一条。
     - 对增广路进行取反操作可以得到一个更大的匹配 $M'$。
     - 若 $M$ 为图 $G$ 的最大匹配当且仅当不存在相对于 $M$ 的增广路。
- 二分图最大匹配转化为最大流，二分图最大权完美匹配转化为费用流。

### 解决问题

#### 最大独立集（最小点覆盖）

- 最大独立集 = 顶点个数 - 最小点覆盖
- 最小点覆盖通过**网络流**或**二分图最大匹配求得**

##### Problem

[2021 Training League 01](https://ac.nowcoder.com/acm/contest/12606/B)

##### Analysis

- 给定 $n$ 个点，边表示端点不能同时出现在所选集合；
- 最大独立集问题，将其转化为最小点覆盖通过最大流或二分图最大匹配问题；
- 删除被匹配的点后，根据二分图最大匹配的性质，图中不存在可行增广路，求得最小点覆盖，则此时剩余点为最大独立集。

##### Code

```C++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e2 + 7;

int n;
string s[MAXN];

struct Hungarian
{
    // Find Maximum Matching on Unweighted Bipartite Graph
    // Time Complexity: O(VE)
    int n, m; // cnt of set1 and set2
    vector<int> graph[MAXN]; 
    int match[MAXN]; // partner of set2
    bool vis[MAXN];

    void init(int n, int m)
    {
        this->n = n;
        this->m = m;
        for (int i = 1; i <= n; ++i)
            graph[i].clear();
        memset(match, 0, sizeof(int) * m);
    }

    void addEdge(int x, int y)
    {
        graph[x].push_back(y);
    }

    bool dfs(int x)
    {
        for (auto i : graph[x])
        {
            if (vis[i] == false)
            {
                vis[i] = true;
                if (match[i] == 0 || dfs(match[i]))
                {
                    match[i] = x;
                    return true;
                }
            }
        }
        return false;
    }

    int hungarian()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            memset(vis, 0, sizeof(bool) * n);
            if (dfs(i))
                ans++;
        }
        return ans;
    }
}hg;

void build(int n)
{
    hg.init(n ,n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            int cnt = 0;
            for (int p = 0; p < s[i].length(); ++p)
            {
                if (s[i][p] != s[j][p])
                {
                    ++cnt;
                }
            }
            if (cnt == 2)
            {
                hg.addEdge(i, j);
                hg.addEdge(j, i);
            }
        }
    }
}

int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> s[i];
    build(n);
    int ans = n - hg.hungarian() / 2;
    // for (int i = 1; i <= n; ++i)
    //     cout << hg.match[i] << " ";
    // cout << endl;
    cout << ans << endl;
    return 0;
}
```

### Bipartite Graph's Maximum Matching

#### Hungarian Algorithm

##### Algorithm

- 原理：DFS 找增广路，求二分图最大匹配
- 时间复杂度 $O(VE)$

##### Template

```C++
struct Hungarian
{
    // Find Maximum Matching on Unweighted Bipartite Graph
    // Time Complexity: O(VE)
    int n, m; // cnt of set1 and set2
    vector<int> graph[MAXN]; 
    int match[MAXN]; // partner of set2
    bool vis[MAXN];

    void init(int n, int m)
    {
        this->n = n;
        this->m = m;
        for (int i = 1; i <= n; ++i)
            graph[i].clear();
        memset(match, 0, sizeof(int) * m);
    }

    void addEdge(int x, int y)
    {
        graph[x].push_back(y);
    }

    bool dfs(int x)
    {
        for (auto i : graph[x])
        {
            if (vis[i] == false)
            {
                vis[i] = true;
                if (match[i] == 0 || dfs(match[i]))
                {
                    match[i] = x;
                    return true;
                }
            }
        }
        return false;
    }

    int hungarian()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            memset(vis, 0, sizeof(bool) * n);
            if (dfs(i))
                ans++;
        }
        return ans;
    }
}hgy;
```

#### Ho - Kashyap Algorithm

##### Algorithm

- 原理：沿 BFS 路径找增广路；
- 时间复杂度：$O(\sqrt{V} E)$

##### Template

```C++
struct HoKashyap
{
    // Find Maximum Matching on Unweighted Bitpartite Graph
    // Time Complexity: O(V^(1/2)E)
    int cntx, cnty; // Num of Set 1 && Set 2
    vector<int> graph[MAXN]; // Edge Set 1 to Set 2
    int matchx[MAXN], matchy[MAXN];
    int depx[MAXN], depy[MAXN]; // Depth
    int dep;
    bool vis[MAXN];

    void init()
    {
        memset(matchx, -1, sizeof(matchx));
        memset(matchy, -1, sizeof(matchy));
    }

    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
    }

    bool bfs()
    {
        queue<int> q;
        dep = INF;
        memset(depx, -1, sizeof(depx));
        memset(depy, -1, sizeof(depy));
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= cntx; ++i)
        {
            if (matchx[i] == -1)
            {
                q.push(i);
                depx[i] = 0;
            }
        }
        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            if (depx[now] > dep)
                break;
            for (int i = 0; i < graph[now].size(); ++i)
            {
                int nxt = graph[now][i];
                if (depy[nxt] == -1)
                {
                    depy[nxt] = depx[now] + 1;
                    if (matchy[nxt] == -1)
                        dep = depy[nxt];
                    else
                    {
                        depx[matchy[nxt]] = depy[nxt] + 1;
                        q.push(matchy[nxt]);
                    }
                }
            }
        }
        return dep != INF;
    }

    bool dfs(int now)
    {
        for (int i = 0; i < graph[now].size(); ++i)
        {
            int nxt = graph[now][i];
            if (!vis[nxt] && depy[nxt] == depx[now] + 1)
            {
                vis[nxt] = true;
                if(matchy[nxt] != -1 && depy[nxt] == dep)
                    continue;
                if(matchy[nxt] == -1 || dfs(matchy[nxt]))
                {
                    matchy[nxt] = now;
                    matchx[now] = nxt;
                    return true;
                }
            }
        }
        return false;
    }

    int hokashyap()
    {
        int ans = 0;
        while (bfs())
            for (int i = 1; i <= cntx; ++i)
                if (matchx[i] == -1 && dfs(i))
                    ans++;
        return ans;
    }
}hk;
```

### Maximum Weight Perfect Matching

#### Kuhn－Munkres Algorithm

##### Algorithm

- 顶标
- 相等子图
  - 对于某组可行顶标，如果其相等子图存在完美匹配，那么，该匹配就是原二分图的最大权完美匹配。

##### Template

```C++
struct KuhnMunkres
{
    // Bitpartite Graph (Perfect Matching's Maximum Matching)
    // add 0 weight Edge for Perfect Matching exsist
    // add -w weight Edge for Minimum Matching
    // add log(w) weight for Muiltiple Maximum Matching
    // Time Complexity: O(V^3)
    // index from 0 to n - 1
    // add Edge (u - 1, v - 1, w)
    int n;
    int cntx;
    int cnty;
    int pre[MAXN];    // 连接右集合的左点
    bool visx[MAXN];
    bool visy[MAXN];
    int lx[MAXN];
    int ly[MAXN];
    int g[MAXN][MAXN];
    int slack[MAXN];
    int matchx[MAXN];
    int matchy[MAXN];
    queue<int> q;
    int res;

    void init(int cntx, int cnty)
    {
        this->cntx = cntx;
        this->cnty = cnty;
        n = max(cntx, cnty);
        res = 0;
        for (int i = 0; i < n; ++i)
            fill(g[i], g[i] + n, -INF);
        memset(matchx, -1, sizeof(int) * n);
        memset(matchy, -1, sizeof(int) * n);
        fill(lx, lx + n, -INF);
    }

    void addEdge(int u, int v, int w)
    {
        // g[u][v] = max(0, w); // 负值还不如不匹配 因此设为 0不影响
        g[u][v] = max(g[u][v], w); // 考虑重边
    }

    bool check(int v)
    {
        visy[v] = true;
        if (matchy[v] != -1)
        {
            q.push(matchy[v]);
            visx[matchy[v]] = true; // in S
            return false;
        }
        // 找到新的未匹配点 更新匹配点 pre 数组记录着 非匹配边 上与之相连的点
        while (v != -1)
        {
            matchy[v] = pre[v];
            swap(v, matchx[pre[v]]);
        }
        return true;
    }

    void bfs(int i)
    {
        while (!q.empty())
            q.pop();
        q.push(i);
        visx[i] = true;
        while (true)
        {
            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (int v = 0; v < n; v++)
                {
                    if (!visy[v])
                    {
                        int delta = lx[u] + ly[v] - g[u][v];
                        if (slack[v] >= delta)
                        {
                            pre[v] = u;
                            if (delta)
                                slack[v] = delta;
                            else if (check(v))
                            // delta=0 代表有机会加入相等子图 找增广路
                            // 找到就 return 重建交错树
                                return;
                        }
                    }
                }
            }
            // 没有增广路 修改顶标
            int a = INF;
            for (int j = 0; j < n; j++)
                if (!visy[j])
                    a = min(a, slack[j]);
            for (int j = 0; j < n; j++)
            {
                if (visx[j]) // S
                    lx[j] -= a;
                if (visy[j]) // T
                    ly[j] += a;
                else // T'
                    slack[j] -= a;
            }
            for (int j = 0; j < n; j++)
                if (!visy[j] && slack[j] == 0 && check(j))
                    return;
        }
    }

    void solve()
    {
        // 初始顶标
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                lx[i] = max(lx[i], g[i][j]);
        for (int i = 0; i < n; i++)
        {
            memset(slack, 0x3f, sizeof(int) * n);
            memset(visx, false, sizeof(bool) * n);
            memset(visy, false, sizeof(bool) * n);
            bfs(i);
        }
        for (int i = 0; i < n; i++)
        {
            // if add extra Edge
            // if (g[i][matchx[i]] > 0)
                // res += g[i][matchx[i]];
            // else
                // matchx[i] = -1;
            res += g[i][matchx[i]];
        }
        cout << res << "\n";
        for (int i = 0; i < cnty; i++)
            cout << matchy[i] + 1 << " ";
        cout << "\n";
    }
}km;
```