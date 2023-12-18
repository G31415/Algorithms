// poj2228 Naptime

// 大意：一天分为N个时间片（可顺到下一天->环形），选择其中B个睡觉。
// 选择第i个时间片能获得u_i点值，但是选择的一个区间内的第一个时间片用来入睡（没睡着），无法获得u_i值。问最大能获得多少u_i值。

// dp[i][j][k]代表前i个时间片，睡了j个时间片得到的最大的utility，由于第i个时间片能否起作用取决于上一个时间片有没有选，因此开了第三维代表第i个时间片选了没。 （一开始是设的k代表前一个时间片选没，不易思考）

// 不选第i个时间片 :
// 前一个时间片没选：dp[i][j][0] = max(dp[i - 1][j][0] + 0, dp[i][j][0]);
// 前一个时间片选了：dp[i][j][0] = max(dp[i - 1][j][1] + 0, dp[i][j][0]);

// 选第i个时间片
// 前一个时间片没选：dp[i][j][1] = max(dp[i - 1][j - 1][0] + 0, dp[i][j][1]);
// 前一个时间片选了：dp[i][j][1] = max(dp[i - 1][j - 1][1] + util[i], dp[i][j][1]);

// 注意每次转移之前要判断状态合不合法，因为我们初始化不成立的状态为 -1，可能会不成立的状态+util[]导致错误的状态，如果初始化为     -INF，只要数据范围不超，应该就不会出现这种问题

// 316K	110MS
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 4e3;
const int INF = 0x3f3f3f3f;
int dp[2][N][2];
int n, b;
int u[N];
int ans = 0;

int main()
{
    cin >> n >> b;
    for (int i = 1; i <= n; ++i)
        cin >> u[i];
    memset(dp, -INF, sizeof(dp));
    dp[0][0][0] = dp[1][1][1] = dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i) // start from 2
    {
        int k = i & 1;
        for (int j = 1; j <= i; ++j)
        {
            dp[k][j][0] = max(dp[k ^ 1][j][0], dp[k ^ 1][j][1]);
            dp[k][j][1] = max(dp[k ^ 1][j - 1][0], dp[k ^ 1][j - 1][1] + u[i]);
        }
    }
    ans = max(dp[n & 1][b][0], dp[n & 1][b][1]);
    memset(dp, -INF, sizeof(dp));
    dp[1][1][1] = u[1];
    dp[0][0][0] = dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i)
    {
        int k = i & 1;
        for (int j = 1; j <= i; ++j) // here
        {
            dp[k][j][0] = max(dp[k ^ 1][j][0], dp[k ^ 1][j][1]);
            dp[k][j][1] = max(dp[k ^ 1][j - 1][0], dp[k ^ 1][j - 1][1] + u[i]);
        }
    }
    ans = max(ans, dp[n & 1][b][1]);
    cout << ans << endl;
    return 0;
}