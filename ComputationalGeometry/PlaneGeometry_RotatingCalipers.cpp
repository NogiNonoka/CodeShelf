/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-31
 * @FilePath            : /CodeShelf/ComputationalGeometry/PlaneGeometry_RotatingCalipers.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Rotating Calipers
 *  Diameter, minimum enclosing rectangle, closest pair on convex hull
 *  Time Complexity: O(N)
 */

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int sgn(double x) { return (x > EPS) - (x < -EPS); }

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    double cross(const Point& o) const { return x * o.y - y * o.x; }
    double dot(const Point& o) const { return x * o.x + y * o.y; }
    double len2() const { return dot(*this); }
    double len() const { return sqrt(len2()); }
    bool operator<(const Point& o) const {
        if (sgn(x - o.x)) return x < o.x;
        return y < o.y;
    }
};

vector<Point> convexHull(vector<Point>& p) {
    sort(p.begin(), p.end());
    int n = p.size();
    if (n <= 1) return p;
    vector<Point> res;
    for (int i = 0; i < n; ++i) {
        while (res.size() > 1 && sgn((res.back() - res[res.size()-2]).cross(p[i] - res.back())) <= 0)
            res.pop_back();
        res.push_back(p[i]);
    }
    int k = res.size();
    for (int i = n - 2; i >= 0; --i) {
        while (res.size() > k && sgn((res.back() - res[res.size()-2]).cross(p[i] - res.back())) <= 0)
            res.pop_back();
        res.push_back(p[i]);
    }
    res.pop_back();
    return res;
}

// Diameter of convex hull (rotating calipers)
double rotatingCalipersDiameter(const vector<Point>& hull) {
    int n = hull.size();
    if (n == 1) return 0;
    if (n == 2) return (hull[0] - hull[1]).len();
    double res = 0;
    int j = 1;
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        while (sgn((hull[ni] - hull[i]).cross(hull[(j+1)%n] - hull[j])) > 0)
            j = (j + 1) % n;
        res = max(res, (hull[i] - hull[j]).len());
        res = max(res, (hull[ni] - hull[j]).len());
    }
    return res;
}

// Minimum distance between two points on convex hull (closest pair variant)
double closestPairOnHull(const vector<Point>& hull) {
    int n = hull.size();
    if (n <= 1) return 0;
    double res = 1e300;
    int j = 1;
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        while (sgn((hull[ni] - hull[i]).cross(hull[(j+1)%n] - hull[j])) > 0)
            j = (j + 1) % n;
        double d = fabs((hull[ni] - hull[i]).cross(hull[j] - hull[i])) / (hull[ni] - hull[i]).len();
        res = min(res, d);
    }
    return res;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    vector<Point> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
    auto hull = convexHull(p);
    printf("%.10f\n", rotatingCalipersDiameter(hull));
    return 0;
}
