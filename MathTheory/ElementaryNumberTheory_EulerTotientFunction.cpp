/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-25 10:09:59
 * @FilePath            : /CodeShelf/MathTheory/ElementaryNumberTheory_EulerTotientFunction.cpp
 * /CodeShelf/MathTheory/ElementaryNumberTheory_EulerTotientFunction.cpp
 * @Forward Declaration : Quick Pow
 * @Discription         :
 *  Use Euler Theorm calc Inverse Element
 *  a ^ phi(b) = 1 (mod b)
 *  phi(b) is NOT minimum order
 *  Use phi(b)'s divisors calc a ^ div = 1 (mod b) for minimum order (Based on
 *  Lagrange theorem - Group theorem)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e7 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

void phiSieve(int n, int* phi) {
    // Time Complexity: O(N)
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i < n; i++) {
        if (!phi[i]) {
            for (int j = i; j < n; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

int qPow(int a, int b, int p = MOD) {
    // Calc a ^ b % MOD
    int ans = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) ans = ans * a % p;
    return ans;
}

int inv(int a, int p) {
    // a^phi(p) = 1 (mod p)
    return qPow(a, phi(p) - 1, p);
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return 0;
}