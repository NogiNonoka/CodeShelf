/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-31
 * @FilePath            : /CodeShelf/DataStructure/LinkCutTree.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Link-Cut Tree (LCT)
 *  Dynamic tree with path queries and link/cut operations
 *  Time Complexity: O(logN) amortized per op
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 7;

struct LinkCutTree {
    int ch[MAXN][2], fa[MAXN];
    bool rev[MAXN];
    int val[MAXN], sum[MAXN];

    bool isRoot(int x) {
        return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
    }

    void pushup(int x) {
        sum[x] = val[x] ^ sum[ch[x][0]] ^ sum[ch[x][1]];
    }

    void pushrev(int x) {
        if (!x) return;
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }

    void pushdown(int x) {
        if (rev[x]) {
            pushrev(ch[x][0]);
            pushrev(ch[x][1]);
            rev[x] = 0;
        }
    }

    void rotate(int x) {
        int y = fa[x], z = fa[y];
        int dir = (ch[y][1] == x);
        if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
        fa[x] = z;
        ch[y][dir] = ch[x][dir ^ 1];
        if (ch[x][dir ^ 1]) fa[ch[x][dir ^ 1]] = y;
        ch[x][dir ^ 1] = y;
        fa[y] = x;
        pushup(y);
        pushup(x);
    }

    int stk[MAXN], top;

    void splay(int x) {
        stk[top = 1] = x;
        for (int y = x; !isRoot(y); y = fa[y]) stk[++top] = fa[y];
        while (top) pushdown(stk[top--]);
        while (!isRoot(x)) {
            int y = fa[x], z = fa[y];
            if (!isRoot(y))
                (ch[y][1] == x) ^ (ch[z][1] == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
    }

    void access(int x) {
        int last = 0;
        for (int y = x; y; y = fa[y]) {
            splay(y);
            ch[y][1] = last;
            pushup(y);
            last = y;
        }
        splay(x);
    }

    void makeRoot(int x) {
        access(x);
        pushrev(x);
    }

    int findRoot(int x) {
        access(x);
        while (true) {
            pushdown(x);
            if (!ch[x][0]) break;
            x = ch[x][0];
        }
        splay(x);
        return x;
    }

    void link(int x, int y) {
        makeRoot(x);
        if (findRoot(y) != x) fa[x] = y;
    }

    void cut(int x, int y) {
        makeRoot(x);
        access(y);
        if (ch[y][0] == x && !ch[x][1]) {
            ch[y][0] = fa[x] = 0;
            pushup(y);
        }
    }

    int query(int x, int y) {
        makeRoot(x);
        access(y);
        return sum[y];
    }

    void modify(int x, int v) {
        splay(x);
        val[x] = v;
        pushup(x);
    }
} lct;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> lct.val[i];
        lct.sum[i] = lct.val[i];
    }
    while (m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 0) {
            cout << lct.query(x, y) << "\n";
        } else if (op == 1) {
            lct.link(x, y);
        } else if (op == 2) {
            lct.cut(x, y);
        } else {
            lct.modify(x, y);
        }
    }
    return 0;
}
