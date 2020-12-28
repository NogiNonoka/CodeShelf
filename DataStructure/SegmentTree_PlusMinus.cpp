/*
 * @Author              : NogiNonoka
 * @Date                : 2020-12-10 10:15:59
 * @FilePath            : /CodeShelf/DataStructure/SegmentTree_PlusMinus.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Segment Tree
 *  Node Change: Plus Minus
 *  Range Change: Plus Minus / Maximum Minimum
 *  Time Complexity: O(NlogN)
 */

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 5e6 + 7;

struct SegmentTree
{
    struct Node
    {
        int left, right;
        Node *lson, *rson;
        int val;
        int tag;
    } *root;

    int data[MAXN];

    void init()
    {
        root = new Node;
    }

    void UpdateNode(Node *now)
    {
        now->val = now->lson->val + now->rson->val;
    }

    void build(int l, int r, Node *now)
    {
        now->left = l;
        now->right = r;
        if (l == r)
        {
            now->lson = nullptr;
            now->rson = nullptr;
            now->val = data[l];
            now->tag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        now->lson = new Node;
        now->rson = new Node;
        build(l, mid, now->lson);
        build(mid + 1, r, now->rson);
        UpdateNode(now);
        now->tag = 0;
    }

    void pushdown(Node *now)
    {
        if (now->left == now->right)
        {
            now->val += now->tag;
            now->tag = 0;
            return;
        }
        now->lson->tag += now->tag;
        now->rson->tag += now->tag;
        now->tag = 0;
    }

    void rangeAdd(int l, int r, Node *now, int tg)
    {
        if (now->left == l && now->right == r)
        {
            now->tag += tg;
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if (r <= now->lson->right)
            rangeAdd(l, r, now->lson, tg);
        else if (l >= now->rson->left)
            rangeAdd(l, r, now->rson, tg);
        else 
        {
            rangeAdd(l, now->lson->right, now->lson, tg);
            rangeAdd(now->rson->left, r, now->rson, tg);
        }
    }

    int query(int l, int r, Node *now)
    {
        int res = 0;
        if (now->left == l && now->right == r)
        {
            pushdown(now);
            res += now->val;
            return res;
        }
        pushdown(now);
        int mid = (now->left + now->right) >> 1;
        if (r <= now->lson->right)
            res += query(l, r, now->lson);
        else if (l >= now->rson->left)
            res += query(l, r, now->rson);
        else 
        {
            res += query(l, now->lson->right, now->lson);
            res += query(now->rson->left, r, now->rson);
        }
        return res;
    }
}stree;

int main(void)
{
    // Problem ID: Luogu P3368
    // Link:https://www.luogu.com.cn/problem/P3368
    int n, m;
    cin >> n >> m;
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (int i = 1; i <= n; ++i)
    {
        cin >> stree.data[i];
    }
    stree.init();
    stree.build(1, n, stree.root);
    for (int i = 1; i <= m; ++i)
    {
        int t;
        cin >> t;
        if (t == 2)
        {
            int x;
            cin >> x;
            cout << stree.query(x, x, stree.root) << endl;
        }
        else 
        {
            int x, y, k;
            cin >> x >> y >> k;
            stree.rangeAdd(x, y, stree.root, k);
        }
    }
}