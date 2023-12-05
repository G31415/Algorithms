// poj1185 炮兵阵地

// 1756K 266MS
// 首先，一个炮的攻击范围有两格，所以对于第i行来讲，i - 1行和i - 2行对它有影响，i - 3行及以上的都没有影响了；
// 所以我们要去求得到关于第i行的一些信息，只需要知道i -1和i - 2的信息即可；

// 然后考虑表示地图：山用1表示，空地用0表示；那么对于一行，就是一个0 or 1的串，这是个二进制数，可以状压成一个十进制数；
// 满足(i & (i << 1)) == 0 && (i & (i << 2)) == 0 的话，它才是一个符合炮与炮之间相互不能攻击的状态；
// 由此，我们通过枚举计算一下有60个状态：由此使用一个state[] 数组保存状态，把每次枚举出来可行的状态保存进去；

//  判断炮兵部队不在山上：只要state[i] & mp[r] == 0,就表示state[i] 可以放在r这行上，而且炮不会在山上，炮之间也不会攻击；

//  判断 i行，i -1行，i - 2行的炮没有冲突：假设现在i行，i - 1行，i - 2行的炮的摆放情况分别是state [i],state[j], state[k]；
// 当满足 state[i] & state[j] == 0 state[i] & state[k] == 0 state[j] & state[k] == 0 条件时，
// 三行的部署情况没有冲突；

//  最后进行状态转移方程。

#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 103
#define MAXM 11

using namespace std;

int n, m;
int mp[MAXN]; // 记录地形

struct State // 记录状态
{
    int sta; // 表示第i个状态是怎么样的
    int cnt; // 记录这个状态下，部署了多少炮兵部队
} state[63];

int dp[MAXN][63][63];

int main()
{
    scanf("%d%d", &n, &m);

    // 二进制记录地图
    for (int i = 1; i <= n; i++) // 将每一行转化为一串二进制
    {
        mp[i] = 0;
        char input[12];
        scanf("%s", input + 1);
        for (int j = 1; j <= m; j++)
        {
            int temp = ((input[j] == 'H') ? 1 : 0);
            mp[i] |= temp; // 或运算转化最后一位
            if (j != m)
                mp[i] = mp[i] << 1;
        }
    }

    // 单纯在炮与炮之间不能互相攻击的限制下，得到每行的所有状态
    int state_num = 0;
    for (int i = 0; i <= (1 << m) - 1; i++)
    {
        if ((i & (i << 1)) == 0 && (i & (i << 2)) == 0) // 不能再两次移动中有1相遇
        {
            state_num++;
            state[state_num].sta = i;
            // 计算有几个炮台
            state[state_num].cnt = 0;
            for (int tmp = i; tmp; tmp = (tmp >> 1))
                if (tmp & 1)
                    state[state_num].cnt++;
        }
    }

    // 状态转移过程 - start
    memset(dp, 0, sizeof(dp));

    // 初始化dp[1][ state of row1 ][ no state ]
    for (int i = 1; i <= state_num; i++)
    {
        if (state[i].sta & mp[1])
            continue; // 冲突则跳过
        dp[1][i][1] = state[i].cnt;
    }

    // 初始化dp[2][ state of row2 ][ state of row1 ]
    for (int i = 1; i <= state_num; i++) // 枚举第2行状态
    {
        if (state[i].sta & mp[2])
            continue;
        for (int j = 1; j <= state_num; j++) // 枚举第1行状态
        {
            if ((state[j].sta & mp[1]) || (state[i].sta & state[j].sta))
                continue;
            dp[2][i][j] = max(dp[2][i][j], dp[1][j][1] + state[i].cnt);
        }
    }

    // 对剩余的进行状态枚举(一行一行枚举，类似动态规划，r行的状态不能与r-1和r-2行冲突)
    for (int r = 3; r <= n; r++)
    {
        for (int i = 1; i <= state_num; i++) // 枚举第r行状态
        {

            if (state[i].sta & mp[r])
                continue;
            for (int j = 1; j <= state_num; j++) // 枚举第r-1行状态
            {
                if ((state[j].sta & mp[r - 1]) || (state[i].sta & state[j].sta))
                    continue;
                for (int k = 1; k <= state_num; k++) // 枚举第r-2行状态
                {
                    if (state[k].sta & mp[r - 2])
                        continue;
                    if ((state[i].sta & state[k].sta) || (state[j].sta & state[k].sta))
                        continue;
                    dp[r][i][j] = max(dp[r][i][j], dp[r - 1][j][k] + state[i].cnt);
                }
            }
        }
    }
    // 状态转移过程 - end

    int ans = 0;
    for (int i = 1; i <= state_num; i++)
    {
        for (int j = 1; j <= state_num; j++)
        {
            ans = max(ans, dp[n][i][j]);
            // n行后的所有情况中的最大值
        }
    }
    printf("%d\n", ans);
}