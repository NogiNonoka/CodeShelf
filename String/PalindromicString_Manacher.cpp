/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-28 17:13:32
 * @FilePath            : /CodeShelf/String/PalindromicString_Manacher.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Manacher Algorithm (Longest Palindromic Substring)
 *  Time Complexity: O(N)
 */

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e7 + 7;

// Manacher Algorithm (Longest Palindromic Substring)
// Time Complexity: O(N)
string text;
int cnt[MAXN];

void pre(const string& s) {
    text = "^#";
    for (auto ch : s) {
        text += ch;
        text += '#';
    }
    text += '$';
}

int manacher() {
    int ans = 0;
    int mid = 0, maxr = 0;
    for (int i = 1; i < text.size(); ++i) {
        if (i < maxr)
            cnt[i] = min(cnt[mid * 2 - i], maxr - i);
        else
            cnt[i] = 1;
        while (text[i + cnt[i]] == text[i - cnt[i]]) ++cnt[i];
        if (i + cnt[i] > maxr) {
            maxr = i + cnt[i];
            mid = i;
        }
        ans = max(ans, cnt[i]);
    }
    return ans - 1;
}

signed main(void) {
    // Problem ID: Luogu P3805
    // Link: https://www.luogu.com.cn/problem/P3805
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    pre(s);
    cout << manacher() << endl;
    return 0;
}