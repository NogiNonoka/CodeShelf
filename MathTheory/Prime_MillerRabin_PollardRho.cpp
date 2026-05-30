/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/MathTheory/Prime_MillerRabin_PollardRho.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Miller-Rabin Primality Test + Pollard Rho Factorization
 *  Time Complexity: O(N^(1/4)) expected
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

int qmul(int a, int b, int mod) {
    int res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

int qpow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) res = qmul(res, a, mod);
        a = qmul(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool millerRabin(int n) {
    if (n < 3) return n == 2;
    if (n % 2 == 0) return false;
    int d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, ++s;
    // Bases sufficient for n < 2^64
    int bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (int a : bases) {
        if (a % n == 0) continue;
        int x = qpow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int r = 1; r < s; ++r) {
            x = qmul(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

int pollardRho(int n) {
    if (n % 2 == 0) return 2;
    static std::mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        int c = uniform_int_distribution<int>(1, n - 1)(rng);
        int x = uniform_int_distribution<int>(0, n - 1)(rng);
        int y = x;
        int d = 1;
        auto f = [&](int v) { return (qmul(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = __gcd(abs(x - y), n);
        }
        if (d != n) return d;
    }
}

void factor(int n, vector<int> &fac) {
    if (n == 1) return;
    if (millerRabin(n)) { fac.push_back(n); return; }
    int d = pollardRho(n);
    factor(d, fac);
    factor(n / d, fac);
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> fac;
    factor(n, fac);
    sort(fac.begin(), fac.end());
    for (int i = 0; i < (int)fac.size(); ++i)
        cout << fac[i] << " \n"[i + 1 == (int)fac.size()];
    return 0;
}
