/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/DataStructure/FenwickTree.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Fenwick Tree (Binary Indexed Tree)
 *  Point Update, Prefix Query
 *  Time Complexity: O(logN)
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 2e5 + 7;

struct Fenwick {
    int bit[MAXN];
    int n;

    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; ++i) bit[i] = 0;
    }

    void add(int x, int v) {
        for (; x <= n; x += x & -x)
            bit[x] += v;
    }

    int sum(int x) {
        int res = 0;
        for (; x > 0; x -= x & -x)
            res += bit[x];
        return res;
    }

    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
} fw;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    fw.init(n);
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        fw.add(i, x);
    }
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) fw.add(x, y);
        else cout << fw.rangeSum(x, y) << endl;
    }
    return 0;
}
