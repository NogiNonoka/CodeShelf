/*
 * @Author              : NogiNonoka
 * @Date                : 2021-01-25 22:34:25
 * @FilePath            : /CodeShelf/DataStructure/SegmentTree_MinMax.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Segment Tree
 *  Node Change: Min Max
 *  Range Change: Min Max (change to new val)
 *  Time Complexity: O(NlogN)
 */

#include <algorithm>
#include <cstring>
#include <iostream>

#define int long long
using namespace std;
const int MAXN = 2e5 + 7;
const int INF = 0x3f3f3f3f;

struct SegmentTreeMinMax {
    // Node Change: Max Min
    // Range Change: Max Min (change to new val)
    // Time Complexity: O(NlogN)
    struct Node {
        int left, right;
        Node *lson, *rson;
        int maxi, mini;
        int maxtag, mintag;
        Node() : lson(nullptr), rson(nullptr){};
    } * root;

    void init() { root = new Node; }

    void update(Node* now) {
        now->mini = min(min(now->lson->mini, now->lson->mintag),
            min(now->rson->mini, now->rson->mintag));
        now->maxi = max(max(now->lson->maxi, now->lson->maxtag),
            max(now->rson->maxi, now->rson->maxtag));
    }

    void build(int l, int r, Node* now) {
        now->left = l;
        now->right = r;
        if (l == r) {
            now->lson = nullptr;
            now->rson = nullptr;
            now->mini = INF;
            now->maxi = 0;
            now->mintag = INF;
            now->maxtag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (now->lson == nullptr) now->lson = new Node;
        if (now->rson == nullptr) now->rson = new Node;
        build(l, mid, now->lson);
        build(mid + 1, r, now->rson);
        update(now);
        now->mintag = INF;
        now->maxtag = 0;
    }

    void rangeChange(int l, int r, Node* now, int tg) {
        if (now->left == l && now->right == r) {
            now->mintag = min(now->mintag, tg);
            now->maxtag = max(now->maxtag, tg);
            return;
        }
        if (r <= now->lson->right)
            rangeChange(l, r, now->lson, tg);
        else if (l >= now->rson->left)
            rangeChange(l, r, now->rson, tg);
        else {
            rangeChange(l, now->lson->right, now->lson, tg);
            rangeChange(now->rson->left, r, now->rson, tg);
        }
        update(now);
    }

    void pushdown(Node* now) {
        now->mini = min(now->mini, now->mintag);
        now->maxi = max(now->maxi, now->maxtag);
        if (now->left == now->right) return;
        now->lson->mintag = min(now->lson->mintag, now->mintag);
        now->lson->maxtag = max(now->lson->maxtag, now->maxtag);
        now->rson->mintag = min(now->rson->mintag, now->mintag);
        now->rson->maxtag = max(now->rson->maxtag, now->maxtag);
    }

    pair<int, int> query(int l, int r, Node* now) {
        pair<int, int> ans; // Range [l, r] Min && Max
        ans.first = INF;
        ans.second = 0;
        if (now->left == l && now->right == r) {
            pushdown(now);
            ans.first = min(ans.first, now->mini);
            ans.second = max(ans.second, now->maxi);
            return ans;
        }
        pushdown(now);
        if (r <= now->lson->right) {
            pair<int, int> range = query(l, r, now->lson);
            ans.first = min(ans.first, range.first);
            ans.second = max(ans.second, range.second);
        } else if (l >= now->rson->left) {
            pair<int, int> range = query(l, r, now->rson);
            ans.first = min(ans.first, range.first);
            ans.second = max(ans.second, range.second);
        } else {
            pair<int, int> range1 = query(l, now->lson->right, now->lson);
            ans.first = min(ans.first, range1.first);
            ans.second = max(ans.second, range1.second);
            pair<int, int> range2 = query(now->rson->left, r, now->rson);
            ans.first = min(ans.first, range2.first);
            ans.second = max(ans.second, range2.second);
        }
        return ans;
    }
} mtree;

int val[MAXN];
int ans[MAXN];

signed main(void) {
    // Problem ID: HDU 5861 (TLE -> AC)
    // Link: http://acm.hdu.edu.cn/showproblem.php?pid=5861
    int n, m;
    mtree.init(); // init once
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(ans, 0, sizeof(ans));
        mtree.build(1, n - 1, mtree.root);
        for (int i = 1; i <= n - 1; ++i) scanf("%d", &val[i]);
        for (int i = 1; i <= m; ++i) {
            int l, r;
            scanf("%d%d", &l, &r);
            if (l > r) swap(l, r);
            mtree.rangeChange(l, r - 1, mtree.root, i);
        }
        for (int i = 1; i <= n - 1; ++i) {
            pair<int, int> tmp = mtree.query(i, i, mtree.root);
            // n^2 TLE
            if (tmp.first <= m) ans[tmp.first] += val[i];
            if (tmp.second > 0) ans[tmp.second + 1] -= val[i];
        }
        for (int i = 1; i <= m; ++i) {
            // sum prefix optimize
            ans[i] += ans[i - 1];
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
