/*
 * @Author              : NogiNonoka
 * @Date                : 2021-10-15 17:58:29
 * @FilePath            : /CodeShelf/DataStructure/KD_Tree.cpp
 * @Forward Declaration : None
 * @Discription         : 
 */
#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 2e5 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int n;
double ans;

struct Node {
    double x, y;

    double dis(const Node &b) {
        return (b.x - x) * (b.x - x) + (b.y - y) * (b.y - y);
    }
} node[MAXN];

bool cmpX(const Node &a, const Node &b) {
    return a.x < b.x;
}

bool cmpY(const Node &a, const Node &b) {
    return a.y < b.y;
}

struct KDNode {
    int lson, rson;
    bool dim; // dimension = 0, x-axis; dimension = 1, y-axis
    double l, r, d, u;
} kd[MAXN];

void update(int x) {
    kd[x].l = kd[x].r = node[x].x;
    kd[x].d = kd[x].u = node[x].y;
    int lson = kd[x].lson;
    int rson = kd[x].rson;
    if (lson) {
        kd[x].l = min(kd[x].l, kd[lson].l); kd[x].r = max(kd[x].r, kd[lson].r);
        kd[x].d = min(kd[x].d, kd[lson].d); kd[x].u = max(kd[x].u, kd[lson].u);
    }
    if (rson) {
        kd[x].l = min(kd[x].l, kd[rson].l); kd[x].r = max(kd[x].r, kd[rson].r);
        kd[x].d = min(kd[x].d, kd[rson].d); kd[x].u = max(kd[x].u, kd[rson].u);
    }
}

int build(int l, int r) {
    if (l > r) return 0;
    int mid = l + r >> 1;
    if (l == r) {
        kd[mid].lson = kd[mid].rson = 0;
        update(mid);
        return mid;
    }
    double avx, avy; // average
    double vax, vay; // varience
    for (int i = l; i <= r; ++i) {
        avx += node[i].x;
        avy += node[i].y;
    }
    avx /= 1.0 * (r - l - 1);
    avy /= 1.0 * (r - l - 1);
    for (int i = l; i <= r; ++i) {
        vax += (avx - node[i].x) * (avx - node[i].x);
        vay += (avy - node[i].y) * (avy - node[i].y);
    }
    if (vax >= vay) {
        kd[mid].dim = 0;
        nth_element(node + l, node + mid, node + r + 1, cmpX);
    } else {
        kd[mid].dim = 1;
        nth_element(node + l, node + mid, node + r + 1, cmpY);
    }
    kd[mid].lson = build(l, mid - 1);
    kd[mid].rson = build(mid + 1, r);
    update(mid);
    return mid;
}

double f(int x, int k) {
    double res = 0;
    if (node[x].x < kd[k].l) res += (node[x].x - kd[k].l) * (node[x].x - kd[k].l);
    if (node[x].x > kd[k].r) res += (node[x].x - kd[k].r) * (node[x].x - kd[k].r);
    if (node[x].y < kd[k].d) res += (node[x].y - kd[k].d) * (node[x].y - kd[k].d);
    if (node[x].y > kd[k].u) res += (node[x].y - kd[k].u) * (node[x].y - kd[k].u);
    return res;
}

void query(int x, int l, int r) {
    if (l > r) return;
    int mid = l + r >> 1;
    if (mid != x) ans = min(ans, node[x].dis(node[mid]));
    if (l == r) return;
    double disl = f(x, kd[mid].lson), disr = f(x, kd[mid].rson);
    if (disl <= disr && disl < ans) {
        query(x, l, mid - 1);
        if (disr < ans) query(x, mid + 1, r);
    } else if (disr < disl && disr < ans) {
        query(x, mid + 1, r);
        if (disl < ans) query(x, l, mid - 1);
    }
}

signed main(void) {
    // Problem ID: Luogu P1429
    // Link: https://www.luogu.com.cn/problem/P1429
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> node[i].x >> node[i].y;
    }
    build(1, n);
    ans = 1e18;
    for (int i = 1; i <= n; ++i) {
        query(i, 1, n);
    }
    printf("%.4lf\n", sqrt(ans));
    return 0;
}