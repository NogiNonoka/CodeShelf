/*
 * @Author              : NogiNonoka
 * @Date                : 2021-04-10 13:18:51
 * @FilePath            : /CodeShelf/String/StringMatch_ACAutomata.cpp
 * @LastEditTime        : 2021-04-10 14:12:03
 * @Forward Declaration : None
 * @Discription         : 
 *  AC Automata
 *  Time Complexity: O(N + k * M)
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 5e5 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct ACAutomata
{
    struct Node
    {
        int next[26];
        int fail;
        int cnt;
    } node[MAXN];

    int size;

    void init()
    {
        for (int i = 0; i < size; ++i)
        {
            memset(node[i].next, 0, sizeof(node[i].next));
            node[i].fail = 0;
            node[i].cnt = 0;
        }
        size = 0;
        node[size++].fail = -1; // root: node[0] 
    }

    void insert(string &s)
    {
        int now = 0;
        for (auto ch : s)
        {
            if (node[now].next[ch - 'a'] == 0)
                node[now].next[ch - 'a'] = size++;
            now = node[now].next[ch - 'a'];
        }
        node[now].cnt++;
    }

    void build()
    {
        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int now = q.front(); q.pop();
            for (int i = 0; i < 26; ++i)
            {
                int nxt = node[now].next[i];
                if (nxt)
                {
                    int p = node[now].fail;
                    while (p != -1 && node[p].next[i] == 0)
                        p = node[p].fail;
                    node[nxt].fail = (p == -1) ? 0 : node[p].next[i]; 
                    q.push(nxt);
                }
            }
        }
    }

    int calc(int now)
    {
        int res = 0;
        while (now)
        {
            res += node[now].cnt;
            node[now].cnt = 0;
            now = node[now].fail;
        }
        return res;
    }

    int match(string &s)
    {
        int ans = 0;
        int now = 0;
        for (auto ch : s)
        {
            if (node[now].next[ch - 'a'])
                now = node[now].next[ch - 'a'];
            else 
            {
                int p = node[now].fail;
                while (p != -1 && node[p].next[ch - 'a'] == 0)
                    p = node[p].fail;
                now = (p == -1) ? 0 : node[p].next[ch - 'a'];
            }
            if (node[now].cnt)
                ans += calc(now);
        }
        return ans;
    }
} aho;

int T;
int n;
string s;

signed main(void)
{
    // Problem ID: HDU 2222
    // Link: http://acm.hdu.edu.cn/showproblem.php?pid=2222
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> T;
    while (T--)
    {
        aho.init();
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
             cin >> s;
             aho.insert(s);
        }
        aho.build();
        cin >> s;
        cout << aho.match(s) << endl;
    }
    return 0;
}