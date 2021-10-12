/*
 * @Author              : NogiNonoka
 * @Date                : 2021-09-06 00:17:00
 * @FilePath            : /CodeShelf/String/SuffixArray.cpp
 * @Forward Declaration : None
 * @Discription         : 
 * Suffix Array (Counting Sort):
 *   Time Complexity: O(NlogN)
 */
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
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

string s;
int sa[MAXN << 1], rk[MAXN << 1], tmprk[MAXN << 1];

void build(int n) {
    // Time Complexity: O(Nlog^2(N))
    for (int i = 0; i < n; ++i) {
        sa[i + 1] = i + 1;
        rk[i + 1] = s[i];
    }
    for (int i = 1; i < n; i <<= 1) { 
        sort(sa + 1, sa + n + 1, [&](int x, int y) { return rk[x] == rk[y] ? rk[x + i] < rk[y + i] : rk[x] < rk[y]; });
        memcpy(tmprk, rk, n * sizeof(int));
        for (int j = 1, cnt = 0; j <= n; ++j) {
            if (tmprk[sa[j]] == tmprk[sa[j - 1]] && tmprk[sa[j] + i] == tmprk[sa[j - 1] + i]) {
                rk[sa[j]] = cnt;
            } else {
                rk[sa[j]] = ++cnt;
            }
        }
    }
}

int cnt[MAXN], id[MAXN];

void getSA(int n) {
    // Time Complexity: O(Nlog(N))
    memset(cnt, 0, sizeof(cnt));
    int ma = 0, cur = 0;
    for (int i = 1; i <= n; ++i) {
        rk[i] = s[i - 1];
        cnt[rk[i]] += 1;
        ma = max(ma, rk[i]);
    }
    for (int i = 1; i <= ma; ++i) { cnt[i] += cnt[i - 1]; }
    for (int i = n; i >= 1; --i) { sa[cnt[rk[i]]--] = i; }
    for (int len = 1; len < n; len <<= 1, ma = cur) {
        // sort with rk[i + len]
        cur = 0;
        for (int i = n - len + 1; i <= n; ++i) { id[++cur] = i; }
        for (int i = 1; i <= n; ++i) {
            if (sa[i] > len) {
                id[++cur] = sa[i] - len;
            }
        }
        // sort with rk[i]
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; ++i) { cnt[rk[id[i]]] += 1; }
        for (int i = 1; i <= ma; ++i) { cnt[i] += cnt[i - 1]; }
        for (int i = n; i >= 1; --i) { sa[cnt[rk[id[i]]]--] = id[i]; }
        // unique
        cur = 0;
        memcpy(tmprk, rk, sizeof(rk));
        for (int i = 1; i <= n; ++i) {
            if (tmprk[sa[i]] == tmprk[sa[i - 1]] && tmprk[sa[i] + len] == tmprk[sa[i - 1] + len]) {
                rk[sa[i]] = cur;
            } else {
                rk[sa[i]] = ++cur;
            }
        }
        if (cur == n) {
            for (int i = 1; i <= n; ++i) { sa[rk[i]] = i; }
            break;
        }
    }
}

int ht[MAXN];

void getHeight(int n) {
    for (int i = 1, cur = 0; i <= n; ++i) {
        if (cur) cur -= 1;
        while (s[i - 1 + cur] == s[sa[rk[i] - 1] - 1 + cur]) {
            cur += 1;
        }
        ht[rk[i]] = cur;
    }
}

void print(int n) {
    for (int i = 1; i <= n; ++i) { 
        cout << sa[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) { 
        cout << rk[i] << " ";
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << ht[i] << " ";
    }
    cout << endl;
}

signed main(void) {
    // Problem ID: LibreOJ P111
    // Link: https://loj.ac/p/111
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> s;
    getSA(s.length());
    // getHeight(s.length());
    // print(s.length());
    for (int i = 1; i <= s.length(); ++i) {
        cout << sa[i] << " ";
    }
    cout << endl;
    return 0;
}