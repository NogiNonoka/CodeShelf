---
title: "[String]Manacher"
tags: "Algorithm"
---

## 回文字符串 (Palindromic String)

### Manacher 算法

#### 算法知识

#### 算法模板

```C++
    const int maxn=1000010; 
    char str[maxn];//原字符串 
    char tmp[maxn<<1];//转换后的字符串 
    int Len[maxn<<1]; 
    //转换原始串 
    int Init(char *st) 
    { 
		int i,len=strlen(st); 
        tmp[0]='@';
		//字符串开头增加一个特殊字符，防止越界 
        for(i=1;i<=2*len;i+=2) 
        { 
            tmp[i]='#'; 
            tmp[i+1]=st[i/2]; 
        } 
        tmp[2*len+1]='#'; 
        tmp[2*len+2]='$';
        //字符串结尾加一个字符，防止越界 
        tmp[2*len+3]=0; 
        return 2*len+1;
        //返回转换字符串的长度 
    } 
    //Manacher算法计算过程 
    int Manacher(char *st,int len) 	
	{ 
        int mx=0,ans=0,po=0;
        //mx即为当前计算回文串最右边字符的最大值 
        for(int i=1;i<=len;i++) 
		{ 
            if(mx>i) 
            Len[i]=min(mx-i,Len[2*po-i]);
			//在Len[j]和mx-i中取个小 
            else 
            Len[i]=1;
			//如果i>=mx，要从头开始匹配 
            while(st[i-Len[i]]==st[i+Len[i]]) 
            Len[i]++; 
            if(Len[i]+i>mx)
            //若新计算的回文串右端点位置大于mx，要更新po和mx的值 
            { 
                mx=Len[i]+i; 
                po=i; 
            } 
            ans=max(ans,Len[i]); 
        } 
        return ans-1;
        //返回Len[i]中的最大值-1即为原串的最长回文子串额长度  
	}
```