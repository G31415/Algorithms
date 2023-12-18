// poj1042 钓鱼

// 大意：
// 现有h个小时,共有n个湖,所有的湖沿着一条单向路顺序排列（每在一个湖钓完鱼后,他只能走到下一个湖继续钓）
// 必须从1号湖开始钓起,但是可以在任何一个湖结束。
// 以5分钟作为单位时间,在每个湖中每5分钟钓的鱼数随时间的增长而线性递减。
// 每个湖中头5分钟可以钓到的鱼数用fi表示,每个湖中相邻5分钟钓鱼数的减少量用di表示,从任意一个湖走到它下一个湖的时间用ti表示。
// 求一种方案,使得John在有限的h小时中可以钓到尽可能多的鱼。
// 经典的贪心例题,采用枚举 + 贪心的解题思路

// 把总时间分为两个部分：在路上的时间和在钓鱼的时间。
// 由于路是单行的,所以在路上的时间取决于走的最远距离,即到达的池塘的最大编号。 剩余的时间用于钓鱼。
// 指定一个池塘为终点,移动过程即从起点到终点的过程,钓鱼的过程就是从起点到终点的各个池塘中选择池塘钓鱼
// 然后,选择到哪些池塘钓鱼的策略采用贪心的方法,每个钓鱼的5分钟都选择期望最大的那一个池塘
// 每在选择一个池塘钓鱼5分钟,减少相应池塘的期望,增加计划中在该池塘钓鱼的时间,然后继续选择期望最大的池塘
// 直到钓鱼的时间不够,或者池塘里没有鱼了。如果池塘没有鱼了,还有时间的话,把多余的时间分配给第一个池塘

// 156K	79MS
#include <iostream>
#include <cstring>
#include <climits>
#define Max 0x19

using namespace std;

int n;
int h;
int fi[Max];     // fi[]期望钓鱼数
int di[Max];     // di[]每五分钟减少鱼数
int ti[Max];     // ti[]位移时间
int time[Max];   // 在当前湖停下来时在每个湖停留的时间
int best[Max];   // 最优解对应的在每个湖停留的时间
int bestFishNum; // 最优解钓鱼总数
int fishNum;     // 当前钓鱼总数

int main()
{
    while (scanf("%d", &n) != EOF && n)
    {
        scanf("%d", &h);
        h *= 12; // 共有h个5分钟
        for (int i = 0; i < n; i++)
            scanf("%d", &fi[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &di[i]);
        for (int i = 0; i < n - 1; i++)
            scanf("%d", &ti[i]);

        bestFishNum = INT_MIN;
        memset(best, 0, sizeof best); // 将best数组的值全部设为0

        for (int p = 0; p < n; p++) // 穷举最终停下的湖的位置
        {
            memset(time, 0, sizeof(time));
            fishNum = 0;
            int remainingTime = h;  // 当前剩余时间
            int remainingFish[Max]; // 当前在每个湖剩余能钓的鱼的数目

            for (int i = 0; i < n; i++)
                remainingFish[i] = fi[i]; // 初始化

            for (int j = 0; j < p; j++)
                remainingTime -= ti[j]; // 先减去路程,之后假设John可以在lake 0到lake i之间随意位移

            while (remainingTime > 0) // 直到时间用尽
            {
                int max = INT_MIN;           // 五分钟钓的最多鱼数
                int pos = 0;                 // 当前能钓鱼最多的位置
                for (int j = 0; j <= p; j++) // 每次选出能钓鱼最多的位置
                    if (remainingFish[j] > max)
                    {
                        max = remainingFish[j];
                        pos = j; // 找到位置
                    }
                time[pos]++;                   // 对应时间++
                fishNum += remainingFish[pos]; // 累加钓鱼数
                remainingFish[pos] = remainingFish[pos] - di[pos] > 0 ? remainingFish[pos] - di[pos] : 0;
                // 更新下一个五分钟的钓鱼数
                remainingTime--; // 减少剩余时间
            }
            if (fishNum > bestFishNum) // 更新最大钓鱼数
            {
                bestFishNum = fishNum;
                for (int i = 0; i < n; i++)
                {
                    best[i] = time[i]; // 更新每个湖的时间
                }
            }
        }
        for (int i = 0; i < n - 1; i++)
            printf("%d, ", best[i] * 5);
        printf("%d\n", best[n - 1] * 5);
        printf("Number of fish expected: %d\n\n", bestFishNum);
    }
    return 0;
}
