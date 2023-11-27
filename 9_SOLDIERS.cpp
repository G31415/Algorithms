// poj1723 SOLDIERS
// 212K	16MS

// cost=∑|y[i]−k| 货仓选址问题，k取y[i]的中位数就可以了
// cost=∑|x[i]−(k+i)|=∑|(x[i]−i)−k| x-i也是与y相同的问题

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#define Max 0x2710 // 十六进制减少运行时间
using namespace std;

int N;
int x[Max];
int y[Max];
int dis;

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d%d", &x[i], &y[i]);
    sort(x, x + N);
    for (int i = 0; i < N; i++)
        x[i] -= i;
    sort(x, x + N);
    sort(y, y + N);
    for (int i = 0; i < N; i++)
        dis += abs(x[N >> 1] - x[i]) + abs(y[N >> 1] - y[i]);
    printf("%d\n", dis);
    return 0;
}
