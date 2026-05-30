/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/Others/FastIO.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Fast IO Template
 *  Custom fast scanner for large input (10^6+)
 *  Usage: FastIO::readint(), FastIO::readll()
 */

#include <bits/stdc++.h>
using namespace std;

struct FastIO {
    static const int BUFSIZE = 1 << 20;
    char buf[BUFSIZE];
    int idx, size;

    FastIO() : idx(0), size(0) {}

    inline char read() {
        if (idx >= size) {
            size = fread(buf, 1, BUFSIZE, stdin);
            idx = 0;
            if (size == 0) return EOF;
        }
        return buf[idx++];
    }

    template <typename T>
    bool read(T &out) {
        char c;
        T sign = 1;
        T val = 0;
        do { c = read(); } while (c <= ' ');
        if (c == '-') { sign = -1; c = read(); }
        for (; c >= '0' && c <= '9'; c = read())
            val = val * 10 + (c - '0');
        out = val * sign;
        return c != EOF;
    }

    int readint() { int x; read(x); return x; }
    long long readll() { long long x; read(x); return x; }

    void readstr(char *s) {
        char c;
        do { c = read(); } while (c <= ' ');
        int len = 0;
        for (; c > ' '; c = read()) s[len++] = c;
        s[len] = '\0';
    }
};

FastIO io;

int main(void) {
    int n = io.readint();
    long long sum = 0;
    for (int i = 0; i < n; ++i) sum += io.readll();
    printf("%lld\n", sum);
    return 0;
}
