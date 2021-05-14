/*
 * @Author              : NogiNonoka
 * @Date                : 2021-05-14 15:58:19
 * @FilePath            : /CodeShelf/DataStructure/BST_Splay.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Binary Search Tree (Splay)
 *  Time Complexity: O(logN) 
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
#define endl "\n"
const int MAXN = 1e5 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

#define DEBUG

struct Node
{
    int fa, ch[2];
    int cnt;
    int size;
    int val;
} node[MAXN];

int cnt, root;

void init()
{
    // set cnt = 0, root will start from 1
    for (int i = 0;i <= cnt; ++i)
    {
        node[cnt].fa = 0;
        node[cnt].ch[0] = node[cnt].ch[1] = 0;
        node[cnt].cnt = 0;
        node[cnt].size = 0;
        node[cnt].val = 0;
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

void rotate(int x)
{
    int f = node[x].fa;
    int g = node[f].fa;
    bool fs = (node[f].ch[1] == x);
    bool gs = (node[g].ch[1] == f);
    node[g].ch[gs] = x;
    node[x].fa = g;
    node[f].ch[fs] = node[x].ch[fs ^ 1];
    node[node[x].ch[fs ^ 1]].fa = f;
    node[x].ch[fs ^ 1] = f;
    node[f].fa = x;
    update(f); update(x); update(g);
}

void splay(int x, int p)
{
    // set node[x].fa = p
    // if p == 0 then set root = x;
    if (!x)
        return;
    while (node[x].fa != p)
    {
        int f = node[x].fa;
        int g = node[f].fa;
        if (g != p)
            (node[f].ch[0] == x) ^ (node[g].ch[0] == f) ? rotate(x) : rotate(f);
        rotate(x);
    }
    if (p == 0)
        root = x;
}

void insert(int val)
{
    int u = root;
    int f = node[u].fa;
    while (u && node[u].val != val)
    {
        f = u;
        u = node[u].ch[val > node[u].val];
    }
    if (u)
        node[u].cnt += 1;
    else
    {
        u = ++cnt;
        if (f)
            node[f].ch[val > node[f].val] = u;
        node[u].fa = f;
        node[u].ch[0] = node[u].ch[1] = 0;
        node[u].val = val;
        node[u].cnt = 1;
        node[u].size = 1;
    }
    splay(u, 0);
}

bool find(int val)
{
    // find node[x].val = val, set root = x
    int u = root;
    while (u && node[u].val != val)
        u = node[u].ch[val > node[u].val];
    splay(u, 0);
    return u != 0;
}

int precursor(int val)
{
    // val exists, return node[u].val < val
    bool flg = find(val);
    int u = node[root].ch[0];
    while (u && node[u].ch[1])
        u = node[u].ch[1];
    return u;
}

int succeed(int val)
{
    // val exists, return node[u].val > val
    find(val);
    int u = node[root].ch[1];
    while (u && node[u].ch[0])
        u = node[u].ch[0];
    return u;
}

void remove(int val)
{
    bool flg = find(val);
    if (!flg)
        return;
    int u = root;
    if (node[u].cnt > 1)
    {
        node[u].cnt--;
        update(u);
        return;
    }
    int lson = precursor(val);
    int rson = succeed(val);
    if (!lson && !rson)
    {
        root = 0;
        return;
    }
    if (!lson)
    {
        splay(rson, 0);
        node[rson].ch[0] = 0;
        update(rson);
        return;
    }
    if (!rson)
    {
        splay(lson, 0);
        node[lson].ch[1] = 0;
        update(lson);
    }
    splay(lson, 0);
    splay(rson, lson);
    node[rson].ch[0] = 0;
    update(rson);
    update(lson);
}

int kthQuery(int k)
{
    if (node[root].size < k)
        return -1;
    int u = root;
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

#ifdef DEBUG
void print(int x)
{
    if (x == 0)
        return;
    cout 
        << x << " val: " << node[x].val 
        << " lson: " << node[x].ch[0] << " rson: " << node[x].ch[1] 
        << " size: " << node[x].size << endl;
    print(node[x].ch[0]);
    print(node[x].ch[1]);
}
#endif

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int T;
    cin >> T;
    int opt, val;
    while (T--)
    {
        cin >> opt >> val;
        if (opt == 1)
            insert(val);
        if (opt == 2)
            remove(val);
        if (opt == 3)
        {
            bool flg = find(val);
            if (!flg)
                insert(val);
            cout << node[node[root].ch[0]].size + 1 << endl;
            if (!flg)
                remove(val);
        }
        if (opt == 4)
            cout << kthQuery(val) << endl;
        if (opt == 5)
        {
            bool flg = find(val);
            if (!flg)
                insert(val);
            cout << node[precursor(val)].val << endl;
            if (!flg)
                remove(val);
        }
        if (opt == 6)
        {
            bool flg = find(val);
            if (!flg)
                insert(val);
            cout << node[succeed(val)].val << endl;
            if (!flg)
                remove(val);
        }
        
    }
    return 0;
}

/*
20 
1 964673
5 968705
4 1
3 964673
5 965257
1 915269
1 53283
3 964673
3 53283
3 53283
1 162641
5 973984
1 948119
2 915269
2 53283
6 959161
1 531821
1 967521
2 531821
1 343410
*/