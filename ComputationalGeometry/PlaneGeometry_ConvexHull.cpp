/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-26 08:35:43
 * @FilePath            : /CodeShelf/ComputationalGeometry/PlaneGeometry_ConvexHull.cpp
 * /CodeShelf/ComputationalGeometry/PlaneGeometry_ConvexHull.cpp
 * @Forward Declaration : Point
 * @Discription         :
 *  Calc Convex Hull in plane
 *  Time Complexity: O(NlogN)
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
// const int MAXN = ;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
const double eps = 1e-9;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

struct Point {
    double x, y;

    Point(){};
    Point(double x, double y) : x(x), y(y) {}

    Point operator+(const Point& b) { return Point(x + b.x, y + b.y); }
    Point operator-(const Point& b) { return Point(x - b.x, y - b.y); }
    Point operator*(double d) { return Point(x * d, y * d); }

    double dot(const Point& b) { return x * b.x + y * b.y; }
    double det(const Point& b) { return x * b.y - y * b.x; }
    double dis(const Point& b) { return (*this - b).dot((*this - b)); }

    bool operator<(const Point& b) const {
        if (x == b.x) return y < b.y;
        return x < b.x;
    }
};

vector<Point> convexHull(vector<Point>& v) {
    // Andrew Algorithm
    // Time Complexity: O(NlogN)
    sort(v.begin(), v.end());
    vector<Point> ans(v.size() * 2);
    int cnt = 0;
    for (int i = 0; i < v.size(); ++i) {
        while (cnt > 1 &&
            (ans[cnt - 1] - ans[cnt - 2]).det(v[i] - ans[cnt - 1]) <= eps)
            --cnt;
        ans[cnt++] = v[i];
    }
    for (int i = v.size() - 2, tmp = cnt; i > 0; --i) {
        while (cnt > tmp &&
            (ans[cnt - 1] - ans[cnt - 2]).det(v[i] - ans[cnt - 1]) <= eps)
            --cnt;
        ans[cnt++] = v[i];
    }
    ans.resize(cnt);
    // for (auto p : ans)
    // {
    //     cout << "* " << p.x << " " << p.y << endl;
    // }
    return ans;
}

signed main(void) {
    // Problem ID: POJ 2187
    // Link: http://poj.org/problem?id=2187
    int n;
    while (cin >> n) {
        vector<Point> v(n);
        for (int i = 0; i < n; ++i) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            v[i] = (Point(x, y));
        }
        vector<Point> ans = convexHull(v);
        double dis = 0;
        for (int i = 0; i < ans.size(); ++i) {
            for (int j = 0; j < i; ++j) { dis = max(dis, ans[i].dis(ans[j])); }
        }
        printf("%.0f\n", dis);
    }
    return 0;
}

/*
8
0 5
1 8
3 4
5 0
6 2
6 6
8 3
8 7
*/