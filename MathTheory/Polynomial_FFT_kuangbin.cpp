#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 200020;
const double PI = acos(-1.0);

struct Complex {
    double x, y;
    Complex(double _x = 0.0, double _y = 0.0) {
        x = _x;
        y = _y;
    }
    Complex operator-(const Complex& b) const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator+(const Complex& b) const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator*(const Complex& b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};
/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 *len 必须为 2 的幂
 */
void change(Complex y[], int len) {
    int i, j, k;
    for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        // 交换互为小标反转的元素，i<j 保证交换一次
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k = k / 2;
        }
        if (j < k) j += k;
    }
}
/*
 * 做 FFT
 *len 必须是 2^k 形式
 *on == 1 时是 DFT，on == -1 时是 IDFT
 */
void fft(Complex y[], int len, int on) {
    change(y, len);
    for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i].x /= len;
        }
    }
}

int n;
Complex a[MAXN], b[MAXN];

signed main() {
    cin >> n;
    int x;
    for (int i = 0; i < n; ++i) cin >> x, a[i] = Complex(x, 0);
    for (int i = 0; i < n; ++i) cin >> x, b[i] = Complex(x, 0);
    int len = 1;
    while (len < (n << 1)) len <<= 1;
    for (int i = n; i < len; ++i) a[i] = b[i] = Complex(0, 0);
    fft(a, len, 1); fft(b, len, 1);
    for (int i = 0; i < len; ++i) a[i] = a[i] * b[i];
    fft(a, len, -1);
    for (int i = 0; i < (n << 1) - 1; ++i) cout << (int)(a[i].x + 0.5) << " ";
    return 0;
}