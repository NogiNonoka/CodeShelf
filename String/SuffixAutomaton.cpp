/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/String/SuffixAutomaton.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : claude-opus-4-8
 *  Suffix Automaton
 *  Substring counting, distinct substring count
 *  Time Complexity: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 7;

struct SuffixAutomaton {
    struct State {
        int len, link;
        int next[26];
        State() : len(0), link(-1) {
            memset(next, -1, sizeof(next));
        }
    } st[MAXN << 1];

    int sz, last;

    void init() {
        st[0] = State();
        sz = 1;
        last = 0;
    }

    void extend(char c) {
        int cur = sz++;
        st[cur] = State();
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && st[p].next[c - 'a'] == -1) {
            st[p].next[c - 'a'] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c - 'a'];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone] = st[q];
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c - 'a'] == q) {
                    st[p].next[c - 'a'] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    long long distinctSubstrings() {
        long long res = 0;
        for (int i = 1; i < sz; ++i)
            res += st[i].len - st[st[i].link].len;
        return res;
    }
} sam;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s;
    cin >> s;
    sam.init();
    for (char c : s) sam.extend(c);
    cout << sam.distinctSubstrings() << endl;
    return 0;
}
