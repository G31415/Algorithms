// poj1201 Intervals

// 大意：有n个区间[ai, bi]，每个区间至少需要选ci个数.求出新的集合Z在满足所有约束条件下，至少包含多少个数。

// 用Si 表示1 - i 中被选出的数的个数.不等式条件： 
// 1、Si >= Si - 1 ，从1 到 i 中选的数必定不会比从1 到 i - 1中选的数少。 
// 2、Si - Si - 1 <= 1 = >> Si - 1 >= Si - 1,相邻之间选的数的个数差不会超过1个数。 
// 3、Sb - Sa - 1 >= c = >> Sb >= Sa - 1 + c, [ a, b ] 中至少选c个数。 
// 同时看看源点是否满足：从源点出发，一点可以走到所有边 
// 由于条件1是从i - 1 向 i 连接一条 权值为0的边，0 - > 1->2 - > 3 … 50001因此源点0是可以到达所有边的。 
// 题目中ai, bi 从0开始的，由于我们一般用0来作为源点，所以在建图的时候把a和b都加1.由于求的是最小值，因此求一遍最长路就行了.

// 2552K	250MS
#include <iostream>
#include <cstring>

using namespace std;

const int N = 50010, M = 150010;

int n;
int h[N], w[M], e[M], ne[M], idx;
int dist[N];
int q[N];
bool st[N];

void add(int a, int b, int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void spfa()
{
    memset(dist, -0x3f, sizeof dist);
    int hh = 0, tt = 1;
    dist[0] = 0;
    q[0] = 0;
    st[0] = true;
    while (hh != tt)
    {
        int t = q[hh++];
        if (hh == N)
            hh = 0;
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] < dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    q[tt++] = j;
                    if (tt == N)
                        tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= 50001; i++)
    {
        add(i - 1, i, 0);
        add(i, i - 1, -1);
    }
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a++;
        b++;
        add(a - 1, b, c);
    }
    spfa();
    printf("%d", dist[50001]);
    return 0;
}
