## Suffix Array

### Introduction

- $sa_i$：排名为 $i$ 的后缀
- $rk_i$：后缀 $i$ 的排名
- $ht_i$：$lcp(sa_i, sa_{i - 1})$

### Algorithm

#### 基于倍增思想的实现
- 时间复杂度：$O(n\log^2(n))$
- 已知 $rk_{i}[i,i + len - 1]$ 求 $sa_{i}[i, i + 2 * len - 1]$，只需双关键字排序即可；
- 根据 $sa$ 对 $rk$ 更新并去重，基于 $sa$ 的含义 $rk[sa[i]] = i$，更新 $rk[i]$ 时只需要比较当前串 $i$ 和 前一串 $i - 1$ 是否相同，相同的条件即合并为 $i$ 的 $i_1$ 与 $i_2$ 的两串与合并为 $(i - 1)$ $(i - 1)_1$ 与 $(i - 1)_2$ 的 $rk_{pre}$ 值相同。

##### Template

```C++
string s;
int sa[MAXN << 1], rk[MAXN << 1], tmp[MAXN << 1];

void build(int n) {
    // Time Complexity: O(Nlog^2(N))
    for (int i = 0; i < n; ++i) {
        sa[i + 1] = i + 1;
        rk[i + 1] = s[i];
    }
    for (int i = 1; i < n; i <<= 1) { 
        sort(sa + 1, sa + n + 1, [&](int x, int y) { return rk[x] == rk[y] ? rk[x + i] < rk[y + i] : rk[x] < rk[y]; });
        memcpy(tmprk, rk, n * sizeof(int));
        for (int j = 1, cnt = 0; j <= n; ++j) {
            if (tmprk[sa[j]] == tmprk[sa[j - 1]] && tmprk[sa[j] + i] == tmprk[sa[j - 1] + i]) {
                rk[sa[j]] = cnt;
            } else {
                rk[sa[j]] = ++cnt;
            }
        }
    }
}
```

#### 基于计数排序的优化

- 时间复杂度：$O(NlogN)$
- 使用计数排序代替快速排序；
- 维护 $id$ 对第二关键字排序；

##### Template

```C++
string s;
int sa[MAXN << 1], rk[MAXN << 1], tmprk[MAXN << 1];
int cnt[MAXN], id[MAXN];

void getSA(int n) {
    // Time Complexity: O(Nlog(N))
    memset(cnt, 0, sizeof(cnt));
    int ma = 0, cur = 0;
    for (int i = 1; i <= n; ++i) {
        rk[i] = s[i - 1];
        cnt[rk[i]] += 1;
        ma = max(ma, rk[i]);
    }
    for (int i = 1; i <= ma; ++i) { cnt[i] += cnt[i - 1]; }
    for (int i = n; i >= 1; --i) { sa[cnt[rk[i]]--] = i; }
    for (int len = 1; len < n; len <<= 1, ma = cur) {
        // sort with rk[i + len]
        cur = 0;
        for (int i = n - len + 1; i <= n; ++i) { id[++cur] = i; }
        for (int i = 1; i <= n; ++i) {
            if (sa[i] > len) {
                id[++cur] = sa[i] - len;
            }
        }
        // sort with rk[i]
        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; ++i) { cnt[rk[id[i]]] += 1; }
        for (int i = 1; i <= ma; ++i) { cnt[i] += cnt[i - 1]; }
        for (int i = n; i >= 1; --i) { sa[cnt[rk[id[i]]]--] = id[i]; }
        // unique
        cur = 0;
        memcpy(tmprk, rk, sizeof(rk));
        for (int i = 1; i <= n; ++i) {
            if (tmprk[sa[i]] == tmprk[sa[i - 1]] && tmprk[sa[i] + len] == tmprk[sa[i - 1] + len]) {
                rk[sa[i]] = cur;
            } else {
                rk[sa[i]] = ++cur;
            }
        }
        if (cur == n) {
            for (int i = 1; i <= n; ++i) { sa[rk[i]] = i; }
            break;
        }
    }
}
```

#### Longest Common Prefix 最长公共前缀

- 引理：$ht_{rk[i]} \ge ht_{rk[i - 1]} - 1$
  - 证明：$i$ 表示后缀字符串，$[a-z]$ 表示单个字符，$[A-Z]$ 表示字符串；
    - $i - 1 = aAD,\ ht_{rk[i - 1]} = lcp(sa[rk[i - 1]], sa[rk[i - 1] - 1]) = len(aA)$
    - $B < D,\ sa[rk[i - 1] - 1] = aAB,\ sa[rk[i - 1] - 1] + 1 = AB$
    - $i = AD,\ ht_{rk[i]} = lcp(sa[rk[i]], sa[rk[i] - 1])$
    - $AB < AD,\ AB \le sa[rk[i] - 1] \le AC \le AD,\ ht_{rk[i]} \ge len(A) = ht_{rk[i - 1]} - 1$

##### Template

```C++
int ht[MAXN];

void getHeight(int n) {
    for (int i = 1, cur = 0; i <= n; ++i) {
        if (cur) cur -= 1;
        while (s[i - 1 + cur] == s[sa[rk[i] - 1] - 1 + cur]) {
            cur += 1;
        }
        ht[rk[i]] = cur;
    }
}
```

### Solution 

- 寻找最小的循环移动位置
- 在字符串中找子串
- 从字符串首尾取字符最小化字典序
- 两子串最长公共前缀
  $lcp(sa_i, sa_j) = \min (ht_{i+1} \dots ht_j)$
- 比较一个字符串的两个子串的大小关系
  - 记 $A = s[a \dots c],\ B = s[b \dots d]$
  - 若 $lcp(a, b) > \min(|A|, |B|) ,\ A < B \Leftrightarrow |A| < |B|$
  - 则 $A < B \Leftrightarrow rk[a] < rk[b]$
