/*
 * @Author              : NogiNonoka
 * @Date                : 2021-07-31 16:15:38
 * @FilePath            : /CodeShelf/MathTheory/LinearAlgebra_MatrixQuickPow.cpp
 * @Forward Declaration : None
 * @Discription         :
 */
#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// const int MAXN = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Matrix {
    static const int MAXL = 100 + 3;
    int len;
    int mat[MAXL][MAXL];

    void nullMatrix() {
        memset(mat, 0, sizeof(mat));
    }

    void eMatrix() {
        memset(mat, 0, sizeof(mat));
        for (int i = 1; i <= len; ++i) {
            mat[i][i] = 1;
        }
    }

    void print() {
        for (int i = 1; i <= len; ++i) {
            for (int j = 1; j <= len; ++j) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    Matrix operator*(const Matrix& b) {
        Matrix c;
        c.nullMatrix();
        for (int i = 1; i <= len; ++i)
            for (int j = 1; j <= len; ++j)
                for (int k = 1; k <= len; ++k)
                    c.mat[i][j] = c.mat[i][j] + mat[i][k] * b.mat[k][j];
        return c;
    }
};

Matrix matrixqPow(Matrix a, int b) {
    Matrix res;
    res.eMatrix();
    for (; b; b >>= 1) {
        if (b & 1)
            res = res * a;
        a = a * a;
    }
    return res;
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}