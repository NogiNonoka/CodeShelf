/*
 * @Author              : beta_dust, NogiNonoka
 * @Date                : 2021-03-22 20:52:45
 * @FilePath            : /CodeShelf/DataStructure/SparseTable.cpp
 * @LastEditTime        : 2021-04-09 18:29:25
 * @Forward Declaration : None
 * @Discription         : 
 *  Sparse Table
 *  Base on Binary Increase
 *  Query Maximum Number in range [l, r]
 *  Time Complexity: Pre O(NlogN) Query O(1)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e6 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct SparseTable
{
    // Query Maximum Number in range [l, r]
    // Time Complexity: Pre O(NlogN) Query O(1)
    int n;
    int st[MAXN][23];

    void input()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &st[i][0]);
        }
    }

    void pre()
    {
        for (int j = 1; j <= 21; ++j)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]); 
            }
        }
    }

    int query(int l, int r)
    {
        int k = log2(r - l + 1);
        return max(st[l][k], st[r -  (1 << k) + 1][k]);
        // can't change to [l + (1 << k)][k]
        // [l, l + 2 ^ k - 1] + [r - 2 ^ k + 1, r] != [l, r]
    }
} stable;

signed main(void)
{
    // Problem ID: Luogu P3865
    // Link: https://www.luogu.com.cn/problem/P3865
    int n, q;
    scanf("%d%d", &n, &q);
    stable.n = n;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &stable.st[i][0]);
    stable.pre();
    int l, r;
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d%d", &l, &r);
        printf("%d\n", stable.query(l, r));
    }
    return 0;
}