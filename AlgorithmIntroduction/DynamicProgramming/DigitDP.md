## 数位 DP

### 解决问题

数位 DP 通常用于解决区间 $[L,\ R]$ 内符合条件的数的个数。

### 算法思想

数位 DP 的实现主要有两种：

- 递推 构建转移方程
- 记忆化搜索

其中，记忆化搜索更易实现且能解决更多问题，本文主要介绍记忆化搜索的实现方式。

### 算法实现

基于 DFS 的记忆化搜索，主要维护**当前位数、条件、数位上限**等参数。

- 通过待求区间上限，计算 $lim$ 得到数位上限与 $pos$ 最大值；
- 递归更新当前条件值 / 数位值等，判断是否处于上限；
- 更新 DP 数组。

```
int lim[];
int pos_max;

function pre(int x)
{
    pos_max = 0;
    while x:
        lim[pos_max++] = x % radix;
        x /= radix;
}

function dfs(int pos, bool condition, bool limit)
{
    if pos == 0:
        return 1;
    if dp[pos][condition][limit]:
        return dp[pos][condition][limit];
    int top = limit ? lim[pos] : digit_max;
    int ans = 0;
    for i = 0 to top:
        if check(i):
            ans += dfs(pos - 1, new_condition, new_limit);
    return dp[pos][condition][limit] = ans;
}
```

### 例题

#### Luogu P2657

链接：[P2657](https://www.luogu.com.cn/problem/P2657)

##### Problem

在区间 $[a,\ b]$ 间不含前导零且相邻两个数字之差至少为 $2$ 的正整数个数。

##### Analysis

- 前缀和思想，处理区间 $[1,\ b] - [1,\ a - 1]$。

##### Code

```C++
#include <bits/stdc++.h>
using namespace std;

int a, b;

int dp[15][15][2][2];
int len;
int lim[15];

void pre(int x)
{
    memset(dp, -1, sizeof(dp));
    len = 0;
    while (x)
    {
        lim[len++] = x % 10;
        x /= 10;
    }
}

int dfs(int now, int pre, bool zero, bool limit)
{
    if (now == -1)
    {
        if (zero)
            return 0;
        else 
            return 1;
    }
    if (~dp[now][pre][zero][limit])
        return dp[now][pre][zero][limit];
    int top = limit ? lim[now] : 9;
    int ans = 0;
    for (int i = 0; i <= top; ++i)
    {
        if (zero || abs(i - pre) >= 2)
            ans += dfs(now - 1, i, zero & (i == 0), limit & (i == lim[now]));
    }
    return dp[now][pre][zero][limit] = ans;
}

void solve()
{
    cin >> a >> b;
    pre(b);
    int ans;
    ans = dfs(len - 1, 0, true, true);
    pre(a - 1);
    ans -= dfs(len - 1, 0, true, true);
    cout << ans << endl;
}

int32_t main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```

#### 2020 ICPC Jinan L - Bit Sequence

链接：[Bit Sequence](https://ac.nowcoder.com/acm/problem/216187)

##### Problem

- 给定长度为 $m \ (1 \le m \le 100)$ 的二进制序列 $a$，$a_i$ 表示 $x + i$ 中 $1$ 个数的奇偶性；
- 询问在区间 $[0,\ l] \ (0 \le l \le 10^{18})$ 内，满足条件的 $x$ 的个数。

##### Analysis

- 注意到 $m \le 100$，故产生变化的位数在最后 $8 \ bit$；
- 同时，后 $8 \ bit$ 可能产生进位对前**连续的** $1$ 个数的奇偶性可能产生影响；
- 故，影响 $a_i$ 的所有可能条件为：
  - 后 $8 \ bit$ 的中 $1$ 个数的奇偶性；
  - 除后 $8 \ bit$ 剩余 $1$ 个数的奇偶性；
  - 产生进位，后 $8 \ bit$ 前**连续的** $1$ 个数的奇偶性。

##### Code

```C++
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5 + 7;

int T;
int m, l;
int a[MAXN];
int lim[70];
int dp[70][2][2][2];
int cnt[130];

void pre()
{
    cnt[0] = 0;
    for (int i = 1; i < 128; i++)
        cnt[i] = (cnt[i >> 1] + (i & 1)) % 2;
}

int cal(bool sum, bool one, bool limit)
{
    int top = (limit ? l % 128 + 1 : 128);
    int ans = 0;
    for (int i = 0; i < top; i++)
    {
        bool ok = true;
        for (int j = 0; j < m && ok; j++)
        {
            if (i + j < 128)
                ok = ((cnt[i + j] ^ sum) == a[j]);
            else
                ok = ((cnt[(i + j) % 128] ^ (1 - one) ^ sum) == a[j]);
        }
        ans += ok;
    }
    return ans;
}

int dfs(int step, bool sum, bool one, bool limit) // 数位, 1 的总数, 连续 1 的个数, 上限
{
    if (~dp[step][sum][one][limit])
        return dp[step][sum][one][limit];
    if (step <= 6)
        return dp[step][sum][one][limit] = cal(sum, one, limit);
    int top = (limit ? lim[step] : 1);
    int ans = 0;
    for (int i = 0; i <= top; i++)
        ans += dfs(step - 1, sum ^ i, i ? one ^ 1 : 0, limit & (i == top));
    return dp[step][sum][one][limit] = ans;
}

int solve(int x)
{
    memset(dp, -1, sizeof(dp));
    int len = 0;
    while (x)
    {
        lim[len++] = x & 1;
        x >>= 1;
    }
    return dfs(len - 1, 0, 0, true);
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> T;
    pre();
    while (T--)
    {
        cin >> m;
        cin >> l;
        for (int i = 0; i < m; i++)
            cin >> a[i];
        cout << solve(l) << endl;
    }
    return 0;
}
```