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
#define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e5 + 7;
// const int MAXE = ;
const int MOD = 1e9 + 7;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int fact[MAXN], inv[MAXN], factInv[MAXN];

void getInv(int n = MAXN, int p = MOD) {
    inv[0] = 0;
    inv[1] = 1;
    for (int i = 2; i < n; i++) inv[i] = (p - p / i) * inv[p % i] % p;
}

void getFact(int n = MAXN, int p = MOD) {
    // Factorial
    fact[0] = 1;
    for (int i = 1; i < n; i++) fact[i] = fact[i - 1] * i % p;
    // Factorials' Muiltiplicative Inverse
    factInv[0] = 1;
    for (int i = 1; i < n; i++) factInv[i] = inv[i] * factInv[i - 1] % p;
}

int C(int n, int m, int p = MOD) {
    // C_n^m
    if (m > n) return 0;
    return fact[n] * factInv[m] % p * factInv[n - m] % p;
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}