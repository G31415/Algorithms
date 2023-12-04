// poj3269 Building A New Barn

// 求 | x-x1 | + | x-x2 | +…+ | x-xn | 的最小值,求 | y-y1 | + | y-y2 | +…+ | y-yn | 的最小值,直接求两者中位数即可

// (1)当n为奇数时,取(x[n / 2],y[n / 2] )
// 若该点为给出点,枚举它的上下左右四个方向上的点能求的最小的 d,然后统计当且仅当这4个点的方案数
// 若该点不为给出点,则直接记录最小距离,方案数为1。

// (2)当n为偶数时,取(x[n / 2 - 1],y[n / 2 - 1])和(x[n / 2 ],y[n / 2 ])
// 由曼哈顿距离的特性知：共有( x[n / 2]-x[n / 2 - 1] ) *(y[n / 2]-y[n / 2 - 1] )个点,
// 且它们到给定的n个点的曼哈顿距离和d相等。
// 因此枚举每个点是否为给定的点,求一次最小距离,再先让方案数为点的个数,每次更新减小方案数即可。

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <queue>
#include <set>
#include <vector>

using namespace std;

#define INF 0x3f3f3f3f
#define N 0x2710

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int x[N], y[N];

int Min, plan;

struct Node
{
    int x;
    int y;
} a[N];

int dis(int x, int y, int n)
{
    int dis = 0;
    for (int i = 0; i < n; i++) // 求最小的距离
        dis += abs(a[i].x - x) + abs(a[i].y - y);
    return dis;
}

int main()
{

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
        x[i] = a[i].x;
        y[i] = a[i].y;
    }
    sort(x, x + n); // 对x排序
    sort(y, y + n); // 对y排序
    if (n % 2)      // n为奇数时
    {
        int temp = (n / 2);
        for (int i = 0; i < n; i++) // 枚举所有点
        {
            if (a[i].x == x[temp] && a[i].y == y[temp]) // 若点为给出点
            {
                Min = INF;
                for (int l = 0; l < 4; l++) // 枚举四个方向
                {
                    int x0 = x[temp] + dx[l];
                    int y0 = y[temp] + dy[l];
                    int sum = dis(x0, y0, n);
                    if (sum < Min) // 遇到小的方案就变1
                    {
                        Min = sum;
                        plan = 1;
                    }
                    else if (sum == Min) // 相同则加1
                        plan++;
                }
                printf("%d %d\n", Min, plan);
                return 0;
            }
            else
            {
                Min += abs(a[i].x - x[temp]) + abs(a[i].y - y[temp]); // 记录最小距离
                plan = 1;                                             // 方案数为1
            }
        }
        printf("%d %d\n", Min, plan);
    }
    else // n为偶数时
    {
        int temp1 = n / 2 - 1, temp2 = n / 2;
        plan = (x[temp2] - x[temp1] + 1) * (y[temp2] - y[temp1] + 1); // 令方案数等于点的个数
        for (int i = 0; i < n; i++)
        {
            Min += abs(a[i].x - x[temp1]) + abs(a[i].y - y[temp1]);
            if (x[temp1] <= a[i].x && a[i].x <= x[temp2] && y[temp1] <= a[i].y && a[i].y <= y[temp2])
                // 更新方案数
                plan--;
        }
        printf("%d %d\n", Min, plan);
    }
    return 0;
}