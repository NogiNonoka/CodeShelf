#include <bits/stdc++.h>
using namespace std;
#define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 4e5 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int qPow(int a, int b, int p) {
    int res = 1;
    for (; b; b >>= 1, a = a * a % p) {
        if (b & 1) {
            res *= a;
            res %= p;
        }
    }
    return (res % p + p) % p;
}

void calcHash(string &s, vector<int> &hs, const int &BASE, const int &MOD) {
    hs.resize(s.length());
    hs[0] = s[0] % MOD;
    for (int i = 1; i < s.length(); ++i) {
        hs[i] = (hs[i - 1] * BASE + s[i]) % MOD;
    }
}

int getHash(vector<int> &hs, const int &l, const int &r, const int &BASE, const int &MOD) {
    if (l == 0) return hs[r];
    return ((hs[r] - hs[l - 1] * qPow(BASE, r - l + 1, MOD)) % MOD + MOD) % MOD;
}

vector<int> v1, v2;
string s1, s2;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int BASE = 233;
    int MOD = 998244353;
    cin >> s1 >> s2;
    calcHash(s1, v1, BASE, MOD);
    calcHash(s2, v2, BASE, MOD);
    for (int i = 0; i < s1.length(); ++i) {
        cout << v1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < s2.length(); ++i) {
        cout << v2[i] << " ";
    }
    cout << endl;
    return 0;
}