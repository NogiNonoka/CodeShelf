#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 5e6 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

string str;
int ans[MAXN];

void lyndon(string &str, int *ans)
{
    // Find str[1...i]'s lexicographically smallest suffix str[j...i]
    int i = 0;
    ans[0] = 1; // Index start from 1
    while (i < str.length())
    {
        int j = i;
        int k = i + 1;
        ans[k] = k + 1;
        while (k < str.length() && str[j] <= str[k])
        {
            if (str[j] == str[k])
            {
                ans[k] = ans[j] + k - j;
                j++;
            }
            else
            {
                j = i;
                ans[k] = i + 1;
            }
            k++;
        }
        while (i <= j)
        {
            i += k - j;
            // Lyndon String Right Pos
            ans[k] = i + 1;
        }
    }
}

signed main(void)
{
    // Problem ID: P6114
    // Link: https://www.luogu.com.cn/problem/P6114
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string str;
    cin >> str;
    lyndon(str, ans);
    int res = 0;
    // for (int i = 0; i < str.length(); ++i)
    // {
    //     cout << ans[i] << " ";
    // }
    // cout << endl;
    int minn = str.length() + 1;
    for (int i = str.length() - 1; i >= 0; --i)
    {
        if (ans[i] < minn)
        {
            res ^= i + 1;
            minn = ans[i];
        }
    }
    cout << res << endl;
    return 0;
}