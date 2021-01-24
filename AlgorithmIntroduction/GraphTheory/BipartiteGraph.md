## 图论——二分图 (Bipartite Graph)

[TOC]

---

### Hungary 算法

#### 前置知识

1. 二分图：顶点集 $V$ 可分割为两个**互不相交**的子集，并且图中每条边依附的两个顶点都分属于这两个互不相交的子集，两个子集内的顶点不相邻。
   - 判定定理：一个图是二分图当且仅当没有长度为奇数的圈。
2. 二分图匹配
   - 匹配：任意两条边都没有公共顶点的边的集合称为匹配。
   - 最大匹配：包含边的个数最多的一组匹配。
   - 完美匹配：如果一个匹配中，图中的**每个顶点**都和图中某条边相关联，则称此匹配为**完全匹配**，也称作**完备匹配**。
   - 增广路：一个连接两个**非匹配点**的路径 $path$， 使得非匹配边和匹配边在 $path$ 上交替出现(第一条边和最后一条边都是未匹配边)，称 $path$ 是一个增广路。
     - 增广路的长度为奇数。
     - 不属于匹配的边比匹配中的边多一条。
     - 对增广路进行取反操作可以得到一个更大的匹配 $M'$。
     - 若 $M$ 为图 $G$ 的最大匹配当且仅当不存在相对于 $M$ 的增广路。

#### 算法知识

1. 本质：$DFS$ 找增广路，求二分图最大匹配
2. 时间复杂度 $O(VE)$

#### 算法模板

```cpp
struct Hungary
{
    int n, m; // Num of Set 1 && 2
    bool graph[MAXN][MAXN]; // Adj Matrix
    int lnk[MAXN];
    bool vis[MAXN];

    void init()
    {
        memset(graph, 0, sizeof(graph));
        memset(lnk, 0, sizeof(lnk));
        memset(vis, 0, sizeof(vis));
    }

    bool dfs(int x)
    {
        for (int i = 1; i <= m; ++i)
        {
            if (graph[x][i] && !vis[i])
            {
                vis[i] = true;
                if (lnk[i] == 0 || dfs(lnk[i]))
                {
                    lnk[i] = x;
                    return true;
                }
            }
        }
        return false;
    }

    int hungary()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            memset(vis, 0, sizeof(vis));
            if (dfs(i))
                ans++;
        }
        return ans;
    }
}hgy;
```

### Ho - Kashyap 算法

#### 算法知识

1. 原理：沿 $BFS$ 路径找增广路
2. 时间复杂度：$O(\sqrt{V} E)$

#### 算法模板

```cpp
struct HK
{
    int cntx, cnty; // Num of Set 1 && Set 2
    vector<int> graph[MAXN]; // Edge Set 1 to Set 2
    int lnkx[MAXN], lnky[MAXN];
    int depx[MAXN], depy[MAXN]; // Depth
    bool vis[MAXN];
    int dep;

    bool bfs()
    {
        queue<int> q;
        dep = INF;
        memset(depx, -1, sizeof(depx));
        memset(depy, -1, sizeof(depy));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= cntx; ++i)
        {
            if (lnkx[i] == -1)
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
                    if (lnky[nxt] == -1)
                        dep = depy[nxt];
                    else
                    {
                        depx[lnky[nxt]] = depy[nxt] + 1;
                        q.push(lnky[nxt]);
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
                if(lnky[nxt] != -1 && depy[nxt] == dep)
                    continue;
                if(lnky[nxt] == -1 || dfs(lnky[nxt]))
                {
                    lnky[nxt] = now;
                    lnkx[now] = nxt;
                    return true;
                }
            }
        }
        return false;
    }

    int Ho_Kashyap()
    {
        int ans = 0;
        memset(lnkx, -1, sizeof(lnkx));
        memset(lnky, -1, sizeof(lnky));
        while (bfs())
        {
            for (int i = 1; i <= cntx; ++i)
            {
                if (lnkx[i] == -1 && dfs(i))
                    ans++;
            }
        }
        return ans;
    }
}hk;
```

### Kuhn－Munkres 算法

#### 算法知识

1. 解决问题：求二分图完备匹配下的最大权匹配。