/*
 * @Author              : NogiNonoka
 * @Date                : 2021-04-08 08:14:04
 * @FilePath            : /CodeShelf/DataStructure/PersistmentSegmentTree_kth.cpp
 * @Forward Declaration : None
 * @Discription         : 
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
using namespace std;
const int MAXN = 1e5 + 7;
const int INF = 0x3f3f3f3f;

struct Node
{
    int lson, rson;
    int size;
} node[MAXN * 40];

int cnt, root[MAXN];

void update(int l, int r, int &now, int pre, int x)
{
    node[++cnt] = node[pre];
    now = cnt;
    node[now].size += 1;
    if (l == r)
        return;
    int m = l + r >> 1;
    if (m >= x)
        update(l, m, node[now].lson, node[pre].lson, x);
    else 
        update(m + 1, r, node[now].rson, node[pre].rson, x);
}

int query(int l, int r, int now, int pre, int k)
{
    if (l == r)
        return l;
    int m = l + r >> 1;
    int sum = node[node[now].lson].size - node[node[pre].lson].size;
    if (sum >= k)
        return query(l, m, node[now].lson, node[pre].lson, k);
    else 
        return query(m + 1, r, node[now].rson, node[pre].rson, k - sum);
}

int n, m;
int a[MAXN];
vector<int> v;

signed main(void)
{
    // Problem ID: POJ 2104 / Luogu P3834
    // Link: http://poj.org/problem?id=2104
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    cnt = 0;
    v.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        v[i] = a[i];
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    node[0].size = 0;
    for (int i = 0; i < n; ++i)
    {
        int val = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        update(1, n, root[i + 1], root[i], val);
    }
    int l, r, k;
    for (int i = 1; i <= m; ++i)
    {
        cin >> l >> r >> k;
        cout << v[query(1, n, root[r], root[l - 1], k) - 1] << endl;
    }
    return 0;
}