/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/MathTheory/Polynomial_FWT_Subset.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Fast Walsh-Hadamard Transform (Subset Convolution)
 *  SOS DP based subset convolution
 *  Time Complexity: O(N * 2^N)
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 20;

struct SubsetConvolution {
    int n;
    int sz;

    void init(int _n) {
        n = _n;
        sz = 1 << n;
    }

    // SOS DP: compute sum over subsets
    void sos(vector<int> &f, bool inv) {
        for (int i = 0; i < n; ++i)
            for (int mask = 0; mask < sz; ++mask)
                if (mask >> i & 1) {
                    if (!inv) f[mask] = (f[mask] + f[mask ^ (1 << i)]) % MOD;
                    else f[mask] = (f[mask] - f[mask ^ (1 << i)] + MOD) % MOD;
                }
    }

    // subset convolution: h[s] = sum_{a subset of s} f[a] * g[s\a]
    vector<int> subsetConv(vector<int> f, vector<int> g) {
        // group by popcount
        vector<vector<int>> F(n + 1, vector<int>(sz));
        vector<vector<int>> G(n + 1, vector<int>(sz));
        for (int mask = 0; mask < sz; ++mask) {
            int pc = __builtin_popcount(mask);
            F[pc][mask] = f[mask];
            G[pc][mask] = g[mask];
        }
        for (int i = 0; i <= n; ++i) {
            sos(F[i], false);
            sos(G[i], false);
        }
        vector<vector<int>> H(n + 1, vector<int>(sz));
        for (int mask = 0; mask < sz; ++mask)
            for (int i = 0; i <= n; ++i)
                for (int j = 0; j <= i; ++j)
                    H[i][mask] = (H[i][mask] + 1LL * F[j][mask] * G[i - j][mask]) % MOD;
        for (int i = 0; i <= n; ++i) sos(H[i], true);
        vector<int> res(sz);
        for (int mask = 0; mask < sz; ++mask)
            res[mask] = H[__builtin_popcount(mask)][mask];
        return res;
    }
} fwt;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    fwt.init(n);
    vector<int> a(1 << n), b(1 << n);
    for (int i = 0; i < (1 << n); ++i) cin >> a[i];
    for (int i = 0; i < (1 << n); ++i) cin >> b[i];
    auto c = fwt.subsetConv(a, b);
    for (int i = 0; i < (1 << n); ++i)
        cout << c[i] << " \n"[i + 1 == (1 << n)];
    return 0;
}
