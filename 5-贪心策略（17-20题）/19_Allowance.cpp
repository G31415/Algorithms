// poj3040 Allowance

// 大意：
// 约翰要给他的牛贝西发工资，每天不得低于C元，约翰有n种面值的钱币，第i种的面值为v_i，数量有b_i。问这些钱最多给贝西发多少天的工资。
// 注意，每种面值的金钱都是下一种的面值的倍数。

// 典型的贪心算法，每一次发工资，都要考虑当前所能实现的最优策略。
// 对coin数组按照面值大小从小到大排序，然后将数值大于等于C的先提前计算。

// 为了能最大程度实现每次发的工资都尽可能贴近C，我们需要先从大到小进行分配，分配过程中，费用不能超过C；
// 然后，如果费用不等于C，也就是仍然需要面值小的进行补偿，就需要从小到大进行分析，这时的费用可以超过C，
// 因为是从小到大，我们可以将小面值用到极致，也就是能用的都用了。

// 贪心过程需要used数组记录每一个面值所使用的数目，这样就可以找到最优组合可以实现多少次，也就是coin[i].num /used[i] 中的最小值。
// 当搭配完毕后，若出现费用仍然大于零的情况，就说明当前的钱不够分工资了，退出循环。

// 156K	32MS
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
    bool operator<(const Coin &other) const // 小于运算符重载，用于排序
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

        for (int i = n - 1; i >= 0; i++) // 从大到小进行选择
        {
            if (coin[i].value >= c)
            {
                res += coin[i].num;
                coin[i].num = 0;
            }
            else
                break; // 小于则跳出循环
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
