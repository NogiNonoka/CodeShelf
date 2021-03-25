/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-25 10:09:59
 * @FilePath            : /CodeShelf/MathTheory/ElementaryNumberTheory_EulerTotientFunction.cpp
 * @Forward Declaration : Quick Pow
 * @Discription         : 
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

int phi(int n)
{
    int ans = n;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}

void phiSieve(int n, int *phi)
{
    // Time Complexity: O(N)
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i < n; i++)
    {
        if (!phi[i])
        {
            for (int j = i; j < n; j += i)
            {
                if (!phi[j])
                    phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

int qpow(int a, int b)
{
    // Calc a ^ b % MOD
    int ans = 1;
    for (; b; b >>= 1, a = a * a % MOD)
        if (b & 1)
            ans = ans * a % MOD;
    return ans;
}

void inv(int a, int p)
{
    // a^phi(p) = 1 (mod p)
    return qpow(a, phi(p) - 1);
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return