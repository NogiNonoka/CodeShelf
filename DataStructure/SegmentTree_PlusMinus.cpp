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
        Node *lson, *rson;
        int val;
        int tag;
        Node() : lson(nullptr), rson(nullptr) {}
    } * root;

    int data[MAXN];

    void init() { root = new Node; }

    void update(Node* now) {
        now->val = now->lson->val + now->rson->val +
            now->lson->tag * (now->lson->right - now->lson->left + 1) +
            now->rson->tag * (now->rson->right - now->rson->left + 1);
    }

    void build(int l, int r, Node* now) {
        now->left = l;
        now->right = r;
        if (l == r) {
            now->lson = nullptr;
            now->rson = nullptr;
            now->val = data[l];
            now->tag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (now->lson == nullptr) now->lson = new Node;
        if (now->rson == nullptr) now->rson = new Node;
        build(l, mid, now->lson);
        build(mid + 1, r, now->rson);
        update(now);
        now->tag = 0;
    }

    void pushdown(Node* now) {
        now->val += now->tag * (now->right - now->left + 1);
        if (now->left == now->right) {
            now->tag = 0;
            return;
        }
        now->lson->tag += now->tag;
        now->rson->tag += now->tag;
        now->tag = 0;
    }

    void rangeAdd(int l, int r, Node* now, int tg) {
        if (now->left == l && now->right == r) {
            now->tag += tg;
            return;
        }
        if (r <= now->lson->right)
            rangeAdd(l, r, now->lson, tg);
        else if (l >= now->rson->left)
            rangeAdd(l, r, now->rson, tg);
        else {
            rangeAdd(l, now->lson->right, now->lson, tg);
            rangeAdd(now->rson->left, r, now->rson, tg);
        }
        update(now);
    }

    int query(int l, int r, Node* now) {
        int res = 0;
        if (now->left == l && now->right == r) {
            pushdown(now);
            return now->val;
        }
        pushdown(now);
        if (r <= now->lson->right)
            return query(l, r, now->lson);
        else if (l >= now->rson->left)
            return query(l, r, now->rson);
        else
            return query(l, now->lson->right, now->lson) +
                query(now->rson->left, r, now->rson);
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
