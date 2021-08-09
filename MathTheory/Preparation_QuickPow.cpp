/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-20 17:04:50
 * @FilePath            : /CodeShelf/MathTheory/Preparation_qPow.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Quick Pow
 * Calc a ^ b % MOD
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
// const int MAXN = ;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int qPow(int a, int b, int p = MOD) {
    // Calc a ^ b % p
    int ans = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) ans = ans * a % p;
    return ans;
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}