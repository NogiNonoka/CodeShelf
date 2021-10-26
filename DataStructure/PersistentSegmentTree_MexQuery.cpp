/*
 * @Author              : NogiNonoka
 * @Date                : 2021-04-09 18:06:54
 * @FilePath            : /CodeShelf/DataStructure/PersistentSegmentTree_MexQuery.cpp
 * /CodeShelf/DataStructure/PersistentSegmentTree_MexQuery.cpp
 * @LastEditTime        : 2021-10-13 14:43:49
 * @Forward Declaration : None
 * @Discription         :
 *  Persistent Segment Tree
 *  Mex in range [l, r]:
 *      If set = [1, x], get sum of val = [1, x + 1] , set = [1, sum].
 *  Time Complexity:
 *      Update: O(NlogN)
 *      Query: O(logN)
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
// #define double long double
#define endl "\n"
const int MAXN = 1e6 + 7;
// const int MAXE = ;
// const int MOD = ;
const int INF = 0x3f3f3f3f;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Node {
    int lson, rson;
    int sum, size;
} node[MAXN * 43];

int cnt, root[MAXN];

void update(int l, int r, int& now, int pre, int x) {
    now = ++cnt;
    node[now] = node[pre];
    node[now].sum += x;
    node[now].size += 1;
    if (l == r) return;
    int m = l + r >> 1;
    if (m >= x)
        update(l, m, node[now].lson, node[pre].lson, x);
    else
        update(m + 1, r, node[now].rson, node[pre].rson, x);
}

int query(int l, int r, int now, int pre, int x) {
    if (!now && !pre) return 0;
    if (x < l) return 0;
    if (x >= r) return node[now].sum - node[pre].sum;
    int m = l + r >> 1;
    return query(l, m, node[now].lson, node[pre].lson, x) +
        query(m + 1, r, node[now].rson, node[pre].rson, x);
}

int n, m;
int l, r;
int ans;
int a[MAXN];

signed main(void) {
    // Problem ID: Nowcoder 2020-2021 ICPC Kunming M
    // Link: https://ac.nowcoder.com/acm/contest/12548/M
    scanf("%lld%lld", &n, &m);
    ans = 0;
    cnt = 0;
    root[0] = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        update(1, INF, root[i], root[i - 1], a[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%lld%lld", &l, &r);
        int x = 0;
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if (l > r) swap(l, r);
        // cout << "* " << l << " " << r << endl;
        while (true) {
            int y = query(1, INF, root[r], root[l - 1], x + 1);
            // cout << "** " << x + 1 << " " << y << endl;
            if (y <= x) break;
            x = y;
        }
        ans = x + 1;
        printf("%lld\n", ans);
    }
    return 0;
}