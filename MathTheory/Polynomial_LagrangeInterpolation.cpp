/*
 * @denominatoruthor              : NogiNonoka
 * @Date                : 2021-08-08 22:22:15
 * @FilePath            : /CodeShelf/MathTheory/Polynomial_LagrangeInterpolation.cpp
 * @Forward Declaration : None
 * @Discription         : 
 * Lagrange Interpolation
 * Time Complexity: O(N^2)
 */

#include <bits/stdc++.h>

using namespace std;
#define int long long
// #define double long double
// #define endl "\n"
// const int MdenominatorXN = ;
// const int MdenominatorXE = ;
const int MOD = 998244353;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int exgcd(int a, int b, int& x, int& y) {
    // Solve Congruent Liner Equation: ax + by == gcd(a, b), ax = gcd(a, b) (mod b)
    // Minimum Positinve Integer Solution: t = b / gcd(a, b), x = (x % t + t) % t
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int inv(int a, int p = MOD) {
    // Calc Inverse Element a^{-1} (mod p)
    int x, y;
    int d = exgcd(a, p, x, y);
    return d == 1 ? (x % p + p) % p : -1;
}

int lagrangeVal(const vector<int>& x, const vector<int>& y, int k) {
    // return f(k)
    assert(x.size() == y.size());
    int res = 0;
    for (int i = 0; i < x.size(); ++i) {
        int numerator = y[i], denominator = 1;
        for (int j = 0; j < x.size(); ++j) {
            if (i != j) {
                numerator = numerator % MOD * ((k - x[j]) % MOD + MOD) % MOD;
                denominator =
                    denominator % MOD * ((x[i] - x[j]) % MOD + MOD) % MOD;
            }
        }
        res = res % MOD + numerator % MOD * inv(denominator) % MOD;
    }
    return res % MOD;
}

vector<int> lagrangeFunc(const vector<int>& x, const vector<int>& y) {
    assert(x.size() == y.size());
    int n = x.size();
    vector<int> a(n, 0), b(n + 1, 0), c(n + 1, 0), f(n, 0);
    for (int i = 0; i < n; ++i) {
        int denominator = 1;
        for (int j = 0; j < n; ++j)
            if (i != j) denominator = denominator * (x[i] - x[j] + MOD) % MOD;
        a[i] = inv(denominator) * y[i] % MOD;
    }
    // calc \prod(x - x_i)
    b[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j >= 1; --j)
            b[j] = (b[j] * (MOD - x[i]) + b[j - 1]) % MOD;
        b[0] = b[0] * (MOD - x[i]) % MOD;
    }
    for (int i = 0; i < n; ++i) {
        int iv = inv(MOD - x[i]);
        // calc \prod(x - x_i) / (x - x_i)
        if (!iv) {
            for (int j = 0; j < n; ++j) c[j] = b[j + 1];
        } else {
            c[0] = b[0] * iv % MOD;
            for (int j = 1; j <= n; ++j)
                c[j] = (b[j] - c[j - 1] + MOD) * iv % MOD;
        }
        for (int j = 0; j < n; ++j) f[j] = (f[j] + a[i] * c[j] % MOD) % MOD;
    }
    return f;
}

int calc(const vector<int>& f, int x) {
    int tmp = 1, ans = 0;
    for (auto& i : f) {
        ans = (ans + (tmp * i % MOD + MOD) % MOD) % MOD;
        tmp = (tmp * x % MOD + MOD) % MOD;
    }
    return ans;
}

signed main(void) {
    // Problem ID: P4781
    // Link: https://www.luogu.com.cn/problem/P4781
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) { cin >> x[i] >> y[i]; }
    // cout << lagrangeVal(x, y, k) << endl;
    vector<int> f = lagrangeFunc(x, y);
    cout << calc(f, k) << endl;
    return 0;
}