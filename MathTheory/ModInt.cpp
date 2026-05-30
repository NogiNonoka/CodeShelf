/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/MathTheory/ModInt.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  ModInt Template
 *  Modular arithmetic with operator overloading
 *  Time Complexity: O(1) per op
 */

#include <bits/stdc++.h>
using namespace std;

template <int MOD>
struct ModInt {
    int v;
    ModInt(long long _v = 0) {
        if (_v >= 0) v = _v % MOD;
        else v = ((_v % MOD) + MOD) % MOD;
    }

    ModInt &operator+=(const ModInt &o) {
        v += o.v; if (v >= MOD) v -= MOD;
        return *this;
    }
    ModInt &operator-=(const ModInt &o) {
        v -= o.v; if (v < 0) v += MOD;
        return *this;
    }
    ModInt &operator*=(const ModInt &o) {
        v = (long long)v * o.v % MOD;
        return *this;
    }

    ModInt operator-() const { return ModInt(-v); }
    ModInt operator+(const ModInt &o) const { return ModInt(*this) += o; }
    ModInt operator-(const ModInt &o) const { return ModInt(*this) -= o; }
    ModInt operator*(const ModInt &o) const { return ModInt(*this) *= o; }

    ModInt inv() const { return qpow(*this, MOD - 2); }
    ModInt &operator/=(const ModInt &o) { return *this *= o.inv(); }
    ModInt operator/(const ModInt &o) const { return ModInt(*this) /= o; }

    static ModInt qpow(ModInt a, long long b) {
        ModInt res(1);
        for (; b; b >>= 1) {
            if (b & 1) res *= a;
            a *= a;
        }
        return res;
    }

    bool operator==(const ModInt &o) const { return v == o.v; }
    bool operator!=(const ModInt &o) const { return v != o.v; }

    friend ostream &operator<<(ostream &os, const ModInt &x) {
        return os << x.v;
    }
};

using mint = ModInt<1000000007>;
using mint998 = ModInt<998244353>;

// Example usage
int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    mint a = 5, b = 3;
    cout << a + b << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    cout << ModInt<1000000007>::qpow(a, 10) << endl;
    return 0;
}
