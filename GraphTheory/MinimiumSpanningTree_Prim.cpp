/*
 * @Author              : NogiNonoka
 * @Date                : 2020-11-23 10:45:45
 * @FilePath            : /CodeShelf/GraphTheory/MinimiumSpanningTree_Prim.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Minimum Spanning Tree
 *  Prim
 *  Time Complexity: O(V^2)
 */

#include <cstdio>
#include <cstring>
#include <iostream>

const int MAXN = 1e3 + 7;
const int INF = 0x3f3f3f3f;

int n;                 // num of Nodes
int graph[MAXN][MAXN]; // Matrix for graph
int dis[MAXN];         // each Edge's val in MST
bool vis[MAXN];        // flg for Node in MST

void prim(int n) {
    // Minimum Spanning Tree
    // Time Complexity: O(V^2)
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    int now = 1;
    vis[now] = true;
    dis[now] = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i] && graph[now][i] < dis[i]) dis[i] = graph[now][i];
    for (int t = 2; t <= n; ++t) {
        int nxt = 0;
        int nxtDis = INF;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && nxtDis > dis[i]) {
                nxt = i;
                nxtDis = dis[i];
            }
        }
        vis[nxt] = true;
        for (int i = 1; i <= n; ++i)
            if (!vis[i] && graph[nxt][i] < dis[i]) dis[i] = graph[nxt][i];
    }
}


int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    return 0;
}