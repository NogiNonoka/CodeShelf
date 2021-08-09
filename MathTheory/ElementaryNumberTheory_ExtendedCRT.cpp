/*
 * @Author              : NogiNonoka
 * @Date                : 2021-08-07 18:03:36
 * @FilePath            : /CodeShelf/MathTheory/ElementaryNumberTheory_ExtendedCRT.cpp
 * @Forward Declaration : Quick Mul & Extended GCD
 * @Discription         : 
 * Extended China Remainder Theorm
 * Solve Congruent Liner Equation Group: x = a (mod p), GCD(p) != 1
 */

#include <bits/stdc++.h>

using namespace std;
#define int long long
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

int qMul(int a, int b, int p) {
    // Calc a * b % p
    int ans = 0;
    for (; b; b >>= 1, a = (a << 1) % p)
        if (b & 1) ans = (ans + a) % p;
    return ans;
}

int exgcd(int a, int b, int& x, int& y) {
    // Solve Congruent Liner Equation: ax + by == gcd(a, b), ax = gcd(a, b) (mod b)
    // Minimum Positive Integer Solution: t = b / gcd(a, b), x = (x % t + t) % t
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int excrt(vector<int> &a, vector<int> &p) {
    // if no ans, return -1
    int a0 = a[0], p0 = p[0];
    int a1, p1;
    int x, y;
    for (int i = 1; i < a.size(); ++i) {
        a1 = a[i];
        p1 = p[i];
        int c = ((a1 - a0) % p1 + p1) % p1;
        int d = exgcd(p0, p1, x, y);
        if (c % d) return -1;
        // x = x * (c / d) % (p1 / d);
        x = qMul(x, c / d, p1 / d);
        a0 = x * p0 + a0;
        p0 = p0 / d * p1; // lcm(p0, p1)
        a0 = (a0 % p0 + p0) % p0;
    }
    return a0;
}


signed main(void) {
    // Problem ID: Luogu P4777
    // Link: https://www.luogu.com.cn/problem/P4777
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i] >> a[i];   
    }
    cout << excrt(a, p) << endl;
    return 0;
}