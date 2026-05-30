/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/DataStructure/SegmentTree_Beats.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Segment Tree Beats
 *  Range chmin / chmax / add / sum query
 *  Time Complexity: O(NlogN) amortized
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 2e5 + 7;

struct SegmentTreeBeats {
    struct Node {
        int max1, max2, maxcnt;
        int min1, min2, mincnt;
        int sum, add;
    } tr[MAXN << 2];

    int a[MAXN];
    int n;

    void pushup(int p) {
        tr[p].sum = tr[p << 1].sum + tr[p << 1 | 1].sum;
        // max
        if (tr[p << 1].max1 == tr[p << 1 | 1].max1) {
            tr[p].max1 = tr[p << 1].max1;
            tr[p].max2 = max(tr[p << 1].max2, tr[p << 1 | 1].max2);
            tr[p].maxcnt = tr[p << 1].maxcnt + tr[p << 1 | 1].maxcnt;
        } else {
            if (tr[p << 1].max1 > tr[p << 1 | 1].max1) {
                tr[p].max1 = tr[p << 1].max1;
                tr[p].max2 = max(tr[p << 1].max2, tr[p << 1 | 1].max1);
                tr[p].maxcnt = tr[p << 1].maxcnt;
            } else {
                tr[p].max1 = tr[p << 1 | 1].max1;
                tr[p].max2 = max(tr[p << 1].max1, tr[p << 1 | 1].max2);
                tr[p].maxcnt = tr[p << 1 | 1].maxcnt;
            }
        }
        // min
        if (tr[p << 1].min1 == tr[p << 1 | 1].min1) {
            tr[p].min1 = tr[p << 1].min1;
            tr[p].min2 = min(tr[p << 1].min2, tr[p << 1 | 1].min2);
            tr[p].mincnt = tr[p << 1].mincnt + tr[p << 1 | 1].mincnt;
        } else {
            if (tr[p << 1].min1 < tr[p << 1 | 1].min1) {
                tr[p].min1 = tr[p << 1].min1;
                tr[p].min2 = min(tr[p << 1].min2, tr[p << 1 | 1].min1);
                tr[p].mincnt = tr[p << 1].mincnt;
            } else {
                tr[p].min1 = tr[p << 1 | 1].min1;
                tr[p].min2 = min(tr[p << 1].min1, tr[p << 1 | 1].min2);
                tr[p].mincnt = tr[p << 1 | 1].mincnt;
            }
        }
    }

    void push_add(int p, int l, int r, int v) {
        tr[p].sum += (r - l + 1) * v;
        tr[p].max1 += v; tr[p].max2 += v;
        tr[p].min1 += v; tr[p].min2 += v;
        tr[p].add += v;
    }

    void push_chmin(int p, int v) {
        if (tr[p].max1 <= v) return;
        tr[p].sum -= (tr[p].max1 - v) * tr[p].maxcnt;
        tr[p].max1 = v;
        if (tr[p].min1 > v) tr[p].min1 = v;
        else if (tr[p].min2 > v) tr[p].min2 = v;
    }

    void push_chmax(int p, int v) {
        if (tr[p].min1 >= v) return;
        tr[p].sum += (v - tr[p].min1) * tr[p].mincnt;
        tr[p].min1 = v;
        if (tr[p].max1 < v) tr[p].max1 = v;
        else if (tr[p].max2 < v) tr[p].max2 = v;
    }

    void pushdown(int p, int l, int r) {
        int mid = (l + r) >> 1;
        if (tr[p].add) {
            push_add(p << 1, l, mid, tr[p].add);
            push_add(p << 1 | 1, mid + 1, r, tr[p].add);
            tr[p].add = 0;
        }
        push_chmin(p << 1, tr[p].max1);
        push_chmin(p << 1 | 1, tr[p].max1);
        push_chmax(p << 1, tr[p].min1);
        push_chmax(p << 1 | 1, tr[p].min1);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            int v = a[l];
            tr[p] = {v, (int)-1e18, 1, v, (int)1e18, 1, v, 0};
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    void rangeAdd(int p, int l, int r, int L, int R, int v) {
        if (L <= l && r <= R) {
            push_add(p, l, r, v);
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) rangeAdd(p << 1, l, mid, L, R, v);
        if (R > mid) rangeAdd(p << 1 | 1, mid + 1, r, L, R, v);
        pushup(p);
    }

    void rangeChmin(int p, int l, int r, int L, int R, int v) {
        if (tr[p].max1 <= v) return;
        if (L <= l && r <= R && tr[p].max2 < v) {
            push_chmin(p, v);
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) rangeChmin(p << 1, l, mid, L, R, v);
        if (R > mid) rangeChmin(p << 1 | 1, mid + 1, r, L, R, v);
        pushup(p);
    }

    void rangeChmax(int p, int l, int r, int L, int R, int v) {
        if (tr[p].min1 >= v) return;
        if (L <= l && r <= R && tr[p].min2 > v) {
            push_chmax(p, v);
            return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) rangeChmax(p << 1, l, mid, L, R, v);
        if (R > mid) rangeChmax(p << 1 | 1, mid + 1, r, L, R, v);
        pushup(p);
    }

    int querySum(int p, int l, int r, int L, int R) {
        if (L <= l && r <= R) return tr[p].sum;
        pushdown(p, l, r);
        int mid = (l + r) >> 1, res = 0;
        if (L <= mid) res += querySum(p << 1, l, mid, L, R);
        if (R > mid) res += querySum(p << 1 | 1, mid + 1, r, L, R);
        return res;
    }

    void init(int _n) {
        n = _n;
        build(1, 1, n);
    }
} beats;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> beats.a[i];
    beats.init(n);
    while (m--) {
        int op, l, r, x;
        cin >> op >> l >> r;
        if (op == 0) {
            cin >> x;
            beats.rangeChmin(1, 1, n, l, r, x);
        } else if (op == 1) {
            cin >> x;
            beats.rangeChmax(1, 1, n, l, r, x);
        } else if (op == 2) {
            cin >> x;
            beats.rangeAdd(1, 1, n, l, r, x);
        } else {
            cout << beats.querySum(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}
