/*
 * @Author              : NogiNonoka
 * @Date                : 2020-12-10 10:15:59
 * @FilePath            : /CodeShelf/DataStructure/SegmentTree_PlusMinus.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Segment Tree
 *  Node Change: Plus Minus
 *  Range Change: Plus Minus
 *  Time Complexity: O(NlogN)
 */

#include <algorithm>
#include <cstring>
#include <iostream>

#define int long long
using namespace std;
const int MAXN = 5e6 + 7;

struct SegmentTree {
    // Node Change: Plus Minus
    // Range Change: Plus Minus
    // Time Complexity: O(NlogN)
    struct Node {
        int left, right;
        int lson, rson;
        int val;
        int tag;
    } pool[MAXN << 2];

    int cnt;
    int root;
    int data[MAXN];

    void init() { cnt = 0; root = ++cnt; }

    void update(int now) {
        pool[now].val = pool[pool[now].lson].val + pool[pool[now].rson].val +
            pool[pool[now].lson].tag * (pool[pool[now].lson].right - pool[pool[now].lson].left + 1) +
            pool[pool[now].rson].tag * (pool[pool[now].rson].right - pool[pool[now].rson].left + 1);
    }

    void build(int l, int r, int now) {
        pool[now].left = l;
        pool[now].right = r;
        if (l == r) {
            pool[now].lson = pool[now].rson = 0;
            pool[now].val = data[l];
            pool[now].tag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        pool[now].lson = ++cnt;
        pool[now].rson = ++cnt;
        build(l, mid, pool[now].lson);
        build(mid + 1, r, pool[now].rson);
        update(now);
        pool[now].tag = 0;
    }

    void pushdown(int now) {
        pool[now].val += pool[now].tag * (pool[now].right - pool[now].left + 1);
        if (pool[now].left == pool[now].right) {
            pool[now].tag = 0;
            return;
        }
        pool[pool[now].lson].tag += pool[now].tag;
        pool[pool[now].rson].tag += pool[now].tag;
        pool[now].tag = 0;
    }

    void rangeAdd(int l, int r, int now, int tg) {
        if (pool[now].left == l && pool[now].right == r) {
            pool[now].tag += tg;
            return;
        }
        if (r <= pool[pool[now].lson].right)
            rangeAdd(l, r, pool[now].lson, tg);
        else if (l >= pool[pool[now].rson].left)
            rangeAdd(l, r, pool[now].rson, tg);
        else {
            rangeAdd(l, pool[pool[now].lson].right, pool[now].lson, tg);
            rangeAdd(pool[pool[now].rson].left, r, pool[now].rson, tg);
        }
        update(now);
    }

    int query(int l, int r, int now) {
        int res = 0;
        if (pool[now].left == l && pool[now].right == r) {
            pushdown(now);
            return pool[now].val;
        }
        pushdown(now);
        if (r <= pool[pool[now].lson].right)
            return query(l, r, pool[now].lson);
        else if (l >= pool[pool[now].rson].left)
            return query(l, r, pool[now].rson);
        else
            return query(l, pool[pool[now].lson].right, pool[now].lson) +
                query(pool[pool[now].rson].left, r, pool[now].rson);
        return res;
    }
} stree;

signed main(void) {
    // Problem ID: Luogu P3372 (Range Query) Luogu P3368 (Node Query)
    // Link: https://www.luogu.com.cn/problem/P3372
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) { cin >> stree.data[i]; }
    stree.init();
    stree.build(1, n, stree.root);
    for (int i = 1; i <= m; ++i) {
        int t;
        cin >> t;
        if (t == 2) {
            int x, y;
            cin >> x >> y;
            cout << stree.query(x, y, stree.root) << endl;
        } else {
            int x, y, k;
            cin >> x >> y >> k;
            stree.rangeAdd(x, y, stree.root, k);
        }
    }
    return 0;
}
