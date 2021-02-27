/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-26 20:35:23
 * @FilePath            : /CodeShelf/ComputationalGeometry/SolidGeometry_MinimumCoveringBall.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Minimum Covering Ball in 3D Coordinate
 *  Time Complexity: O(N)
 *  if N < 100 use Ternary Search or Simulated Annealing
 */
#include <bits/stdc++.h>
const int MAXN = 2e5 + 7;
const double eps = 1e-8;

struct MinimumCoveringBall
{
    // Minimum Covering Ball in 3D Coordinate
    // Time Complexity: O(N)
    // if N < 100 use Ternary Search or Simulated Annealing
    struct Point
    {
        double x, y, z;
    }point[200007], outer[4], res;;

    double rad, tmp;
    int npoint, nouter;

    double dis(Point p1, Point p2)
    {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double dz = p1.z - p2.z;
        return (dx * dx + dy * dy + dz * dz);
    }

    double dot(Point p1, Point p2)
    {
        return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
    }

    void ball()
    {
        Point q[3];
        double m[3][3], sol[3], L[3], det;
        int i, j;
        res.x = res.y = res.z = rad = 0;
        switch (nouter)
        {
            case 1:
                res = outer[0];
                break;
            case 2:
                res.x = (outer[0].x + outer[1].x) / 2;
                res.y = (outer[0].y + outer[1].y) / 2;
                res.z = (outer[0].z + outer[1].z) / 2;
                rad = dis(res, outer[0]);
                break;
            case 3:
                for (int i = 0; i < 2; i++)
                {
                    q[i].x = outer[i + 1].x - outer[0].x;
                    q[i].y = outer[i + 1].y - outer[0].y;
                    q[i].z = outer[i + 1].z - outer[0].z;
                }
                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 2; j++)
                        m[i][j] = dot(q[i], q[j]) * 2;
                for (int i = 0; i < 2; i++)
                    sol[i] = dot(q[i], q[i]);
                if (fabs(det = m[0][0] * m[1][1] - m[0][1] * m[1][0]) < eps)
                    return;
                L[0] = (sol[0] * m[1][1] - sol[1] * m[0][1]) / det;
                L[1] = (sol[1] * m[0][0] - sol[0] * m[1][0]) / det;
                res.x = outer[0].x + q[0].x * L[0] + q[1].x * L[1];
                res.y = outer[0].y + q[0].y * L[0] + q[1].y * L[1];
                res.z = outer[0].z + q[0].z * L[0] + q[1].z * L[1];
                rad = dis(res, outer[0]);
                break;
            case 4:
                for (int i = 0; i < 3; i++)
                {
                    q[i].x = outer[i + 1].x - outer[0].x;
                    q[i].y = outer[i + 1].y - outer[0].y;
                    q[i].z = outer[i + 1].z - outer[0].z;
                    sol[i] = dot(q[i], q[i]);
                }
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        m[i][j] = dot(q[i], q[j]) * 2;
                det = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[2][1] * m[1][0] - m[0][2] * m[1][1] * m[2][0] - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];
                if (fabs(det) < eps)
                    return;
                for (int j = 0; j < 3; j++)
                {
                    for (int i = 0; i < 3; i++)
                        m[i][j] = sol[i];
                    L[j] = (m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[2][1] * m[1][0] - m[0][2] * m[1][1] * m[2][0] - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1]) / det;
                    for (int i = 0; i < 3; i++)
                        m[i][j] = dot(q[i], q[j]) * 2;
                }
                res = outer[0];
                for (int i = 0; i < 3; i++)
                {
                    res.x += q[i].x * L[i];
                    res.y += q[i].y * L[i];
                    res.z += q[i].z * L[i];
                }
                rad = dis(res, outer[0]);
        }
    }

    void minBall(int n)
    {
        ball();
        if (nouter < 4)
            for (int i = 0; i < n; i++)
                if (dis(res, point[i]) - rad > eps)
                {
                    outer[nouter] = point[i];
                    ++nouter;
                    minBall(i);
                    --nouter;
                    if (i > 0)
                    {
                        Point tmp = point[i];
                        memmove(&point[1], &point[0], sizeof(Point) * i);
                        point[0] = tmp;
                    }
                }
    }

    double minimumCoveringBall()
    {
        rad = -1;
        for (int i = 0; i < npoint; i++)
        {
            if (dis(res, point[i]) - rad > eps)
            {
                nouter = 1;
                outer[0] = point[i];
                minBall(i);
            }
        }
        return sqrt(rad);
    }
}mcb;

int main()
{
    // Problem: ICPC 2018 Nanjing D
    // Link: https://codeforces.com/gym/101981/attachments
    scanf("%d", &mcb.npoint);
    for (int i = 0; i < mcb.npoint; i++)
        scanf("%lf%lf%lf", &mcb.point[i].x, &mcb.point[i].y, &mcb.point[i].z);
    double ans = mcb.minimumCoveringBall();
    printf("%.12f\n", ans);
    return 0;
}