/*
 * @Author              : NogiNonoka
 * @Date                : 2021-04-01 10:18:59
 * @FilePath            : /CodeShelf/MathTheory/Prime_Mobius.cpp
 * @Forward Declaration : None
 * @Discription         : 
 */

#include <bits/stdc++.h>
using namespace std;
// #define int long long
// #define double long double
// #define endl "\n"
const int MAXN = 1e5 + 7;
// const int MAXE = ;
// const int MOD = ;
// const int INF = ;
// const double eps = ;
// const double PI = acos(-1);
// const int DIRX[] = {};
// const int DIRY[] = {};

int prime[MAXN];
bool vis[MAXN];
int mobius[MAXN];

void mobiusSieve(int n, int *prime, bool *vis, int *mobius)
{
    prime[0] = 0;
    mobius[1] = 1;
    for (int i = 2; i < n; ++i)
    {
        if (!vis[i])
            prime[++prime[0]] = i, mobius[i] = -1;
        for (int j = 1; j <= prime[0]; ++j)
        {
            if (i * prime[j] > n)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                mobius[i * prime[j]] = 0;
                break;
            }
            else 
                mobius[i * prime[j]] = -mobius[i];
        }

    }
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    return 0;
}