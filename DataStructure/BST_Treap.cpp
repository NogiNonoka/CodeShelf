/*
 * @Author              : NogiNonoka
 * @Date                : 2021-05-21 16:34:02
 * @FilePath            : /CodeShelf/DataStructure/BST_Treap.cpp
 * @Forward Declaration : None
 * @Discription         : 
 */
#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
#define endl "\n"
const int MAXN = 1e5 + 7;
// const int MAXE = ;
// const int MOD = ;
const int INF = 0x3f3f3f3f;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Node
{
    int ch[2];
    int val, cnt, size, rand;
} node[MAXN];

int cnt, root;

#define DEBUG
#ifdef DEBUG
void print(int x)
{
    if (x == 0)
        return;
    cout 
        << x << " val: " << node[x].val 
        << " lson: " << node[x].ch[0] << " rson: " << node[x].ch[1] 
        << " size: " << node[x].size << " cnt: " << node[x].cnt  << " rand: " << node[x].rand << endl;
    print(node[x].ch[0]);
    print(node[x].ch[1]);
}
#endif

void init()
{
    // set cnt = 0, root will start from 1
    for (int i = 0;i <= cnt; ++i)
    {
        node[cnt].ch[0] = node[cnt].ch[1] = 0;
        node[cnt].val = node[cnt].cnt = node[cnt].size = 0;
        node[cnt].rand = 0;
    }
    cnt = 0;
    root = 0;
}

void update(int x)
{
    // size of subtree x
    if (x == 0)
        return;
    node[x].size = node[x].cnt;
    if (node[x].ch[0])
        node[x].size += node[node[x].ch[0]].size;
    if (node[x].ch[1])
        node[x].size += node[node[x].ch[1]].size;
}

void rotate(int &x, bool d)
{
    int s = node[x].ch[d ^ 1];
    node[x].ch[d ^ 1] = node[s].ch[d];
    node[s].ch[d] = x;
    x = s;
    update(node[x].ch[d]); update(x);
}

void insert(int &x, int val)
{
    if (!x)
    {
        x = ++cnt;
        node[x].ch[0] = node[x].ch[1] = 0;
        node[x].val = val;
        node[x].cnt = node[x].size = 1;
        node[x].rand = rand();
        return;
    }
    if (node[x].val == val)
        node[x].cnt += 1;
    else
    {
        bool xs = val > node[x].val;
        insert(node[x].ch[xs], val);
        if (node[x].rand < node[node[x].ch[xs]].rand)
            rotate(x, xs ^ 1);
    }
    update(x);
}

void remove(int &x, int val)
{
    if (!x)
        return;
    if (node[x].val != val)
        remove(node[x].ch[val > node[x].val], val);
    else 
    {
        if (node[x].cnt > 1)
            node[x].cnt -= 1;
        else if (!node[x].ch[0] && !node[x].ch[1])
            x = 0;
        else 
        {
            bool xs = node[node[x].ch[1]].rand > node[node[x].ch[0]].rand;
            rotate(x, xs ^ 1);
            remove(node[x].ch[xs ^ 1], val);
        }
    }
    update(x);
}

int ranking(int val)
{
    int x = root, rnk = 1;
    while (x)
    {
        if (node[x].val == val)
            return rnk + node[node[x].ch[0]].size;
        if (node[x].val < val)
            rnk += node[node[x].ch[0]].size + node[x].cnt, x = node[x].ch[1]; 
        else
            x = node[x].ch[0];
    }
    return rnk;
}

int kthQuery(int k)
{
    int u = root;
    if (node[u].size < k)
        return -1;
    while (true)
    {
        int lson = node[u].ch[0];
        int rson = node[u].ch[1];
        if (k > node[lson].size + node[u].cnt)
        {
            k -= node[lson].size + node[u].cnt;
            u = rson;
        }
        else
        {
            if (node[lson].size >= k)
                u = lson;
            else 
                return node[u].val;
        }
    }
}

int precursor(int val)
{
    int x = root, pre = 0;
    while (x) 
    {
        bool xs = val > node[x].val;
        if (xs)
            pre = x;
        x = node[x].ch[xs];
    }
    return pre;
}

int succeeding(int val)
{
    int x = root, suc = 0;
    while (x) 
    {
        bool xs = val >= node[x].val;
        if (!xs)
            suc = x;
        x = node[x].ch[xs];
    }
    return suc;
}

signed main(void)
{
    // Problem ID: Luogu P3369
    // Link: https://www.luogu.com.cn/problem/P3369
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int T;
    cin >> T;
    int opt, val;
    while (T--)
    {
        cin >> opt >> val;
        if (opt == 1)
            insert(root, val);
        if (opt == 2)
            remove(root, val);
        if (opt == 3)
            cout << ranking(val) << endl;
        if (opt == 4)
            cout << kthQuery(val) << endl;
        if (opt == 5)
            cout << node[precursor(val)].val << endl;
        if (opt == 6)
            cout << node[succeeding(val)].val << endl; 
    }
    return 0;
}
