#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e6 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

using Complex = complex<double>;

const Complex I = Complex(0, 1), R = Complex(1, 0);

Complex tmp[MAXN];

void DFT(Complex f[], int len, int opt) {
    if (len == 1) return;
    for (int i = 0; i < len; ++i) tmp[i] = f[i];
    for (int i = 0; i < len; ++i) f[i / 2 + (i & 1 ? len / 2 : 0)] = tmp[i];
    Complex *g = f, *h = f + len / 2;
    DFT(g, len / 2, opt); DFT(h, len / 2, opt);
    Complex cur = R, stp = Complex(cos(2 * PI / len), sin(2 * PI * opt / len));
    for (int i = 0; i < len / 2; ++i) {
        tmp[i] = g[i] + cur * h[i];
        tmp[i + len / 2] = g[i] - cur * h[i];
        cur *= stp;
    }
    for (int i = 0; i < len; ++i) f[i] = tmp[i];
}

Complex a[MAXN], b[MAXN];

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    int x;
    for (int i = 0; i < n; ++i) cin >> x, a[i] = Complex(x, 0);
    for (int i = 0; i < n; ++i) cin >> x, b[i] = Complex(x, 0);
    int len = 1; 
    while (len < (n << 1)) len <<= 1;
    for (int i = n; i < len; ++i) a[i] = b[i] = Complex(0, 0);
    DFT(a, len, 1); DFT(b, len, 1);
    for (int i = 0; i < len; ++i) a[i] *= b[i];
    DFT(a, len, -1);
    for (int i = 0; i < (n << 1) - 1; ++i) cout << a[i].real() / len << " ";
    return 0;
}