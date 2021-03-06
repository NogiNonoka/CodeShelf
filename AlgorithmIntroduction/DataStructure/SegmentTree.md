## Segment Tree

### 线段树

#### 算法知识：

##### 定义：完全二叉树

##### 建树：

1.  节点下标
    -   父节点：i
    -   子节点：2i 2i+1

##### 复杂度：O(logn)

##### 解决问题：

1.  单点操作：
    -   单点查询
    -   单点修改
2.  区间操作：
    -   区间查询：最值 区间求和
    -   区间修改：**LazyTag**
3.  逆序对

#### 算法模板

```C++
// To be Continued
```

---

### 可持续化线段树（主席树）

#### 前置知识

##### 离散化

1.  保证离散化后的数据非负且尽可能的小。
2.  离散化后各数据项之间的大小关系不变，原本相等的也要保持相等。
3.  找出数据项在原序列中从小到大排第几。
4.  可以通过下面的方法以O(nlogn)的时间复杂度完成离散化，n为序列长度。
    -   对原序列进行排序，使其按升序排列。
    -   去掉序列中重复的元素。
    -   此时序列中各位置的值和位置的序号就是离散化的映射方式。
    -   STL函数：
        iterator unique(iterator it_1,iterator it_2,bool MyFunc); 
        - 删除的是相邻的重复元素，所以在使用unique函数之前，一般都会将目标序列进行排序。
        - 返回值是一个迭代器，它指向的是去重后容器中不重复序列的最后一个元素的下一个元素。
        - 删除过程实际上就是不停的把后面不重复的元素移到前面来，也可以说是用不重复的元素占领重复元素的位置。

###### 算法模板

```C++
int n, a[MAXN], t[MAXN];//这里以下标1为序列的起点，一般情况下从0开始也可以
for(int i = 1;i <= n;i++)
{
    scanf("%d", &a[i]);
    t[i] = a[i];
    //t是一个临时数组，用来得到离散化的映射关系
}
//下面使用了STL中的sort(排序)，unique(去重)，lower_bound(查找)函数
sort(t + 1, t + n + 1);
//排序
int m = unique(t + 1, t + 1 + n) - t - 1;
//去重，并获得去重后的长度m
for(int i = 1;i <= n;i++)
    a[i] = lower_bound(t + 1, t + 1 + m, a[i]) - t;//通过二分查找，快速地把元素和映射对应起来
```

##### 离线处理

1.  复杂度：O(1)查询
2.  对询问排序。

#### 算法知识

##### 基础：线段树

1.  支持询问历史版本、同时利用它们之间的共同数据来减少时间和空间消耗。
    -   每一次更新增加 log(n）个节点。
    -   非叶子节点会连向一个是其他版本的节点，一个是连向新节点。
    -   根节点很多，每一个根节点构成一个线段树。
    -   每一个节点都有可能有不只一个父亲（或母亲）节点。

2.  root数组：存储根节点位于结构体数组的下标。

##### 解决问题：

1.  区间第K大（小）。
    -   洛谷P3834
    -   POJ 2104 / HDU 2665
2.  动态区间第K大（小）

#### 算法模板

1.  静态区间第K小

```C++
struct PersistentSegementTree
{
    int val[MAXN << 5];
    int left[MAXN << 5], right[MAXN << 5];
    int nodecnt = 0;
    int root[MAXN];

    int rootclone(int pos)
    {
        ++nodecnt;
        val[nodecnt] = val[pos] + 1;
        left[nodecnt] = left[pos];
        right[nodecnt] = right[pos];
        return nodecnt;
    }

    int buildtree(int pos, int l, int r)
    {
        pos = ++nodecnt;
        if(l == r)
        {
            val[pos] = 0;
            left[pos] = l;
            right[pos] = r;
            return pos;
        }
        int mid = l + (r - l) / 2;
        val[pos] = 0;
        left[pos] = buildtree(left[pos], l, mid);
        right[pos] = buildtree(right[pos], mid + 1, r);
        return pos;
    }

    int nodechange(int pos, int l, int r, int aim)
    {
        pos = rootclone(pos);
        if(l == aim && r == aim)
        {
            return pos;
        }
        else
        {
            int mid = l + (r - l) / 2;
            if(aim <= mid)
                left[pos] = nodechange(left[pos], l, mid, aim);
            else
                right[pos] = nodechange(right[pos], mid + 1, r, aim);
        }
        return pos;
    }

    int nodequery(int pos, int l, int r, int aim)
    {
        if(l == aim && r == aim)
        {
            return val[pos];
        }
        else
        {
            int mid = l + (r - l) / 2;
            if(aim <= mid)
                return nodequery(left[pos], l, mid, aim);
            else 
                return nodequery(right[pos], mid + 1, r, aim);
        }
    }

    int kthquery(int fr, int to, int l, int r, int k)
    {
        int mid = l + (r - l) / 2;
        int sum = val[left[to]] - val[left[fr]];
        if(l == r)
            return l;
        if(sum >= k)
            return kthquery(left[fr], left[to], l, mid, k);
        else
            return kthquery(right[fr], right[to], mid + 1, r, k - sum);
    }
}pst;
```

* * *
