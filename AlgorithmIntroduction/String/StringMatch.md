## String Match

### KMP Algorithm

#### Introduction

- 字符串匹配算法
- 时间复杂度：O(N + M)
- 对于给定的模式串 $t$，在文本串 $s$ 中求解出现位置、出现次数等信息。

#### Algorithm

- 定义 $next$ 数组，记录 $t$ 中 $i$ 位置的子串 $t[0 \dots i]$ 中前缀与后缀的最长公共子串 $LCS$；
- $O(M)$ 求得 $Next$ 数组后，在字符串失配位置优化模式串移动距离，实现 $O(N)$ 字符串匹配。

##### Match

字符串下标从 **0** 开始。

将 $Next$ 数组全部向后移动一位，令 $nxt[0] = -1$，此时 $nxt[j]$ 表示子串 $t[0 \dots j - 1]$ 前缀与后缀的 $LCP$，即 $t[0 \dots nxt[j] - 1]$ 与 $t[j - 1 - nxt[j] \dots j - 1]$ 相等，则下一步模式串 $s[i]$ 与 $s[nxt[j]]$ 比较

##### Calculate Next

字符串下标从 **0** 开始。

- 计算 $Next$ 数组采用一种近似线性动态规划的方法；
- 对于 $nxt[j + 1]$，我们已知 $nxt[0 \dots j]$ 的值，$t[0 \dots nxt[j] - 1] = t[j - 1 - nxt[j] \dots j - 1] $ 此时 $j$ 位置有两种情况
  - $t[j] = t[nxt[j] + 1]$，可见 $nxt[j + 1] = nxt[j] + 1$；
  - $t[j] \neq t[nxt[j] + 1]$，字符串在此处失配，递归的寻找 $nxt[nxt[j]]$。

> 以样例 $t = abaaaba$ 为例，$nxt[] = [0,0,1,1,1,2,3]$：
> - $j = 2$，判断 $t[2] = t[nxt[1]]$，$nxt[2] = nxt[1] + 1$；
> - $j = 3$，判断 $t[3] \ne (t[nxt[2] + 1] = t[1])$ 在此处失配，递归判断 $t[3] = t[nxt[1] - 1] = t[0]$；
> - $j= 5$，判断 $t[5] = t[nxt[4] + 1] = t[2]$。

#### Template

```C++
struct KMP
{
    // Serach t in s and return pos
    // Time Complexity: O(N+M)
    string s;
    string t;

    int nxt[MAXN];

    void getNext()
    {
        int j = 0, k = -1;
        nxt[0] = -1;
        while (j < (int)t.length())
        {
            if (k == -1 || t[j] == t[k])
                nxt[++j] = ++k;
            else 
                k = nxt[k];
        }
    }

    void kmpAllIndex()
    {
        /**
         * @description: print all first index found in s
         * @param {void}
         * @return {void}
         */        
        getNext();
        int i = 0, j = 0;
        while (i < (int)s.length())
        {
            if (j == -1 || s[i] == t[j])
                ++i, ++j;
            else 
                j = nxt[j];
            if (j == t.length())
            {
                cout << i - j + 1 << endl;
                j = nxt[j];
            }
        }
    }
}kmp;
```

### AC Automate

## Prefix - Suffix Compare

### Extend KMP (Z Algorithm)