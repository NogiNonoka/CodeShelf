/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/MathTheory/BerlekampMassey.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Berlekamp-Massey Algorithm
 *  Find shortest linear recurrence from sequence
 *  Time Complexity: O(N^2)
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9 + 7;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

struct BerlekampMassey {
    vector<int> bm(vector<int> s) {
        vector<int> C(1, 1), B(1, 1);
        int L = 0, m = 1, b = 1;
        for (int n = 0; n < (int)s.size(); ++n) {
            int d = 0;
            for (int i = 0; i <= L; ++i)
                d = (d + C[i] * s[n - i]) % MOD;
            if (d == 0) {
                ++m;
            } else if (2 * L <= n) {
                vector<int> T = C;
                int coef = d * qpow(b, MOD - 2) % MOD;
                if (C.size() < B.size() + m) C.resize(B.size() + m);
                for (int i = 0; i < (int)B.size(); ++i)
                    C[i + m] = (C[i + m] - coef * B[i] % MOD + MOD) % MOD;
                L = n + 1 - L;
                B = T;
                b = d;
                m = 1;
            } else {
                int coef = d * qpow(b, MOD - 2) % MOD;
                if (C.size() < B.size() + m) C.resize(B.size() + m);
                for (int i = 0; i < (int)B.size(); ++i)
                    C[i + m] = (C[i + m] - coef * B[i] % MOD + MOD) % MOD;
                ++m;
            }
        }
        C.erase(C.begin());
        for (int &x : C) x = (MOD - x) % MOD;
        return C;
    }

    vector<int> combine(vector<int> a, vector<int> b, vector<int> rec) {
        int k = rec.size();
        vector<int> res(k * 2);
        for (int i = 0; i < k; ++i)
            for (int j = 0; j < k; ++j)
                res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
        for (int i = 2 * k - 2; i >= k; --i)
            for (int j = 1; j <= k; ++j)
                res[i - j] = (res[i - j] + res[i] * rec[j - 1]) % MOD;
        res.resize(k);
        return res;
    }

    int linearRecurrence(vector<int> init, vector<int> rec, int n) {
        int k = rec.size();
        if (n < k) return init[n];
        vector<int> pol(k), e(pol);
        pol[0] = e[1] = 1;
        --n;
        while (n) {
            if (n & 1) pol = combine(pol, e, rec);
            e = combine(e, e, rec);
            n >>= 1;
        }
        int res = 0;
        for (int i = 0; i < k; ++i)
            res = (res + pol[i] * init[i]) % MOD;
        return res;
    }
} bm;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int k, n;
    cin >> k;
    vector<int> init(k);
    for (int i = 0; i < k; ++i) cin >> init[i];
    cin >> n;
    auto rec = bm.bm(init);
    cout << bm.linearRecurrence(init, rec, n - 1) << endl;
    return 0;
}
