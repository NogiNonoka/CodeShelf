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
        int lson, rson;
        int maxi, mini;
        int maxtag, mintag;
    } pool[MAXN << 2];

    int cnt;
    int root;

    void init() { cnt = 0; root = ++cnt; }

    void update(int now) {
        pool[now].mini = min(min(pool[pool[now].lson].mini, pool[pool[now].lson].mintag),
            min(pool[pool[now].rson].mini, pool[pool[now].rson].mintag));
        pool[now].maxi = max(max(pool[pool[now].lson].maxi, pool[pool[now].lson].maxtag),
            max(pool[pool[now].rson].maxi, pool[pool[now].rson].maxtag));
    }

    void build(int l, int r, int now) {
        pool[now].left = l;
        pool[now].right = r;
        if (l == r) {
            pool[now].lson = pool[now].rson = 0;
            pool[now].mini = INF;
            pool[now].maxi = 0;
            pool[now].mintag = INF;
            pool[now].maxtag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        pool[now].lson = ++cnt;
        pool[now].rson = ++cnt;
        build(l, mid, pool[now].lson);
        build(mid + 1, r, pool[now].rson);
        update(now);
        pool[now].mintag = INF;
        pool[now].maxtag = 0;
    }

    void rangeChange(int l, int r, int now, int tg) {
        if (pool[now].left == l && pool[now].right == r) {
            pool[now].mintag = min(pool[now].mintag, tg);
            pool[now].maxtag = max(pool[now].maxtag, tg);
            return;
        }
        if (r <= pool[pool[now].lson].right)
            rangeChange(l, r, pool[now].lson, tg);
        else if (l >= pool[pool[now].rson].left)
            rangeChange(l, r, pool[now].rson, tg);
        else {
            rangeChange(l, pool[pool[now].lson].right, pool[now].lson, tg);
            rangeChange(pool[pool[now].rson].left, r, pool[now].rson, tg);
        }
        update(now);
    }

    void pushdown(int now) {
        pool[now].mini = min(pool[now].mini, pool[now].mintag);
        pool[now].maxi = max(pool[now].maxi, pool[now].maxtag);
        if (pool[now].left == pool[now].right) return;
        pool[pool[now].lson].mintag = min(pool[pool[now].lson].mintag, pool[now].mintag);
        pool[pool[now].lson].maxtag = max(pool[pool[now].lson].maxtag, pool[now].maxtag);
        pool[pool[now].rson].mintag = min(pool[pool[now].rson].mintag, pool[now].mintag);
        pool[pool[now].rson].maxtag = max(pool[pool[now].rson].maxtag, pool[now].maxtag);
    }

    pair<int, int> query(int l, int r, int now) {
        pair<int, int> ans; // Range [l, r] Min && Max
        ans.first = INF;
        ans.second = 0;
        if (pool[now].left == l && pool[now].right == r) {
            pushdown(now);
            ans.first = min(ans.first, pool[now].mini);
            ans.second = max(ans.second, pool[now].maxi);
            return ans;
        }
        pushdown(now);
        if (r <= pool[pool[now].lson].right) {
            pair<int, int> range = query(l, r, pool[now].lson);
            ans.first = min(ans.first, range.first);
            ans.second = max(ans.second, range.second);
        } else if (l >= pool[pool[now].rson].left) {
            pair<int, int> range = query(l, r, pool[now].rson);
            ans.first = min(ans.first, range.first);
            ans.second = max(ans.second, range.second);
        } else {
            pair<int, int> range1 = query(l, pool[pool[now].lson].right, pool[now].lson);
            ans.first = min(ans.first, range1.first);
            ans.second = max(ans.second, range1.second);
            pair<int, int> range2 = query(pool[pool[now].rson].left, r, pool[now].rson);
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
