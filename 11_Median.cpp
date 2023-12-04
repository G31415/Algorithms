// poj3579 Median

// 416K	407MS
// 给出N个数，对于存有每两个数的差值的序列求中位数，如果这个序列有偶数个元素，就取中间偏小的作为中位数。

// 因为N<=100000,所以想要求出每一个差值是不可行的，我们很容易想到二分答案。 在二分答案时我们会进行判定，求出小于等于枚举值的个数，我看其他人的判定似乎都是O(NlogN) 的，我在这里就给出一个O(N)的判定方法。

// 首先同样将数组排序(我们命名为a数组好了)
// 我们枚举一个区间[l,r),因为当r增加的时候，要使[l,r)中的数都大于于等于a[r]−枚举值，l必定不会增加，然后r单调递增，l单调不递减,则时间复杂度为O(n)。
#include <cstdio>
#include <algorithm>
long long n, a[100005];
int main()
{
    long long i, j;
    while (~scanf("%I64d", &n))
    {
        for (i = 1; i <= n; i++)
            scanf("%I64d", a + i);
        std::sort(a + 1, a + n + 1);
        long long l = 0, r = a[n], mid, m = (n - 1) * n / 4, num;
        if ((n * (n - 1) / 2) & 1)
            m++;
        if (n == 1)
        {
            printf("0\n");
            continue;
        }
        while (l < r)
        {
            mid = (l + r) >> 1;
            j = 1;
            num = 0;
            for (i = 2; i <= n; i++)
            {
                while (a[i] - a[j] > mid)
                    j++;
                num += (i - j);
            }
            if (num >= m)
                r = mid;
            else
                l = mid + 1;
        }
        printf("%I64d\n", l);
    }
    return 0;
}

// 288K	704MS
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int arr[100007], inf = 0x3f3f3f3f, n, k;
void input()
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int count = n * (n - 1) / 2;
    k = count / 2;
    if (count % 2 != 0)
    {
        k++;
    }
    sort(arr, arr + n);
    arr[n] = inf;
}
bool judge(int mid)
{
    ll countLt = 0, countEq = 0;
    for (int i = 0; i < n; i++)
    {
        ll val = arr[i];
        val += mid;
        int rangeLt;
        if (val < inf)
        {
            rangeLt = lower_bound(arr, arr + n + 1, arr[i] + mid) - arr - i - 1;
        }
        else
        {
            rangeLt = n - i - 1;
        }
        countLt = countLt + rangeLt;
    }
    return countLt < k;
}
void binarySearch()
{
    int left = -1, right = arr[n - 1] - arr[0] + 1;
    while (left + 1 < right)
    {
        ll mid = left;
        mid += right;
        mid = mid >> 1;
        if (judge((int)mid))
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    printf("%d\n", left);
}
int main()
{
    while (~scanf("%d", &n))
    {
        input();
        binarySearch();
    }
    return 0;
}