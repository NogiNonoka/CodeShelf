## Elementary Number Theory

### Preparation

#### Quick Pow

```C++
inline int qpow(int a, int b)
{
    // Calc a ^ b % MOD
    int ans = 1;
    for (; b; b >>= 1, a = a * a % MOD)
        if (b & 1)
            ans = ans * a % MOD;
    return ans;
}
```

#### Quick Mul

```C++
inline int qmul(int a, int b, int p)
{
    // Calc a * b % p
    int ans = 0;
    for (; b; b >>= 1, a = (a << 1) % p)
        if (b & 1)
            ans = (ans + a) % p;
    return ans;
}
```

### Prime

#### Prime Number Theorem

- 素数定理
- 估计不超过 $x$ 的素数个数：$\pi (x) \sim \dfrac{n}{\ln (n)}$

#### Euler

- 欧拉筛（线性筛）
- 时间复杂度：$O(N)$

```C++
bool vis[MAXN];
int prime[MAXN];

void getPrime(int n)
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
```

#### Min_25

（待补）
- Min_25 筛
- 计算积性函数前缀和。

### Congruence Modulo and Inverse Element

剩余与乘法逆元

#### Linear Inverse Element

- 线性求逆元
  - 需要定义模数 $MOD$。

```C++
int inv[MAXN];

void getInv(int n)
{
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    // Multiplicative Inverse
}
```
- 阶乘逆元计算组合数
```C++
int fac[MAXN], inv[MAXN], facinv[MAXN];

void getInv(int n)
{
    fac[0] = 1;
    for (int i = 1; i < n; i++)
        fac[i] = fac[i - 1] * i % MOD;
   	// Factorial
    inv[1] = 1;
    for (int i = 2; i < n; i++)
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    facinv[0] = 1;
    for (int i = 1; i < n; i++)
        facinv[i] = inv[i] * facinv[i - 1] % MOD;
    // Factorials' Muiltiplicative Inverse
}

inline int C(int n, int m)
{
    if (m > n)
        return 0;
    return fac[n] * facinv[m] % MOD * facinv[n - m] % MOD;
}
// C_n^m
```

#### Fermat's Little Theorem

- 费马小定理
- 前置函数：Quick Pow
- 满足 $gcd(a, p) = 1$ 的条件下，$a \cdot a^{-1} \equiv 1 \ (mod \ p)$ 求 $a$ 的逆元 $a^{-1}$:
$$a^{p - 1} \equiv 1 (mod \ p)$$ 
- 故 $a^{-1} \equiv a^{p - 2} = qpow(a, p - 2) \  (mod \ p)$。

#### Extended GCD (Congruent Liner Equation)

- 裴蜀定理：不定方程 $ax + by = gcd(a,b)$ 有解，可扩展到 $n$ 元情况；
- 线性同余方程
  - 形如：$ax \equiv c \ (mod \ b) \Leftrightarrow ax + by = c$
  - 方程有解的条件：$gcd(a,b) | c$；
- 扩展欧几里得
  - 解不定方程 $ax + by = gcd(a, b)$；
  - 判断并求解不定方程 $ax + by = c$；
    - 若 $a \ b$ 不互质，将方程转化为 $\dfrac{a}{gcd(a, b)}x + \dfrac{b}{gcd(a,b)} = \dfrac{c}{gcd(a, b)}$；
    - 求最小非负整数解：记 $t = \dfrac{b}{gcd(a, b)}$，则$x = (x \% t + t) \% t$，代回方程求 $y$。

```C++
int exgcd(int a, int b, int &x, int &y)
{
    // Solve Congruent Liner Equation: ax + by == gcd(a, b), ax = gcd(a, b) (mod b)
    // Minimum Positive Integer Solution: t = b / gcd(a, b), x = (x % t + t) % t
    if (b == 0)
    {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
```

- 扩展欧几里得求逆元

```C++
int inv(int a, int p)
{
    // Calc Inverse Element a^{-1} (mod p)
    int x, y;
    int d = exgcd(a, p, x, y);
    return d == 1 ? (x % p + p) % p : -1;
}
```

#### China Remainder Theorem (Congruent Liner Equation Group)

- 一元线性同余方程组
  - 形如：
$$
\left\{
\begin{array}{l} 
    x \equiv a_1 \ (mod \ p_1) \\
    x \equiv a_2 \ (mod \ p_2) \\
    \dots
\end{array}
\right.
$$
其中 $p_1, p_2 \dots$ 互质。
- 中国剩余定理
  - 前置函数：Extended GCD & Quick Mul
  - 解线性同余方程组；
  - 算法过程：
    - 计算 $m = \Pi p_i$；
    - 对于每一个方程，计算 $n = \dfrac{m}{p_i}$；
    - 计算 $n^{-1} \ (mod \ p_i)$；
    - 计算 $x_i = n * n^{-1} * a[i]$，$x$ 满足 $\forall (p_j \in p, \ i \neq j),\ x \equiv 1 \ (mod \ p_j)$ 且 $x_i \equiv a_i \ (mod \ p_i)$
    - 方程的解为 $ans = \sum x_i (mod \ m)$；

```C++
int crt(vector<int> &a, vector<int> &p)
{
    // Solve Congruent Liner Equation Group: x = a (mod p)
    int ans = 0, m = 1;
    for (int i = 0; i < p.size(); ++i)
        m *= p[i];
    for (int i = 0; i < p.size(); ++i)
    {
        int n = m / p[i];
        int x = inv(n, p[i]); //Solve nx = 1 (mod p) based on exgcd
        ans = (ans + qmul(qmul(n, x, m), (a[i] % m + m) % m, m)) % m;
        // ans = (ans + n * x % m * a[i] % m) % m;
    }
    ans = (ans % m + m) % m;
    return ans;
}
```

- 扩展中国剩余定理
  - 解决方程组模数 $p$ 不互质的情况;
  - 考虑两个方程的情况：
$$
\left\{
\begin{array}{l} 
    x \equiv a_1 \ (mod \ p_1) \\
    x \equiv a_2 \ (mod \ p_2) \\
\end{array}
\right.
$$
    - 根据线性同余方程的性质，方程组可转化为：
$$
\left\{
\begin{array}{l} 
    x = p_1 m + a_1 \\
    x = p_2 n + a_2 \\
\end{array}
\right.  
$$
    - 即 $x = p_1m + a_1 = p_2n + a_2$，化为 $p_1m - p_2n = a_2 - a_1$ 使用 Extended GCD 判断有解 $gcd(p_1, p_2) | a_2 - a_1$ 并解出 $m,\ n$，带回求得 $x$。
  - 对于多个方程的情况：
    - 将前两个方程解得 $x$ 后得到新方程 $x \equiv p_1m + a_1 \ (mod \  lcm(p_1, p_2))$；
    - 递推解两个方程构成的方程组。

#### Quadratic Residue

（待补）
- 二次剩余
- 对于给定的 $p, n$，存在 $x$，使 $x^2 \equiv n (mod \ p)$，那么称 $n$ 为模 $p$ 意义下的二次剩余。

#### Residue of Higher Degree

（待补）
- 高次剩余