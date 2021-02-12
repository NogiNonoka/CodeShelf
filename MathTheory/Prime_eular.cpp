/*
 * @Author              : NogiNonoka
 * @Date                : 2021-02-01 23:35:51
 * @FilePath            : /CodeShelf/MathTheory/Prime_Eular.cpp
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

void getPrime(int n)
{
    
    memset(vis, 0, sizeof(vis));
    memset(prime, 0, sizeof(prime));
    prime[0] = 0;
    // Use index 0 as a Cnt
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