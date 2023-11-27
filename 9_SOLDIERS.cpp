// poj1723 SOLDIERS
// 212K	16MS

// cost=∑|y[i]−k| 货仓选址问题，k取y[i]的中位数就可以了
// cost=∑|x[i]−(k+i)|=∑|(x[i]−i)−k| x-i也是与y相同的问题

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
#define Max 10000

int N;
int n;
int x[Max];
int y[Max];
int disx;
int disy;
int dis;

int main()
{
    scanf("%d", &N);
    n = N >> 1;
    for (int i = 0; i < N; i++)
        scanf("%d %d", &x[i], &y[i]);
    sort(y, y + N);
    disy = y[n];
    sort(x, x + N);
    for (int i = 0; i < N; i++)
        x[i] -= i;
    sort(x, x + N);
    disx = x[n];
    for (int i = 0; i < N; i++)
    {
        dis += abs(disx - x[i]);
        dis += abs(disy - y[i]);
    }
    printf("%d", dis);
    return 0;
}
