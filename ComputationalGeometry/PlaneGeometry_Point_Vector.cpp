/*
 * @Author              : NogiNonoka
 * @Date                : 2021-03-26 08:09:39
 * @FilePath            :
 * /CodeShelf/ComputationalGeometry/PlaneGeometry_Point_Vector.cpp
 * @Forward Declaration : None
 * @Discription         :
 *  Point & Vector in plane
 *  dot: dot product
 *  det: cross product
 *  Fucntion add may use instead + for eps
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
// const int MAXN = ;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
const double eps = 1e-8;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

double add(double a, double b) {
    // add with eps
    if (abs(a + b) < eps * (abs(a) + abs(b))) return 0;
    return a + b;
}

int sgn(double x) { return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1); }

struct Point {
    double x, y;

    Point(){};
    Point(double x, double y) : x(x), y(y) {}

    Point operator+(const Point& b) { return Point(x + b.x, y + b.y); }
    Point operator-(const Point& b) { return Point(x - b.x, y - b.y); }
    Point operator*(double d) { return Point(x * d, y * d); }

    double dot(const Point& b) { return x * b.x + y * b.y; }
    double det(const Point& b) { return x * b.y - y * b.x; }
    double dis(const Point& b) { return (*this - b).dot(*this - b); }
};

typedef Point Vector;

double crossProduct(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

double dotProduct(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

bool pointOnSegment(Point p, Point a, Point b) {
    // sgn(crossProduct(a - p, b - p)) == 0 may cause eps problem.
    // If p is on the line, for check on the segment, ignore this condition.
    return sgn(crossProduct(a - p, b - p)) == 0 &&
        sgn(dotProduct(a - p, b - p)) < 0;
}

double disToLine(Point p, Point a, Point b) {
    // Point p, to Line a
    double dis = sqrt(a.dis(b));
    double area = fabs(crossProduct(a - b, p - a));
    // for directed distance, ignore fabs().
    return area / dis;
}

double disToSegment(Point p, Point a, Point b) {
    Vector v1 = p - a, v2 = p - b, v3 = b - a;
    if (sgn(dotProduct(v1, v3)) < 0) return sqrt(p.dis(a));
    if (sgn(dotProduct(v2, v3)) > 0) return sqrt(p.dis(b));
    return disToLine(p, a, b);
}

Point projectionOnLine(Point p, Point a, Point b) {
    Vector v1 = b - a, v2 = p - a;
    return a + v1 * (dotProduct(v1, v2) / sqrt(b.dis(a)));
}

bool segmentIntersection(Point a1, Point a2, Point b1, Point b2) {
    // If A at left side of BC, crossProduct(AB, AC) < 0.
    double c1 = (a2 - a1).det(b1 - a1), c2 = (a2 - a1).det(b2 - a1);
    double d1 = (b2 - b1).det(a1 - b1), d2 = (b2 - b1).det(a2 - b1);
    return sgn(c1) * sgn(c2) < 0 && sgn(d1) * sgn(d2) < 0;
}

Point lineIntersection(Point p, Vector u, Point q, Vector v) {
    // Line 1: I = p + t * u
    // Line 2: I = q + s * v
    Vector w = p - q;
    double t = crossProduct(v, w) / crossProduct(u, v);
    return p + u * t;
}

Point lineIntersection2(Point a1, Point a2, Point b1, Point b2) {
    // Line a: I = a1 + t * (a2 - a1)
    // Line b: I = b1 + s * (b2 - b1)
    // Calc Function based on Cramer's Rule
    Vector u = a2 - a1, v = b2 - b1;
    Vector w = a1 - b1;
    double det0 = -crossProduct(u, v);
    double dett = crossProduct(w, v);
    double dets = -crossProduct(u, w);
    double t = dett / det0, s = dets / det0;
    return a1 + u * t; // == a2 + v * s
}

signed main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    Point p[5];
    for (int i = 1; i <= 4; ++i) { cin >> p[i].x >> p[i].y; }
    Point ans1 = lineIntersection(p[1], p[2] - p[1], p[3], p[4] - p[3]);
    Point ans2 = lineIntersection2(p[1], p[2], p[3], p[4]);
    cout << ans1.x << " " << ans1.y << endl;
    cout << ans2.x << " " << ans2.y << endl;
    cout << segmentIntersection(p[1], p[2], p[3], p[4]) << endl;
    return 0;
}