// poj2586 Y2K Accounting Bug

// 大意：某公司每个月要么盈利s元，要么亏损d元，一年之中任意连续的五个月的利润和是亏损的，最后问一年的总收入是多少，如果盈利即输出数额，如果亏损，则输出Deficit。直接去枚举所有的情况分析也是可以的，因为出现的情况并不复杂也不多。

// 本题纯用贪心思想编写算法即可。也就是说先假设所有的月均为盈利，判断第一个连续五月是亏损，如果不亏损，将最后一个月设为亏损，再次判断如果仍亏损的话让倒数第二个月设为亏损。。直到满足情况为止。依次判断8个连续的五月，最后检查总情况。

// 156K	0MS
#include <stdio.h>
#include <stdlib.h>

int month[12];
int add(int m[], int n)
{
    int i = 0, result = 0;
    for (i = n; i < n + 5; i++)
        result = result + m[i];
    return result;
}
int main()
{
    int d, s;
    while (scanf("%d", &s) == 1 && s > 0 && scanf("%d", &d) == 1 && d > 0)
    {
        d = -d;
        int i = 0;
        for (i = 0; i < 12; i++)
            month[i] = s;

        int j;
        for (i = 0; i < 8; i++)
        {
            for (j = 1; j <= 5; j++)
            {
                int flag = add(month, i);
                if (flag >= 0)
                    month[i + 5 - j] = d;
                else
                    break;
            }
        }
        int all = 0;
        for (i = 0; i < 12; i++)
            all += month[i];
        if (all > 0)
            printf("%d\n", all);
        else
            printf("Deficit\n");
    }
    return 0;
}
