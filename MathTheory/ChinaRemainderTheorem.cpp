/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-18 21:25:12
 * @FilePath            : /CodeShelf/MathTheory/ChinaRemainderTheorem.cpp
 * @LastEditTime        : 2021-03-20 18:21:48
 * @Forward Declaration : Quick Mul & Extended GCD
 * @Discription         : 
 *  Solve Congruent Liner Equation Group: x = a (mod p)
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

int qmul(int a, int b, int p)
{
    // Calc a * b % p
    int ans = 0;
    for (; b; b >>= 1, a = (a << 1) % p)
        if (b & 1)
            ans = (ans + a) % p;
    return ans;
}

int exgcd(int a, int b, int &x, int &y)
{
    // Solve Congruent Liner Equation: ax + by == gcd(a, b), ax = gcd(a, b) (mod b)
    // Minimum Positive Integer Solution: t = b / gcd(a, b), x = (x % t + t) % t
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int inv(int a, int p)
{
    // Calc Inversion a^{-1} (mod p)
    int x, y;
    int d = exgcd(a, p, x, y);
    return d == 1 ? (x % p + p) % p : -1;
}

int crt(vector<int> &a, vector<int> &p)
{
    // Solve Congruent Liner Equation Group: x = a (mod p)
    int ans = 0, m = 1;
    for (int i = 0; i < p.size(); ++i)
        m *= p[i];
    for (int i = 0; i < p.size(); ++i)
    {
        int n = m / p[i];
        int x = inv(n, p[i]); //Solve nx = 1 (mod p) based on exgcd
        ans = (ans + qmul(qmul(n, x, m), (a[i] % m + m) % m, m)) % m;
        // ans = (ans + n * x % m * a[i] % m) % m;
    }
    ans = (ans % m + m) % m;
    return ans;
}

signed main(void)
{
    // Problem ID: Luogu P3868
    // Link: https://www.luogu.com.cn/problem/P3868
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int k;
    vector<int> a;
    vector<int> p;
    cin >> k;
    a.resize(k);
    p.resize(k);
    for (int i = 0; i < k; ++i)
    {
        cin >> a[i];
    }
    for (int i = 0; i < k; ++i)
    {
        cin >> p[i];
    }
    int ans = crt(a, p);
    cout << ans << endl;
    return 0;
}