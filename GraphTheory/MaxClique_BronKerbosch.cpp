/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-08 15:43:51
 * @FilePath            : /CodeShelf/GraphTheory/MaxClique_BronKerbosch.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Bron - Kerbosch Algorithm
 *  Search Maximum Clique in Undirected Graph
 *  Time Complexity: O(3^{N/3})
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 50 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct BronKerbosch {
    // Search Maximum Clique in Undirected Graph
    // Time Complexity: O(3^{N/3})
    bool graph[MAXN][MAXN]; // Undirected Graph
    int cnt[MAXN];          // cnt[i] >= i的最大团点数
    int group[MAXN];        // points in maxClique
    int pos[MAXN];          // 记录点的位置
    int res;                // 最大团的数目

    bool dfs(int now, int num) { // num 为已取的点数
        for (int i = now + 1; i <= n; i++) {
            if (cnt[i] + num <=
                res) // 剪枝，若取 i 但 cnt[i] + 已经取了的点数 < ans
                return false;
            if (graph[now][i]) { // 与当前团中元素比较，取 Non-N(i)
                int j;
                for (j = 0; j < num; j++)
                    if (!graph[i][pos[j]]) break;
                if (j ==
                    num) { // 若为空，则皆与 i 相邻，则此时将 i 加入到最大团中
                    pos[num] = i;
                    if (dfs(i, num + 1)) return true;
                }
            }
        }
        if (num > res) { // 每添加一个点最多使最大团数 +1,后面的搜索就没有意义了
            res = num;                     // 最大团中点的数目
            for (int i = 1; i <= num; i++) // 最大团的元素
                group[i] = pos[i - 1];
            return true;
        }
        return false;
    }

    void maxClique() {
        res = -1;
        for (int i = n; i >= 1; i--) { // 枚举所有点
            pos[0] = i;
            dfs(i, 1);
            cnt[i] = res;
        }
    }

} bk;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}