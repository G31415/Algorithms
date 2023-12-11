// poj1088 滑雪

// 大意: 输入一个代表高度的矩阵, 可以由高点通过上下左右到达低点, 求最长距离

// 记忆化搜索
// 类似从上到下同时记录的动态规划
// 运用dfs深度搜索，在运行过程中将搜索过的点的索引值记录下来

// 244K 16MS
#include <iostream>
#define Max 0x69
using namespace std;

int n, m;
int high[Max][Max];
int maxLen[Max][Max];
int to[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}}; // 上下左右

bool check(int x, int y)
{
    if (x >= 1 && y >= 1 && x <= n && y <= m)
        return 1;
    else
        return 0;
}

int dfs(int x, int y)
{
    if (maxLen[x][y] != 0) // 退出边界 ，这个点已经搜索过，或者这个点是边界
        return maxLen[x][y];

    maxLen[x][y] = 1; // 最低的点就是1;
    for (int i = 0; i < 4; i++)
    { // 搜索上下左右
        int x1 = x + to[i][0];
        int y1 = y + to[i][1];
        if (check(x1, y1) && high[x1][y1] < high[x][y])
        { // 判断能否向下滑
            maxLen[x][y] = max(dfs(x1, y1) + 1, maxLen[x][y]);//递归搜索
        }
    }
    return maxLen[x][y]; // 返回搜索过的点，并保存在数组中
}
int main()
{
    int ans = 1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &high[i][j]);
            maxLen[i][j] = 0;//初始化
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ans = max(ans, dfs(i, j)); // 搜索每一个点，并且找出最大值
        }
    }
    printf("%d",ans);
    return 0;
}

// 动态规划的状态方程:我们如果从下往上推，找到最小的点，
// 然后可以用这个点更新上下左右的点，如果从这个点到上下
// 左右4个点的上升序列比 这4个点本身的上升序列 变长了就
// 更新并记录。直到找到最大值。
// 每用一个点，这个点的作用是更新其他4个点的最大上升序列值。

// 364K	32MS

// #include <iostream>
// #include <stdio.h>
// #include <algorithm>
// #define Max 0x69

// using namespace std;

// int n, m;
// int high[Max][Max];
// int maxLen[Max][Max];
// int to[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}}; // 上下左右
// struct node
// {
//     int x;
//     int y;
//     int data;
// };

// bool cmp(node a, node b)
// {
//     return a.data < b.data;
// }

// bool check(int x, int y)
// {
//     if (x >= 1 && y >= 1 && x <= n && y <= m)
//         return 1;
//     else
//         return 0;
// }

// int main()
// {
//     int ans = 1;
//     scanf("%d%d", &n, &m);
//     int k = 0;
//     node s[0x2716];
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= m; j++)
//         {
//             scanf("%d", &high[i][j]);
//             s[++k].data = high[i][j];
//             s[k].x = i;
//             s[k].y = j;
//             maxLen[i][j] = 1;
//         }
//     }
//     sort(s + 1, s + k + 1, cmp);//按照高度排序
//     for (int i = 1; i <= k; i++)
//     {
//         int x1, y1;

//         for (int j = 0; j < 4; j++)
//         {
//             int x = s[i].x;
//             int y = s[i].y;
//             x1 = x + to[j][0];
//             y1 = y + to[j][1];
//             if (check(x1, y1))
//             {
//                 if (high[x][y] > high[x1][y1])
//                 {
//                     maxLen[x][y] = max(maxLen[x1][y1] + 1, maxLen[x][y]);
//                     ans = max(ans, maxLen[x][y]);
//                 }
//             }
//         }
//     }
//     printf("%d", ans);
//     return 0;
// }
