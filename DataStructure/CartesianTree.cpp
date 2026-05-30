/**
 * @Author              : NogiNonoka
 * @Date                : 2026-05-31
 * @FilePath            : /CodeShelf/DataStructure/CartesianTree.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Cartesian Tree
 *  Heap property + inorder = original sequence
 *  Time Complexity: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 7;

struct CartesianTree {
    int l[MAXN], r[MAXN], stk[MAXN];
    int root;

    void build(int a[], int n) {
        int top = 0;
        for (int i = 1; i <= n; ++i) {
            int k = top;
            while (k > 0 && a[stk[k]] > a[i]) --k;
            if (k) r[stk[k]] = i;
            if (k < top) l[i] = stk[k + 1];
            stk[++k] = i;
            top = k;
        }
        root = stk[1];
    }

    void clear(int n) {
        for (int i = 1; i <= n; ++i) l[i] = r[i] = 0;
    }
} ct;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    static int a[MAXN];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ct.clear(n);
    ct.build(a, n);
    // parent array can be derived from l, r
    for (int i = 1; i <= n; ++i)
        cout << ct.l[i] << " " << ct.r[i] << "\n";
    return 0;
}
