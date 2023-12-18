// poj1860 Currency Exchange

// 大意:  有多种汇币，汇币之间可以交换，这需要手续费，当你用100A币交换B币时，A到B的汇率是29 .75，手续费是0.39，
// 那么你可以得到(100 - 0.39) * 29.75 = 2963.3975 B币。问s币的金额经过交换最终得到的s币金额数能否增加

// 货币的交换是可以重复多次的，所以我们需要找出是否存在正权回路，且最后得到的s金额是增加的

// 一种货币就是图上的一个点
// 一个“兑换点”就是图上两种货币之间的一个兑换环，相当于“兑换方式”M的个数，是双边
// 唯一值得注意的是权值，当拥有货币A的数量为V时，A到A的权值为K，即没有兑换
// 而A到B的权值为(V - Cab) * Rab
// 本题是“求最大路径”，之所以被归类为“求最小路径”是因为本题题恰恰与bellman- Ford算法的松弛条件相反，
// 求的是能无限松弛的最大正权路径，但是依然能够利用bellman - Ford的思想去解题。
// 因此初始化d(S) = V 而源点到其他店的距离（权值）初始化为无穷小（0），当s到其他某点的距离能不断变大时，说明存在最大路径

// 252K   16MS
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int n;    // 货币种数
int m;    // 兑换点数量
int s;    // 持有第s种货币
double v; // 持有的s货币的本金

int all;         // 边总数
double dis[101]; // s到各点的权值

class exchange_points
{
public:
    int a;    // 货币a
    int b;    // 货币b
    double r; // rate
    double c; // 手续费
} exc[202];

bool bellman(void)
{
    memset(dis, 0, sizeof(dis)); // 这里与bellman的目的刚好相反。初始化为源点到各点距离无穷小
    dis[s] = v;                  // 即bellman本用于找负环，求最小路径，本题是利用同样的思想找正环，求最大路径

    /*relax*/

    bool flag;
    for (int i = 1; i <= n - 1; i++)
    {
        flag = false;
        for (int j = 0; j < all; j++)
            if (dis[exc[j].b] < (dis[exc[j].a] - exc[j].c) * exc[j].r) // 寻找最长路径
            {
                // 进行比较的是"某点到自身的权值"和"某点到另一点的权值"
                dis[exc[j].b] = (dis[exc[j].a] - exc[j].c) * exc[j].r;
                flag = true;
            }
        if (!flag)
            break;
    }
    /*Search Positive Circle*/
    for (int k = 0; k < all; k++)
        if (dis[exc[k].b] < (dis[exc[k].a] - exc[k].c) * exc[k].r) // 正环能够无限松弛
            return true;

    return false;
}

int main(void)
{
    int a, b;
    double rab, cab, rba, cba; // 临时变量

    while (cin >> n >> m >> s >> v)
    {
        all = 0; // 注意初始化
        for (int i = 0; i < m; i++)
        {
            cin >> a >> b >> rab >> cab >> rba >> cba;
            exc[all].a = a;
            exc[all].b = b;
            exc[all].r = rab;
            exc[all++].c = cab;
            exc[all].a = b;
            exc[all].b = a;
            exc[all].r = rba;
            exc[all++].c = cba;
        }

        /*Bellman-form Algorithm*/

        if (bellman())
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}