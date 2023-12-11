// poj3040 Allowance

#include <iostream>
#include <cstdio>
#include <string>
#include <limits.h>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <set>
#include <vector>
#include <queue>

using namespace std;

struct Coin
{
    int value;
    int num;
    Coin() {}
    Coin(int x, int y) : value(x), num(y) {}
    bool operator<(const Coin &other) const//小于运算符重载，用于排序
    {
        return value < other.value;
    }
} coin[20];

int used[20];
int n;
int c;

int main()
{
    while (scanf("%d%d", &n, &c) != EOF)
    {
        for (int i = 0; i < n; i++)
            scanf("%d%d", &coin[i].value, &coin[i].num);

        int res = 0;
        sort(coin, coin + n);
        
        for (int i = n - 1; i >= 0; i++)//从大到小进行选择
        {
            if (coin[i].value >= c)
            {
                res += coin[i].num;
                coin[i].num = 0;
            }
            else
                break;//小于则跳出循环
        }
        while (true)
        {
            memset(used, 0, sizeof(used));
            int cou = c;

            // 从大到小 先挑面值大的，总值不能超过c
            for (int i = n - 1; i >= 0; i--)
            {
                if (coin[i].num != 0)
                {
                    int temp = cou / coin[i].value;
                    temp = min(temp, coin[i].num);
                    used[i] = temp;
                    cou -= temp * coin[i].value;
                    if (cou == 0)
                        break;
                }
            }

            // 从小到大 补足剩余的钱 总值可以超过c
            if (cou > 0)
            {
                for (int i = 0; i < n; i++)
                {
                    if (coin[i].num > 0)
                    {
                        while (used[i] < coin[i].num)
                        {
                            cou -= coin[i].value;
                            used[i]++;
                            if (cou <= 0)
                                break;
                        }
                        if (cou <= 0)
                            break;
                    }
                }
            }

            if (cou > 0)
                break;

            int temp = INT_MAX;
            for (int i = 0; i < n; i++)
            {
                if (used[i] != 0)
                {
                    temp = min(temp, coin[i].num / used[i]);
                }
            }

            res += temp;
            for (int i = 0; i < n; i++)
            {
                if (used[i] != 0)
                    coin[i].num -= used[i] * temp;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
