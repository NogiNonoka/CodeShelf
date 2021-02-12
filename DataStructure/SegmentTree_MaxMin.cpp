/*
 * @Author              : NogiNonoka
 * @Date                : 2021-01-25 22:34:25
 * @FilePath            : /CodeShelf/DataStructure/SegmentTree_MaxMin.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Segment Tree
 *  Node Change: Max Min
 *  Range Change: Max Min (change to new val)
 *  Time Complexity: O(NlogN)
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#define int long long
using namespace std;
const int MAXN = 2e5 + 7;
const int INF = 0x3f3f3f3f;

struct SegmentTreeMaxMin
{
    struct Node
    {
        int left, right;
        Node *lson, *rson;
        int maxi, mini;
        int maxtag, mintag;
        Node(): lson(nullptr), rson(nullptr) {};
    } *root;

    void init()
    {
        root = new Node;
    }

    void update(Node *now)
    {
        now->maxi = max(max(now->lson->maxi, now->lson->maxtag), max(now->rson->maxi, now->rson->maxtag));
        now->mini = min(min(now->lson->mini, now->lson->mintag), min(now->rson->mini, now->rson->mintag));
    }

    void build(int l, int r, Node *now)
    {
        now->left = l;
        now->right = r;
        if (l == r)
        {
            now->lson = nullptr;
            now->rson = nullptr;
            now->maxi = 0;
            now->mini = INF;
            now->maxtag = 0;
            now->mintag = INF;
            return;
        }
        int mid = (l + r) >> 1;
        if (now->lson == nullptr)
            now->lson = new Node;
        if (now->rson == nullptr)
            now->rson = new Node;
        build(l, mid, now->lson);
        build(mid + 1, r, now->rson);
        update(now);
        now->maxtag = 0;
        now->mintag = INF;
    }

    void rangeChange(int l, int r, Node *now, int tg)
    {
        if (now->left == l && now->right == r)
        {
            now->maxtag = max(now->maxtag, tg);
            now->mintag = min(now->mintag, tg);
            return;
        }
        if (r <= now->lson->right)
            rangeChange(l, r, now->lson, tg);
        else if (l >= now->rson->left)
            rangeChange(l, r, now->rson, tg);
        else 
        {
            rangeChange(l, now->lson->right, now->lson, tg);
            rangeChange(now->rson->left, r, now->rson, tg);
        }
        update(now);
    }

    void pushdown(Node *now)
    {
        now->maxi = max(now->maxi, now->maxtag);
        now->mini = min(now->mini, now->mintag);
        if (now->left == now->right)
            return;
        now->lson->maxtag = max(now->lson->maxtag, now->maxtag);
        now->lson->mintag = min(now->lson->mintag, now->mintag);
        now->rson->maxtag = max(now->rson->maxtag, now->maxtag);
        now->rson->mintag = min(now->rson->mintag, now->mintag);
    }
    
    pair<int, int> query(int l, int r, Node *now)
    {
        pair<int, int> ans; // Range [l, r] Max && Min
        ans.first = 0; ans.second = INF;
        if (now->left == l && now->right == r)
        {
            pushdown(now);
            ans.first = max(ans.first, now->maxi);
            ans.second = min(ans.second, now->mini);
            return ans;
        }
        pushdown(now);
        if (r <= now->lson->right)
        {
            pair<int, int> range = query(l, r, now->lson);
            ans.first = max(ans.first, range.first);
            ans.second = min(ans.second, range.second);
        }
        else if (l >= now->rson->left)
        {
            pair<int, int> range = query(l, r, now->rson);
            ans.first = max(ans.first, range.first);
            ans.second = min(ans.second, range.second);
        }
        else 
        {
            pair<int, int> range1 = query(l, now->lson->right, now->lson);
            ans.first = max(ans.first, range1.first),
            ans.second = min(ans.second, range1.second);
            pair<int, int> range2 = query(now->rson->left, r, now->rson);
            ans.first = max(ans.first, range2.first),
            ans.second = min(ans.second, range2.second);
        }
        return ans;
    }

    void clear(Node *now)
    {
        if (now->lson)
            clear(now->lson);
        if (now->rson)
            clear(now->rson);
        delete now;
    }
}mtree;

int val[MAXN];
int ans[MAXN];

int32_t main(void)
{
    // Problem ID: HDU 5861 (TLE -> AC)
    // Link: http://acm.hdu.edu.cn/showproblem.php?pid=5861
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m;
    mtree.init(); // init once
    while (cin >> n >> m)
    {
        memset(ans, 0, sizeof(ans));
        mtree.build(1, n - 1, mtree.root);
        for (int i = 1; i <= n - 1; ++i)
            cin >> val[i];
        for (int i = 1; i <= m; ++i)
        {
            int l, r;
            cin >> l >> r;
            if (l > r) swap(l, r);
            mtree.rangeChange(l, r - 1, mtree.root, i);
        }
        for (int i = 1; i <= n - 1; ++i)
        {
            pair<int, int> tmp = mtree.query(i, i, mtree.root);
            // cout << i << " " << tmp.second << " " << tmp.first << endl;
            for (int j = tmp.second; j <= tmp.first && j <= m; ++j)
                ans[j] += val[i];
        }
        for (int i = 1; i <= m; ++i)
            cout << ans[i] << endl;
        // mtree.clear(mtree.root);
    }
    return 0;
}
