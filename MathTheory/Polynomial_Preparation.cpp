/*
 * @Author              : NogiNonoka
 * @Date                : 2021-08-09 22:18:53
 * @FilePath            : /CodeShelf/MathTheory/Polynomial_Preparation.cpp
 * @Forward Declaration : None
 * @Discription         : 
 */

#include <bits/stdc++.h>

void polyMul(vector<int>& a, vector<int>& b) {
    // a = a * b
    a.resize(a.size() + b.size() - 1, 0);
    for (int i = a.size() - 1; i >= 0; --i) {
        int tmp = 0;
        for (int j = 0; j < b.size() && j <= i; ++j) { tmp += a[i - j] * b[j]; }
        a[i] = tmp;
    }
}

void polyDinv(vector<int>& a, vector<int>& b) {
    // a = a / b
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {}
    }
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    return 0;
}