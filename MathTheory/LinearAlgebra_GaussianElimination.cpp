/*
 * @Author              : beta_dust, Tilnel, NogiNonoka
 * @Date                : 2021-03-22 18:57:06
 * @FilePath            : /CodeShelf/MathTheory/LinearAlgebra_GaussianElimination.cpp
 * @LastEditTime        : 2021-03-22 22:14:04
 * @Forward Declaration : None
 * @Discription         : 
 *  Gaussian Elimination
 *  Calc n * n matrix's solution
 *  Time Complexity: O(N^2)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
#define endl "\n"
const int MAXN = 103;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Gauss
{
    int n; // n * n  matrix
    double matrix[MAXN][MAXN];

    void input()
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n + 1; ++j)
            {
                scanf("%lf", &matrix[i][j]);
            }
        }
    }

    bool gauss()
    {
        // Gaussian Elimination
        // Calc n * n matrix's solution
        // Time Complexity: O(N^2)
        for (int i = 1; i <= n; ++i)
        {
            int maxi = i;
            for (int j = i + 1; j <= n; ++j)
            {
                if (fabs(matrix[j][i]) > fabs(matrix[maxi][i]))
                    maxi = j;
            }
            for (int j = 1; j <= n + 1; ++j)
                swap(matrix[i][j], matrix[maxi][j]);
            if (!matrix[i][i])
                return false;
            // if (!matrix[i][i] && matrix[i][n + 1])
            //     return false;
            for (int j = 1; j <= n; ++j)
            {
                if (j != i)
                {
                    double tmp = matrix[j][i] / matrix[i][i];
                    for (int k = i + 1; k <= n + 1; ++k)
                        matrix[j][k] -= matrix[i][k] * tmp;
                }
            }
        }
        // Calc determinant
        // double det = 1;
        // for (int i = 1; i <= n; i++)
        // {
        //     det *= a[i][i];
        // }
        return true;
    }

    void output()
    {
        for (int i = 1; i <= n; ++i)
        {
            printf("%.2lf\n", matrix[i][n + 1] / matrix[i][i]);
        }
    }
} ge;

signed main(void)
{
    // Problem: Luogu P3389
    // Link: https://www.luogu.com.cn/problem/P3389
    ge.input();
    if (ge.gauss())
    {
        ge.output();
    }
    else
    {
        printf("No Solution\n");
    }
    return 0;
}