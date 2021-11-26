#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define ll long long
#define mod 998244353
#define maxn 1 << 18

int n;
ll a[maxn], b[maxn], A[maxn], B[maxn];
void FWT_or(ll* f, int type) {
    for (int mid = 1; mid < n; mid <<= 1)
        for (int block = mid << 1, j = 0; j < n; j += block)
            for (int i = j; i < j + mid; i++)
                f[i + mid] = (f[i + mid] + f[i] * type + mod) % mod;
}
void FWT_and(ll* f, int type) {
    for (int mid = 1; mid < n; mid <<= 1)
        for (int block = mid << 1, j = 0; j < n; j += block)
            for (int i = j; i < j + mid; i++)
                f[i] = (f[i] + f[i + mid] * type + mod) % mod;
}
int inv_2 = 499122177;
void FWT_xor(ll* f, int type) {
    for (int mid = 1; mid < n; mid <<= 1)
        for (int block = mid << 1, j = 0; j < n; j += block)
            for (int i = j; i < j + mid; i++) {
                ll x = f[i], y = f[i + mid];
                f[i] = (x + y) % mod * (type == 1 ? 1 : inv_2) % mod;
                f[i + mid] = (x - y + mod) % mod * (type == 1 ? 1 : inv_2) % mod;
            }
}
void work(void (*FWT)(ll* f, int type)) //将函数作为参数传入
{
    for (int i = 0; i < n; i++) a[i] = A[i], b[i] = B[i];
    FWT(a, 1);
    FWT(b, 1);
    c
            cout
        << "* ";
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    cout << endl;
    cout << "* ";
    for (int i = 0; i < n; ++i) cout << b[i] << " ";
    cout << endl;
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % mod;
    FWT(a, -1);
    for (int i = 0; i < n; i++) printf("%lld ", a[i]);
    printf("\n");
}

int main() {
    scanf("%d", &n);
    n = 1 << n;
    for (int i = 0; i < n; i++) scanf("%lld", &A[i]), A[i] %= mod;
    for (int i = 0; i < n; i++) scanf("%lld", &B[i]), B[i] %= mod;
    work(FWT_or);
    work(FWT_and);
    work(FWT_xor);
}
