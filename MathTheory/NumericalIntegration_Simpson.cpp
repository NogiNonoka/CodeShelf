/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-31
 * @FilePath            : /CodeShelf/MathTheory/NumericalIntegration_Simpson.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Simpson Integration
 *  Adaptive Simpson's rule for numerical integration
 *  Time Complexity: O(1/eps) evaluations
 */

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

// Define your function here
double f(double x) {
    // Example: integrate sin(x)
    return sin(x);
}

double simpson(double l, double r) {
    double mid = (l + r) / 2.0;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6.0;
}

double asr(double l, double r, double eps, double S) {
    double mid = (l + r) / 2.0;
    double L = simpson(l, mid), R = simpson(mid, r);
    if (fabs(L + R - S) <= 15 * eps)
        return L + R + (L + R - S) / 15.0;
    return asr(l, mid, eps / 2.0, L) + asr(mid, r, eps / 2.0, R);
}

double integrate(double l, double r) {
    return asr(l, r, EPS, simpson(l, r));
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    double l, r;
    cin >> l >> r;
    printf("%.10f\n", integrate(l, r));
    return 0;
}
