/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/Others/MosAlgorithm.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Mo's Algorithm (Sqrt Decomposition)
 *  Offline range query with O((N+Q)*sqrt(N))
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 7;

struct Query {
    int l, r, id, block;
} q[MAXN];

int a[MAXN], ans[MAXN];
int cnt[MAXN];
int curAns;
int blockSize;

bool cmp(const Query& a, const Query& b) {
    if (a.block != b.block) return a.l < b.l;
    return (a.block & 1) ? a.r > b.r : a.r < b.r;
}

void add(int x) {
    // customize by problem
    // example: count distinct
    // if (++cnt[a[x]] == 1) ++curAns;
}

void remove(int x) {
    // customize by problem
    // example: count distinct
    // if (--cnt[a[x]] == 0) --curAns;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    blockSize = max(1, (int)sqrt(n));
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
        q[i].block = q[i].l / blockSize;
    }
    sort(q, q + m, cmp);
    int L = 1, R = 0;
    for (int i = 0; i < m; ++i) {
        while (L > q[i].l) add(--L);
        while (R < q[i].r) add(++R);
        while (L < q[i].l) remove(L++);
        while (R > q[i].r) remove(R--);
        ans[q[i].id] = curAns;
    }
    for (int i = 0; i < m; ++i)
        cout << ans[i] << "\n";
    return 0;
}
