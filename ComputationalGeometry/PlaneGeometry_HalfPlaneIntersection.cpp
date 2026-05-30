/*
 * @Author              : NogiNonoka
 * @Date                : 2026-05-31
 * @FilePath            : /CodeShelf/ComputationalGeometry/PlaneGeometry_HalfPlaneIntersection.cpp
 * @Forward Declaration : None
 * @Discription         :
 * @GeneratedBy        : Claude Code (Anthropic)
 * @Model              : model1 (user-provided API)
 *  Half-Plane Intersection
 *  Compute intersection of half-planes (polygon kernel)
 *  Time Complexity: O(NlogN)
 */

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int sgn(double x) { return (x > EPS) - (x < -EPS); }

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    double cross(const Point& o) const { return x * o.y - y * o.x; }
};

struct Line {
    Point s, e;
    double angle;
    Line() {}
    Line(Point _s, Point _e) : s(_s), e(_e) {
        angle = atan2(e.y - s.y, e.x - s.x);
    }
    bool operator<(const Line& o) const {
        if (sgn(angle - o.angle)) return angle < o.angle;
        return sgn((e - s).cross(o.s - s)) > 0;
    }
};

Point lineIntersect(Line a, Line b) {
    Point u = a.s - b.s, v = a.e - a.s, w = b.e - b.s;
    double t = w.cross(u) / v.cross(w);
    return a.s + v * t;
}

bool onLeft(Line l, Point p) {
    return sgn((l.e - l.s).cross(p - l.s)) >= 0;
}

vector<Point> halfPlaneIntersection(vector<Line>& lines) {
    sort(lines.begin(), lines.end());
    deque<Line> dq;
    deque<Point> pts;
    dq.push_back(lines[0]);
    for (size_t i = 1; i < lines.size(); ++i) {
        if (!sgn(lines[i].angle - lines[i - 1].angle)) continue;
        while (pts.size() && !onLeft(lines[i], pts.back())) {
            pts.pop_back();
            dq.pop_back();
        }
        while (pts.size() && !onLeft(lines[i], pts.front())) {
            pts.pop_front();
            dq.pop_front();
        }
        pts.push_back(lineIntersect(dq.back(), lines[i]));
        dq.push_back(lines[i]);
    }
    while (pts.size() > 1 && !onLeft(dq.front(), pts.back())) {
        pts.pop_back();
        dq.pop_back();
    }
    while (pts.size() > 1 && !onLeft(dq.back(), pts.front())) {
        pts.pop_front();
        dq.pop_front();
    }
    if (dq.size() < 3) return {};
    pts.push_back(lineIntersect(dq.front(), dq.back()));
    return vector<Point>(pts.begin(), pts.end());
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin >> n;
    vector<Line> lines;
    for (int i = 0; i < n; ++i) {
        Point a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        lines.push_back(Line(a, b));
    }
    auto res = halfPlaneIntersection(lines);
    cout << res.size() << endl;
    return 0;
}
