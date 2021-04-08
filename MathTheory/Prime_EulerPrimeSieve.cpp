/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-01 23:35:51
 * @FilePath            : /CodeShelf/MathTheory/Prime_Euler.cpp
 * @Forward Declaration : None
 * @Discription         : 
 *  Prime (Euler)
 *  Time Complexity: O(n)
 */

#include <cstring>
// #define int long long
const int MAXN = 1e5 + 7;

bool vis[MAXN];
int prime[MAXN];

void primeSieve(int n, int *prime, bool *vis)
{
    // Get Prime in Range [0, n)
    // use prime[0] as cnt
    // Time Complexity: O(N)
    memset(vis, 0, sizeof(vis));
    memset(prime, 0, sizeof(prime));
    prime[0] = 0;
    // Use index 0 as Cnt
    for (int i = 2; i < n; i++)
    {
        if (!vis[i])
            prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0] && i * prime[j] < n; j++)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    return 0;
}