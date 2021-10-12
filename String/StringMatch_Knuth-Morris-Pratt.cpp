/*
 * @Author              : NogiNonoka
 * @Date                : 2020-11-14 20:32:45
 * @FilePath            : /CodeShelf/String/StringMatch_Knuth-Morris-Pratt.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  String Compare
 *  Knuth-Morris-Pratt
 *  Time Complexity: O(N+M)
 */

#include <iostream>
#include <string>
using namespace std;
const int MAXN = 1e5 + 7;

struct KMP {
    // Serach t in s and return pos
    // Time Complexity: O(N+M)
    string s;
    string t;

    int nxt[MAXN];

    void getNext() {
        int j = 0, k = -1;
        nxt[0] = -1;
        while (j < (int)t.length()) {
            if (k == -1 || t[j] == t[k])
                nxt[++j] = ++k;
            else
                k = nxt[k];
        }
    }

    void kmpAllIndex() {
        /**
         * @description: print all first index found in s
         * @param {void}
         * @return {void}
         */
        getNext();
        int i = 0, j = 0;
        while (i < (int)s.length()) {
            if (j == -1 || s[i] == t[j])
                ++i, ++j;
            else
                j = nxt[j];
            if (j == t.length()) {
                cout << i - j + 1 << endl;
                j = nxt[j];
            }
        }
    }

    int kmpFirstIndex();

    int kmpFirstCount();

#ifdef DEBUG
    void print() {
        for (int i = 0; i < t.length(); ++i) { cout << t[i] << " "; }
        cout << endl;
        for (int i = 0; i < t.length(); ++i) { cout << nxt[i] << " "; }
    }
#endif
} kmp;

int main(void) {
    // Problem: Luogu P3375
    // Link: https://www.luogu.com.cn/problem/P3375
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> kmp.s >> kmp.t;
    kmp.kmpAllIndex();
    // nxt[i] means t[i - 1]'s LCS
    for (int i = 0; i < kmp.t.length(); ++i) cout << kmp.nxt[i + 1] << " ";
    return 0;
}