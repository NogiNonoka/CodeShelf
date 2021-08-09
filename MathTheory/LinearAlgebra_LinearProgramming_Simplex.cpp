/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-23 08:03:09
 * @FilePath            : /CodeShelf/MathTheory/LinearAlgebra_LinearProgramming_Simplex.cpp
 * /CodeShelf/MathTheory/LinearAlgebra_LinearProgramming_Simplex.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Simplex (Linear Programming)
 *  a[m]: z_max = \sum (a_mj * xj)
 *  a[i]: \sum (a_ij * xj) = a[i][n]
 *  Time Complexity: O(Exponential)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 500 + 7;
const int MAXM = 500 + 7;
// const int MAXE = ;
// const int MOD = ;
const double INF = 1e100;
const double eps = 1e-10;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Simplex {
    // Simplex for Standard Linear Programming
    // a[m]: z_max = \sum (a_mj * xj)
    // a[i]: \sum (a_ij * xj) = a[i][n]
    // Time Complexity: O(Exponential)
    int n;                // num of variables
    int m;                // NUM OF limitations
    double a[MAXM][MAXN]; // matrix for limitations and target
    int bvar[MAXM];       // basic variables, |bv| = m
    int nvar[MAXN];       // nonbasic variables, |nv| = n
    double ans;
    double x[MAXN];

    void pivot(int r, int c) {
        swap(bvar[r], nvar[c]);
        a[r][c] = 1 / a[r][c];
        for (int j = 0; j <= n; ++j)
            if (j != c) a[r][j] *= a[r][c];
        for (int i = 0; i <= m; ++i) {
            if (i != r) {
                for (int j = 0; j <= n; ++j)
                    if (j != c) a[i][j] -= a[i][c] * a[r][j];
                a[i][c] = -a[i][c] * a[r][c];
                ;
            }
        }
    }

    bool feasible() {
        while (true) {
            int r, c;
            double p = INF;
            for (int i = 0; i < m; ++i)
                if (a[i][n] < p) p = a[r = i][n];
            if (p > -eps) return true;
            p = 0;
            for (int j = 0; j < n; ++j)
                if (a[r][j] < p) p = a[r][c = j];
            if (p < -eps) return false;
            p = a[r][n] / a[r][c];
            for (int i = r + 1; i < m; ++i) {
                if (a[i][c] > eps) {
                    double v = a[i][n] / a[i][c];
                    if (v < p) r = i, p = v;
                }
            }
            pivot(r, c);
        }
    }

    int simplex(int n, int m) {
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; ++i) nvar[i] = i;
        for (int i = 0; i < m; ++i) bvar[i] = n + i;
        if (!feasible()) return 0; // no solution
        while (true) {
            int r, c;
            double p = 0;
            for (int j = 0; j < n; ++j)
                if (a[m][j] > p) p = a[m][c = j];
            if (p < eps) {
                for (int i = 0; i < n; ++i)
                    if (nvar[i] < n) x[nvar[i]] = 0;
                for (int i = 0; i < m; ++i)
                    if (bvar[i] < n) x[bvar[i]] = a[i][n];
                ans = -a[m][n];
                return 1;
            }
            p = INF;
            for (int i = 0; i < m; ++i) {
                if (a[i][c] > eps) {
                    double v = a[i][n] / a[i][c];
                    if (v < p) r = i, p = v;
                }
            }
            if (p == INF) return -1; // unbounded, z_max = INF
            pivot(r, c);
        }
    }
} spx;

signed main(void) {
    // Problem ID: UVA 10498
    // Link:
    // https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1439
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < n; ++i) cin >> spx.a[m][i];
        spx.a[m][n] = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j <= n; ++j) cin >> spx.a[i][j];
        if (spx.simplex(n, m) == 1)
            printf("Nasa can spend %d taka.\n", (int)ceil(spx.ans * m));
    }
    return 0;
}