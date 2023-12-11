// poj2228 Naptime
// 这是环形dp的一种，策略是执行两次dp，第一次在任意位置断链成环，按照线性dp求解，第二次则通过赋值和限制条件，算出把断开的位置连上的状态的解，然后比较两次dp的结果
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int f1[4000][2], f2[4000][2]; // 每一个状态其实只跟上一个状态有关,所以第一维i =2~n是可以省略的,否则会mle
int main()
{
    int n, b, i, j, k, u[4000];
    cin >> n >> b;
    for (i = 1; i <= n; i++)
        cin >> u[i];
    for (j = 0; j <= b; j++)
        f1[j][0] = f1[j][1] = f2[j][0] = f2[j][1] = 1 << 31; // 全部初始化为负无穷
    f1[0][0] = 0, f1[1][1] = 0;
    f2[1][1] = u[1]; // f2[0][0]=0;这个加不加对结果没影响,我的理解是这个状态在f1里面已经算过了,所以f2没必要去考虑
    for (i = 2; i <= n; i++)
        for (j = b; j >= 0; j--)
        { // 倒序
            f1[j][0] = max(f1[j][0], f1[j][1]);
            f2[j][0] = max(f2[j][0], f2[j][1]);
            if (j)
            {
                f1[j][1] = max(f1[j - 1][0], f1[j - 1][1] + u[i]);
                f2[j][1] = max(f2[j - 1][0], f2[j - 1][1] + u[i]);
            }
        }
    int ans = 0;
    ans = max(max(f1[b][0], f1[b][1]), f2[b][1]);
    cout << ans << endl;

    return 0;
}