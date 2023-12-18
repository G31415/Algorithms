// poj3660 Cow Contest

// 大意：有n头牛比赛，m种比赛结果，问你一共有多少头牛的排名被确定了，其中如果a战胜b，b战胜c，则也可以说a战胜c，即可以传递胜负。
// 求能确定排名的牛的数目。

// 如果一头牛被x头牛打败，打败y头牛，且x + y = n - 1，则我们容易知道这头牛的排名就被确定了，所以我们只要将任何两头牛的胜负关系确定了，在遍历所有牛判断一下是否满足x + y = n - 1，将满足这个条件的牛数目加起来就是所求解。

// 可以用floyd传递闭包算法，由每个顶点的出度与入度 （出度 + 入度 = 顶点数 - 1）则能够确定其编号的牛数量。归类到最短路.....

// 180K	63MS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <math.h>
#define N 110

using namespace std;

int n, m;
int maps[N][N];

void floyd()
{
    int i, j, k;
    for (k = 1; k <= n; k++)
    {
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                maps[i][j] = maps[i][j] || (maps[i][k] && maps[k][j]);
            }
        }
    }
}

int main()
{
    int i, j, a, b;
    scanf("%d%d", &n, &m);
    memset(maps, 0, sizeof(maps));
    for (i = 0; i < m; i++)
    {
        scanf("%d%d", &a, &b);
        maps[a][b] = 1;
    }

    floyd();
    int ans = 0, cot;
    for (i = 1; i <= n; i++)
    {
        cot = 0;
        for (j = 1; j <= n; j++)
        {
            if (maps[i][j])
                cot++;
            if (maps[j][i])
                cot++;
        }
        if (cot == n - 1)
            ans++;
    }
    printf("%d\n", ans);
}