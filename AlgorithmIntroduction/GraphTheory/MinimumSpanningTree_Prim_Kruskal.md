---
title: "[GraphTheory]Prim&&Kruskal"
tags: "Algorithm"
---

## 图论——最小生成树 (MST)

[TOC]

* * *

### Kruskal

#### 前置知识

1.  图
    -   连通图：在**无向图**中，若任意两个顶点都有路径相通，则称该无向图为连通图。
    -   强连通图：在**有向图**中，若任意两个顶点都有路径相通，则称该有向图为强连通图。
    -   连通网：在连通图中，若图的边具有一定的意义，每一条边都对应着一个数，称为权；权代表着连接连个顶点的代价，称这种连通图叫做连通网。
    -   生成树：一个连通图的生成树是指一个连通子图，它含有图中全部n个顶点，但只有足以构成一棵树的n-1条边。一颗有n个顶点的生成树 **有且仅有n-1条边**，如果生成树中再添加一条边，则必定成环。
    -   最小生成树：在连通网的所有生成树中，所有**边的代价和最小**的生成树，称为最小生成树。

2.  并查集
    -   **路径压缩**

```C++
int parent[MAXN];
//最小生成树中所连通的的点集
void init_parent(int n)
{
    for (int i = 1; i <= n; ++i)
        parent[i] = i;
}
//初始化每一个点的父亲为他本身
int find_parent(int x)
{
    if (parent[x] == x)
        return x;
    else
    {
        parent[x] = find_parent(parent[x]);
    }
    return parent[x];
}
//找爸爸 路径压缩
bool check_unicom(int x, int y)
{
    return find_parent(x) == find_parent(y);
}
//判断连通性
void merge(int x, int y)
{
    parent[find_parent(x)] = find_parent(y);
}
//将两个点连通
```

#### 算法知识

1.  本质：**加边法** **贪心** 按边权大小排序
2.  复杂度：$O(E\log_2 E)$ 仅和边数量有关
3.  解决问题：**稀疏图**上找最小生成树

#### 算法模板

```C++
struct EDGE
{
    int fr, to;
    int val;
    bool operator<(const EDGE &b) const
    {
        return val < b.val;
    }
    //重载运算符按从小到大的顺序对边排序
} edge[MAXE];
//稀疏图使用结构体存边
int kruskal()
{
    int sum = 0;
    init_parent(n);
    sort(edge + 1, edge + m + 1);
    for (int i = 1; i <= m; ++i)
    {
        if (!check_unicom(edge[i].fr, edge[i].to))
        {
            merge(edge[i].fr, edge[i].to);
            sum += edge[i].val;
        }
        //判断连通性 若边起点与终点不连通则不在最小生成树内 将其加入最小生成树
    }
    return sum;
}
```

* * *

### Prim

#### 算法知识

1.  本质：**加点法** 每次加入点集内与点集外任一点最小的权值所连成的边，将点加入点集`vis[i]`，并更新点集内的点到点集外的点的权值`dis[i]`。
2.  复杂度：$O(V^2)$
3.  解决问题：**稠密图**上找最小生成树

#### 算法模板

```C++
int graph[MAXN][MAXN];
int dis[MAXN];
bool vis[MAXN];

int prim()
{
    int now = 1;
    //选初始的点
    int sum = 0;
    vis[now] = true;
    for (int i = 1; i <= n; ++i)
    {
        dis[i] = graph[now][i];
    }
    for (int i = 2; i <= n; ++i)
    {
        int min = INF;
        for (int nxt = 1; nxt <= n; ++nxt)
        {
            if (!vis[nxt] && dis[nxt] < min)
            {
                now = nxt;
                min = dis[nxt];
            }
            //若不在点集内 则找到与点击内点所连边权值最小的点
        }
        vis[now] = true;
        //加入点集
        sum += min;
        for (int j = 1; j <= n; ++j)
        {
            if (!vis[j] && graph[now][j] < dis[j])
            {
                dis[j] = graph[now][j];
            }
        }
        //更新点集外的点到点集内点的权值
    }
}
```

* * *
