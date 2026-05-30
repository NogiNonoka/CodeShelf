/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/MathTheory/Polynomial_FFT.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Fast Fourier Transform (Iterative)
 *  Polynomial multiplication via Cooley-Tukey FFT
 *  Time Complexity: O(NlogN)
 */

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

using Complex = complex<double>;

void fft(vector<Complex> &a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        Complex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            Complex w(1);
            for (int j = 0; j < len / 2; ++j) {
                Complex u = a[i + j];
                Complex v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inv) {
        for (Complex &x : a) x /= n;
    }
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    fft(fa, true);
    vector<int> res(n);
    for (int i = 0; i < n; ++i)
        res[i] = (int)round(fa[i].real());
    while ((int)res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 0; i <= n; ++i) cin >> a[i];
    for (int i = 0; i <= m; ++i) cin >> b[i];
    auto c = multiply(a, b);
    for (int i = 0; i < (int)c.size(); ++i)
        cout << c[i] << " \n"[i + 1 == (int)c.size()];
    return 0;
}
