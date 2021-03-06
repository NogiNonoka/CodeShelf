/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-05 23:37:12
 * @FilePath            : \CodeShelf\String\SuffixCompare_exKMP_ZAlgorithm.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Extend KMP (Z Algorithm)
 *  Match suffix of s with prefix of t
 *  Time Complexity: O(N + M)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 2e7 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct EXKMP
{
    // Extend KMP (Z Algorithm)
    // Match suffix of s with prefix of t
    // Time Complexity: O(N + M)
    int z[MAXN];
    int ext[MAXN];

    void Z(string &t)
    {
        /**
         * @description: Z Algorithm, match suffix of t with prefix of t 
         * @param {model string t}
         * @return {void}
         */
        z[0] = t.length();
        int now = 0;
        while (now + 1 < t.length() && t[now] == t[now + 1])
            ++now;
        z[1] = now;
        int pos = 1;
        for (int i = 2; i < t.length(); ++i)
        {
            if (i + z[i - pos] < pos + z[pos])
                z[i] = z[i - pos];
            else
            {
                now = max(0, pos + z[pos] - i);
                while (now + i < t.length() && t[now] == t[now + i])
                    ++now;
                z[i] = now;
                pos = i;
            }
        }
    }

    void exKMP(string &s, string &t)
    {
        /**
         * @description: Extend KMP
         * @param {text string s, model string t}
         * @return {void}
         */
        Z(t);
        int now = 0;
        while (now < s.length() && now < t.length()  && s[now] == t[now])
            ++now;
        ext[0] = now;
        int pos = 0;
        for (int i = 1; i < s.length(); ++i)
        {
            if (i + z[i - pos] < pos + ext[pos])
                ext[i] = z[i - pos];
            else
            {
                now = max(0, pos + ext[pos] - i);
                while (now + i < s.length() && now < t.length() && s[now + i] == t[now])
                    ++now;
                ext[i] = now;
                pos = i;
            }
        }
    }
}exkmp;

int32_t main(void)
{
    // Problem ID: Luogu P5410
    // Link: https://www.luogu.com.cn/problem/P5410
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s, t;
    long long ans;
    cin >> s >> t;
    exkmp.exKMP(s, t);
    ans = 0;
    for (int i = 0; i < t.length(); ++i)
        // cout << exkmp.z[i] << " ";
        ans = ans ^ (1LL * (i + 1) * (exkmp.z[i] + 1));
    cout << ans << endl;
    ans = 0;
    for (int i = 0; i < s.length(); ++i)
        // cout << exkmp.ext[i] << " ";
        ans = ans ^ (1LL * (i + 1) * (exkmp.ext[i] + 1));
    cout << ans << endl;
    return 0;
}