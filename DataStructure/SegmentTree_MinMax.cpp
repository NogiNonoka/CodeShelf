/*
 * @Author              : NogiNonoka
 * @Date                : 2021-01-25 22:34:25
 * @FilePath            : /CodeShelf/DataStructure/SegmentTree_MinMax.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : claude-opus-4-8
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
    } nodes[MAXN << 2];

    int cnt;
    int root;

    void init() { cnt = 0; root = ++cnt; }

    void update(int now) {
        nodes[now].mini = min(min(nodes[nodes[now].lson].mini, nodes[nodes[now].lson].mintag),
            min(nodes[nodes[now].rson].mini, nodes[nodes[now].rson].mintag));
        nodes[now].maxi = max(max(nodes[nodes[now].lson].maxi, nodes[nodes[now].lson].maxtag),
            max(nodes[nodes[now].rson].maxi, nodes[nodes[now].rson].maxtag));
    }

    void build(int l, int r, int now) {
        nodes[now].left = l;
        nodes[now].right = r;
        if (l == r) {
            nodes[now].lson = nodes[now].rson = 0;
            nodes[now].mini = INF;
            nodes[now].maxi = 0;
            nodes[now].mintag = INF;
            nodes[now].maxtag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        nodes[now].lson = ++cnt;
        nodes[now].rson = ++cnt;
        build(l, mid, nodes[now].lson);
        build(mid + 1, r, nodes[now].rson);
        update(now);
        nodes[now].mintag = INF;
        nodes[now].maxtag = 0;
    }

    void rangeChange(int l, int r, int now, int tg) {
        if (nodes[now].left == l && nodes[now].right == r) {
            nodes[now].mintag = min(nodes[now].mintag, tg);
            nodes[now].maxtag = max(nodes[now].maxtag, tg);
            return;
        }
        if (r <= nodes[nodes[now].lson].right)
            rangeChange(l, r, nodes[now].lson, tg);
        else if (l >= nodes[nodes[now].rson].left)
            rangeChange(l, r, nodes[now].rson, tg);
        else {
            rangeChange(l, nodes[nodes[now].lson].right, nodes[now].lson, tg);
            rangeChange(nodes[nodes[now].rson].left, r, nodes[now].rson, tg);
        }
        update(now);
    }

    void pushdown(int now) {
        nodes[now].mini = min(nodes[now].mini, nodes[now].mintag);
        nodes[now].maxi = max(nodes[now].maxi, nodes[now].maxtag);
        if (nodes[now].left == nodes[now].right) return;
        nodes[nodes[now].lson].mintag = min(nodes[nodes[now].lson].mintag, nodes[now].mintag);
        nodes[nodes[now].lson].maxtag = max(nodes[nodes[now].lson].maxtag, nodes[now].maxtag);
        nodes[nodes[now].rson].mintag = min(nodes[nodes[now].rson].mintag, nodes[now].mintag);
        nodes[nodes[now].rson].maxtag = max(nodes[nodes[now].rson].maxtag, nodes[now].maxtag);
    }

    pair<int, int> query(int l, int r, int now) {
        pair<int, int> ans; // Range [l, r] Min && Max
        ans.first = INF;
        ans.second = 0;
        if (nodes[now].left == l && nodes[now].right == r) {
            pushdown(now);
            ans.first = min(ans.first, nodes[now].mini);
            ans.second = max(ans.second, nodes[now].maxi);
            return ans;
        }
        pushdown(now);
        if (r <= nodes[nodes[now].lson].right) {
            pair<int, int> range = query(l, r, nodes[now].lson);
            ans.first = min(ans.first, range.first);
            ans.second = max(ans.second, range.second);
        } else if (l >= nodes[nodes[now].rson].left) {
            pair<int, int> range = query(l, r, nodes[now].rson);
            ans.first = min(ans.first, range.first);
            ans.second = max(ans.second, range.second);
        } else {
            pair<int, int> range1 = query(l, nodes[nodes[now].lson].right, nodes[now].lson);
            ans.first = min(ans.first, range1.first);
            ans.second = max(ans.second, range1.second);
            pair<int, int> range2 = query(nodes[nodes[now].rson].left, r, nodes[now].rson);
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
