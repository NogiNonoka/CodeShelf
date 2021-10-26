/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-20 18:17:28
 * @FilePath            : /CodeShelf/MathTheory/Preparation_QuickMul.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Quick Mul
 *  Calc a * b % p
 *  Especially a * b may larger than max long long
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

int fuckMul(int a, int b, int p = MOD) {
    // Calc a * b % p
    int ans = 0;
    for (; b; b >>= 1, a = (a << 1) % p)
        if (b & 1) ans = (ans + a) % p;
    return ans;
}

int lightMul(int a, int b, int p) {
    return (a * b - (int)floor((long double)a * (long double)b / (long double)p + 0.5 ) * p + p) % c;
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}