/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/DataStructure/LiChaoSegmentTree.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Li Chao Segment Tree
 *  Dynamic line/segment insertion, point query for max/min
 *  Time Complexity: O(logC) per op
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = (int)1e18;

struct Line {
    int k, b;
    Line(int _k = 0, int _b = -INF) : k(_k), b(_b) {}
    int get(int x) const { return k * x + b; }
};

struct LiChao {
    struct Node {
        Line line;
        int lson, rson;
    } tr[(int)4e6];
    int cnt;
    int X_MIN, X_MAX;

    void init(int xl, int xr) {
        cnt = 0;
        X_MIN = xl;
        X_MAX = xr;
    }

    int newNode() {
        tr[++cnt] = {Line(), 0, 0};
        return cnt;
    }

    void insert(Line nw, int l, int r, int& p) {
        if (!p) p = newNode();
        int mid = (l + r) >> 1;
        bool lef = nw.get(l) > tr[p].line.get(l);
        bool m = nw.get(mid) > tr[p].line.get(mid);
        if (m) swap(tr[p].line, nw);
        if (r - l == 0) return;
        if (lef != m) insert(nw, l, mid, tr[p].lson);
        else insert(nw, mid + 1, r, tr[p].rson);
    }

    void insertLine(Line nw) { insert(nw, X_MIN, X_MAX, tr[0].lson); }

    int query(int x, int l, int r, int p) {
        if (!p) return -INF;
        int mid = (l + r) >> 1;
        int res = tr[p].line.get(x);
        if (r - l == 0) return res;
        if (x <= mid) return max(res, query(x, l, mid, tr[p].lson));
        else return max(res, query(x, mid + 1, r, tr[p].rson));
    }

    int query(int x) { return query(x, X_MIN, X_MAX, tr[0].lson); }
} lct;

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, xl, xr;
    cin >> n >> xl >> xr;
    lct.init(xl, xr);
    while (n--) {
        int op, k, b, x;
        cin >> op;
        if (op == 1) {
            cin >> k >> b;
            lct.insertLine(Line(k, b));
        } else {
            cin >> x;
            cout << lct.query(x) << endl;
        }
    }
    return 0;
}
