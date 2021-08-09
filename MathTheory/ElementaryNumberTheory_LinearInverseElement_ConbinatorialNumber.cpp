/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-20 18:15:30
 * @FilePath            : /CodeShelf/MathTheory/ElementaryNumberTheory_LinearInverseElement_ConbinatorialNumber.cpp
 * /CodeShelf/MathTheory/ElementaryNumberTheory_LinearInverseElement_ConbinatorialNumber.cpp
 * @Forward Declaration : None
 * @Discription         :
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = ;
// const int MAXE = ;
const int MOD = 1e9 + 7;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int fac[MAXN], inv[MAXN], facinv[MAXN];

void getInv(int n, int* inv, int p = MOD) {
    inv[1] = 1;
    for (int i = 2; i < n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
}

void getFac(int n, int* fac, int* facinv, int p = MOD) {
    fac[0] = 1;
    for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i % p;
    // Factorial
    facinv[0] = 1;
    for (int i = 1; i < n; i++) facinv[i] = inv[i] * facinv[i - 1] % p;
    // Factorials' Muiltiplicative Inverse
}

int C(int n, int m, int p = MOD) {
    if (m > n) return 0;
    return fac[n] * facinv[m] % p * facinv[n - m] % p;
}
// C_n^m

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}