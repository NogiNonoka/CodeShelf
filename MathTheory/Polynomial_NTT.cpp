/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/MathTheory/Polynomial_NTT.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Number Theoretic Transform
 *  Mod: 998244353, Primitive Root: 3
 *  Time Complexity: O(NlogN)
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G = 3;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void ntt(vector<int> &a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = qpow(G, (MOD - 1) / len);
        if (inv) wlen = qpow(wlen, MOD - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int u = a[i + j];
                int v = 1LL * a[i + j + len / 2] * w % MOD;
                a[i + j] = u + v < MOD ? u + v : u + v - MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
                w = 1LL * w * wlen % MOD;
            }
        }
    }
    if (inv) {
        int n_inv = qpow(n, MOD - 2);
        for (int &x : a) x = 1LL * x * n_inv % MOD;
    }
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * b[i] % MOD;
    ntt(a, true);
    while ((int)a.size() > 1 && a.back() == 0) a.pop_back();
    return a;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 0; i <= n; ++i) cin >> a[i];
    for (int i = 0; i <= m; ++i) cin >> b[i];
    vector<int> c = multiply(a, b);
    for (int i = 0; i < (int)c.size(); ++i)
        cout << c[i] << " \n"[i + 1 == (int)c.size()];
    return 0;
}
