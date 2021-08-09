/*
 * @Author              : NogiNonoka
 * @Date                : 2020-12-09 08:01:59
 * @FilePath            : /CodeShelf/DataStructure/DisjointUnion_PathZip.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Disjoint Union
 *  Time Complexity:
 *      Search: O(1)
 *      Union: O(logN)
 */

#include <iostream>
using namespace std;
const int MAXN = 1e5 + 7;

struct DisjointUnion {
    int parent[MAXN];
    int n;         // Num of Nodes
    int sum[MAXN]; // (Sum of Val) / Num in each Node (rank < this.rank)
    int rnk[MAXN]; // Rnk of Node in Union

    void initParent(int n) {
        this->n = n;
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            sum[i] = 1;
            rnk[i] = 0;
        }
    }

    int findParent(int x) {
        if (parent[x] == x)
            return x;
        else
            return parent[x] = findParent(parent[x]);
    }

    bool checkUnicom(int x, int y) { return findParent(x) == findParent(y); }

    void mergeNode(int x, int y) {
        x = findParent(x);
        y = findParent(y);
        if (rnk[x] > rnk[y]) {
            parent[y] = x;
            if (x != y) sum[x] += sum[y];
        } else {
            parent[x] = y;
            if (x != y) sum[y] += sum[x];
            if (rnk[x] == rnk[y]) rnk[y] += 1;
        }
    }
} dsu;

int main(void) {
    // Problem ID: Luogu P3367
    // Link: https://www.luogu.com.cn/problem/P3367
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    dsu.initParent(n);
    for (int i = 1; i <= m; ++i) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) { dsu.mergeNode(x, y); }
        if (t == 2) {
            if (dsu.checkUnicom(x, y))
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
    }
    return 0;
}