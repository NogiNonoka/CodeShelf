/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-31
 * @FilePath            : /CodeShelf/String/PalindromicTree_Eertree.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Palindromic Tree (Eertree)
 *  Count distinct palindromic substrings and occurrences
 *  Time Complexity: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 7;

struct Eertree {
    struct Node {
        int next[26];
        int len, sufflink, cnt;
    } tree[MAXN];

    int num, suff, n;
    char s[MAXN];

    void init() {
        num = 2; suff = 2;
        tree[1].len = -1; tree[1].sufflink = 1;
        tree[2].len = 0;  tree[2].sufflink = 1;
        for (int i = 0; i < 26; ++i) tree[1].next[i] = tree[2].next[i] = 0;
        n = 0;
    }

    bool addLetter(int pos) {
        int cur = suff, curlen = 0;
        int ch = s[pos] - 'a';
        while (true) {
            curlen = tree[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
            cur = tree[cur].sufflink;
        }
        if (tree[cur].next[ch]) {
            suff = tree[cur].next[ch];
            tree[suff].cnt++;
            return false;
        }
        suff = ++num;
        tree[num].len = tree[cur].len + 2;
        tree[num].cnt = 1;
        for (int i = 0; i < 26; ++i) tree[num].next[i] = 0;
        tree[cur].next[ch] = num;
        if (tree[num].len == 1) {
            tree[num].sufflink = 2;
            return true;
        }
        while (true) {
            cur = tree[cur].sufflink;
            curlen = tree[cur].len;
            if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                tree[num].sufflink = tree[cur].next[ch];
                break;
            }
        }
        return true;
    }

    void build(const char *str) {
        init();
        int len = strlen(str);
        for (int i = 0; i < len; ++i) {
            s[n++] = str[i];
            addLetter(n - 1);
        }
    }

    long long distinctCount() { return num - 2; }
} eertree;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s;
    cin >> s;
    eertree.build(s.c_str());
    cout << eertree.distinctCount() << endl;
    return 0;
}
