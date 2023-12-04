// poj1050 To the Max

// 依据数组的最大子数组问题，将矩阵第i到j行相加，然后求此数组的最大子数组(动态规划问题)
// sum[i+1] = max(sum[i]+a[i+1], a[i+1])  其中sum[i]为以a[i]为尾元素的最大子数列

// 236K 16MS
#include <iostream>
#include <cstring>
#define Max 0x65

using namespace std;

int a[Max][Max];
int b[Max][Max]; // b[j][k]表示从i行加到j行 第k列值的大小，将二维转为一维
int dp[Max]; //存储每一个数组的最大子数列
int ans, n;

void solve(int j)
{
    memset(dp, 0, sizeof(dp));//重置dp数组
    for (int i = 1; i <= n; i++)//从i开始，动态规划
    {
        dp[i] = max(b[j][i], b[j][i] + dp[i - 1]);
        ans = max(ans, dp[i]);
    }
}

int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) // 从第i行开始加
    {
        memset(b, 0, sizeof(b));
        for (int j = i; j <= n; j++) // 加到第j行
        {
            for (int k = 1; k <= n; k++) // 第k列
            {
                b[j][k] = a[j][k] + b[j - 1][k];
            }
            solve(j);
        }
    }
    printf("%d",ans);

    return 0;
}
