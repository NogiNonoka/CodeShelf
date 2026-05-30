/*
 * @Author              : NogiNonoka
 * @Date                : 2020-12-10 10:15:59
 * @FilePath            : /CodeShelf/DataStructure/SegmentTree_PlusMinus.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : claude-opus-4-8
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
    } nodes[MAXN << 2];

    int cnt;
    int root;
    int data[MAXN];

    void init() { cnt = 0; root = ++cnt; }

    void update(int now) {
        nodes[now].val = nodes[nodes[now].lson].val + nodes[nodes[now].rson].val +
            nodes[nodes[now].lson].tag * (nodes[nodes[now].lson].right - nodes[nodes[now].lson].left + 1) +
            nodes[nodes[now].rson].tag * (nodes[nodes[now].rson].right - nodes[nodes[now].rson].left + 1);
    }

    void build(int l, int r, int now) {
        nodes[now].left = l;
        nodes[now].right = r;
        if (l == r) {
            nodes[now].lson = nodes[now].rson = 0;
            nodes[now].val = data[l];
            nodes[now].tag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        nodes[now].lson = ++cnt;
        nodes[now].rson = ++cnt;
        build(l, mid, nodes[now].lson);
        build(mid + 1, r, nodes[now].rson);
        update(now);
        nodes[now].tag = 0;
    }

    void pushdown(int now) {
        nodes[now].val += nodes[now].tag * (nodes[now].right - nodes[now].left + 1);
        if (nodes[now].left == nodes[now].right) {
            nodes[now].tag = 0;
            return;
        }
        nodes[nodes[now].lson].tag += nodes[now].tag;
        nodes[nodes[now].rson].tag += nodes[now].tag;
        nodes[now].tag = 0;
    }

    void rangeAdd(int l, int r, int now, int tg) {
        if (nodes[now].left == l && nodes[now].right == r) {
            nodes[now].tag += tg;
            return;
        }
        if (r <= nodes[nodes[now].lson].right)
            rangeAdd(l, r, nodes[now].lson, tg);
        else if (l >= nodes[nodes[now].rson].left)
            rangeAdd(l, r, nodes[now].rson, tg);
        else {
            rangeAdd(l, nodes[nodes[now].lson].right, nodes[now].lson, tg);
            rangeAdd(nodes[nodes[now].rson].left, r, nodes[now].rson, tg);
        }
        update(now);
    }

    int query(int l, int r, int now) {
        int res = 0;
        if (nodes[now].left == l && nodes[now].right == r) {
            pushdown(now);
            return nodes[now].val;
        }
        pushdown(now);
        if (r <= nodes[nodes[now].lson].right)
            return query(l, r, nodes[now].lson);
        else if (l >= nodes[nodes[now].rson].left)
            return query(l, r, nodes[now].rson);
        else
            return query(l, nodes[nodes[now].lson].right, nodes[now].lson) +
                query(nodes[nodes[now].rson].left, r, nodes[now].rson);
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
