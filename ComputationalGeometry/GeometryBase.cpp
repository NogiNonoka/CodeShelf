/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-30
 * @FilePath            : /CodeShelf/ComputationalGeometry/GeometryBase.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  2D Point / Vector Base Class
 *  Common operations for computational geometry
 *  Time Complexity: O(1) per op
 */

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int sgn(double x) { return (x > EPS) - (x < -EPS); }

typedef double T;

struct Point {
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}

    Point operator+(const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point &o) const { return Point(x - o.x, y - o.y); }
    Point operator*(T k) const { return Point(x * k, y * k); }
    Point operator/(T k) const { return Point(x / k, y / k); }

    T dot(const Point &o) const { return x * o.x + y * o.y; }
    T cross(const Point &o) const { return x * o.y - y * o.x; }
    T len2() const { return dot(*this); }
    double len() const { return sqrt(len2()); }

    Point rot90() const { return Point(-y, x); }
    Point normalize() const { return *this / len(); }

    double angle() const { return atan2(y, x); }
    Point rotate(double rad) const {
        return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
    }

    bool operator<(const Point &o) const {
        return sgn(x - o.x) < 0 || (sgn(x - o.x) == 0 && sgn(y - o.y) < 0);
    }
    bool operator==(const Point &o) const {
        return sgn(x - o.x) == 0 && sgn(y - o.y) == 0;
    }
    bool operator!=(const Point &o) const { return !(*this == o); }

    friend ostream &operator<<(ostream &os, const Point &p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

// Distance from point p to line ab
double pointToLine(const Point &p, const Point &a, const Point &b) {
    return abs((b - a).cross(p - a)) / (b - a).len();
}

// Distance from point p to segment ab
double pointToSeg(const Point &p, const Point &a, const Point &b) {
    if (sgn((p - a).dot(b - a)) < 0) return (p - a).len();
    if (sgn((p - b).dot(a - b)) < 0) return (p - b).len();
    return pointToLine(p, a, b);
}

// Projection of point p onto line ab
Point proj(const Point &p, const Point &a, const Point &b) {
    Point v = b - a;
    return a + v * ((p - a).dot(v) / v.len2());
}

// Check if segments ab and cd intersect
bool segIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    auto cross = [](const Point &a, const Point &b, const Point &c) {
        return (b - a).cross(c - a);
    };
    if (sgn(cross(a, b, c)) * sgn(cross(a, b, d)) < 0 &&
        sgn(cross(c, d, a)) * sgn(cross(c, d, b)) < 0)
        return true;
    // Check collinear cases
    auto onSeg = [](const Point &p, const Point &a, const Point &b) {
        return sgn((p - a).cross(b - a)) == 0 && sgn((p - a).dot(p - b)) <= 0;
    };
    return onSeg(c, a, b) || onSeg(d, a, b) || onSeg(a, c, d) || onSeg(b, c, d);
}

// Intersection of lines ab and cd (assuming not parallel)
Point lineIntersect(const Point &a, const Point &b, const Point &c, const Point &d) {
    Point v1 = b - a, v2 = d - c;
    T s = (c - a).cross(v2) / v1.cross(v2);
    return a + v1 * s;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    Point a(0, 0), b(4, 0), c(2, 3);
    cout << "cross: " << (b - a).cross(c - a) << endl;
    cout << "dist to line: " << pointToLine(c, a, b) << endl;
    cout << "intersect: " << segIntersect(a, b, Point(2, -1), Point(2, 1)) << endl;
    return 0;
}
