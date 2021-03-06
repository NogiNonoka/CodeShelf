## 回文字符串 (Palindromic String)

### Manacher 算法

#### 算法知识

- 求解最长回文子串算法 Manacher；
- 时间复杂度：$O(N)$

#### 算法模板

```C++
struct Manacher
{
    // Manacher Algorithm (Longest Palindromic Substring)
    // Time Complexity: O(N)
    string text;
    int cnt[MAXN];
    
    void pre(string &s)
    {
        text = "*#";
        for (auto ch : s)
        {
            text += ch;
            text += '#';
        }
    }

    int manacher()
    {
        int ans = 0;
        int mid = 0, maxr = 0;
        for (int i = 0; i < text.size(); ++i)
        {
            if (i < maxr)
                cnt[i] = min(cnt[mid * 2 - i], maxr - i);
            else 
                cnt[i] = 1;
            while (text[i + cnt[i]] == text[i - cnt[i]])
                ++cnt[i];
            if (i + cnt[i] > maxr)
            {
                maxr = i + cnt[i];
                mid = i;
            }
            ans = max(ans, cnt[i]);
        }
        return ans;
    }
}ps;
```
