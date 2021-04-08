/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-18 16:58:46
 * @FilePath            : /CodeShelf/MathTheory/ElementaryNumberTheory_ExtendedGCD.cpp
 * @LastEditTime        : 2021-03-27 14:45:12
 * @Forward Declaration : None
 * @Discription         : 
 *  Solve Congruent Liner Equation: ax + by == gcd(a, b), ax = gcd(a, b) (mod b)
 *  Minimum Positive Integer Solution: t = b / gcd(a, b), x = (x % t + t) % t
 *  Calc Inversion a^{-1} (mod p)
 */

#include <iostream>
#include <algorithm>
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

int exgcd(int a, int b, int &x, int &y)
{
    // Solve Congruent Liner Equation: ax + by == gcd(a, b), ax = gcd(a, b) (mod b)
    // Minimum Positive Integer Solution: t = b / gcd(a, b), x = (x % t + t) % t
    if (b == 0)
    {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int inv(int a, int p)
{
    // Calc Inverse Element a^{-1} (mod p)
    int x, y;
    int d = exgcd(a, p, x, y);
    return d == 1 ? (x % p + p) % p : -1;
}

signed main(void)
{
    // Problem ID: POJ 2142
    // Link: http://poj.org/problem?id=2142
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int a, b, c;
    while (cin >> a >> b >> c && a * b * c)
    {
        int x1, y1;
        int d1 = exgcd(a, b, x1, y1);
        int t1 = b / d1;
        x1 = x1 * c / d1;
        x1 = (x1 % t1 + t1) % t1;
        y1 = (c - a * x1) / b;
        y1 = abs(y1);
        int x2, y2;
        int d2 = exgcd(b, a, x2, y2);
        int t2 = a / d2;
        x2 = x2 * c / d2;
        x2 = (x2 % t2 + t2) % t2;
        y2 = (c - b * x2) / a;
        y2 = abs(y2);
        swap(x2, y2);
        if (x1 + y1 < x2 + y2)
            cout << x1 << " " << y1 << endl;
        else
            cout << x2 << " " << y2 << endl;
    }
    return 0;
}