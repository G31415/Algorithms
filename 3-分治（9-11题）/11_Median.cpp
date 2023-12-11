// poj3579 Median

// 大意: 给出N个数，对于存有每两个数的差值的序列求中位数，如果这个序列有偶数个元素，就取中间偏小的作为中位数。

// 因为N<=100000,所以想要求出每一个差值是不可行的，可以用二分答案来不断接近中位数值。
// 首先同样将数组排序(我们命名为a数组好了)
// 中位数数列最小是l=0，最大是r=a[n]-a[0]
// 对中位数数列不断二分，将mid=(l+r)>>1与枚举a[j]-a[i]<=mid的总数作为二分依据
// 不断接近中位数的值

// 288K	329MS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f
#define Max 0x186a0

using namespace std;

int n, a[Max];

// 检验小于x的数是不是比(n * (n - 1)) >> 2小
bool check(int x)
{
    int cnt = 0;
    //[i,j]之间的数是满足 a[j] - a[i]<= x, 则有j - i个
    for (int i = 1, j = 1; i <= n; ++i)
    {
        while (a[j] <= a[i] + x && j <= n)
            ++j;
        --j;
        cnt += j - i;
    }
    if (!(((n * (n - 1)) >> 1) & 1))//判断奇偶
        return cnt < (n * (n - 1)) >> 2;
    else
        return cnt <= (n * (n - 1)) >> 2;
}
int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        sort(a + 1, a + 1 + n);
        int l = 0, r = a[n];
        while (l < r)
        {
            int mid = (l + r )>> 1;
            if (check(mid))//二分中间值数列
                l = mid + 1;
            else
                r = mid;
        }
        printf("%d\n", l);
    }
    return 0;
}

