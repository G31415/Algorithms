// poj3169 Layout

// 大意：
// 一共有n头牛，有ml个关系好的牛的信息，有md个关系不好的牛的信息，对应输入的第一行的三个元素，接下来ml行，每行三个元素A, B, D，表示A牛和B牛相距不希望超过D，接下来md行，每行三个元素A, B, D表示A牛和B牛的相距至少要有D才行。求1号牛和n号牛的最大距离，如果距离无限大输出 - 2，如果无解输出 - 1。

// 思路：
// 差分约束系统问题，能够将问题转化为最短路问题。

// 对应ml条信息：
// 牛A和牛B的距离不想超过D，那么建立不等式：posA - posB <= D;加入到图中直接add（A，B，D）即可

// 对应md条信息：
// 牛A和牛B的距离至少要为D，那么建立不等式：posA - posB >= D，
// 那么我们左右两边同乘 - 1有：posB - posA <= -D，那么加入到图中add（B，A， - D）即可。

// 图建立好之后直接跑最短路即可。对应输出：
// 如果dis[n] == inf，输出 - 2；
// 否则输出dis[n]；
// 如果在跑SPFA过程中发现了负环，说明问题无解，那么输出 - 1.

// 472K	47MS
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
struct node
{
    int from;
    int to;
    int w;
    int next;
} e[200000];
int head[10000];
int vis[10000];
int out[10000];
int dis[10000];
int n, ml, dl, cont;
void add(int from, int to, int w)
{
    e[cont].to = to;
    e[cont].w = w;
    e[cont].next = head[from];
    head[from] = cont++;
}
void SPFA()
{
    for (int i = 1; i <= n; i++)
        dis[i] = 0x3f3f3f3f;
    dis[1] = 0;
    memset(vis, 0, sizeof(vis));
    memset(out, 0, sizeof(out));
    queue<int> s;
    s.push(1);
    int flag = 0;
    while (!s.empty())
    {
        int u = s.front();
        out[u]++;
        if (out[u] > n)
        {
            flag = 1;
            break;
        }
        s.pop();
        vis[u] = 0;
        for (int i = head[u]; i != -1; i = e[i].next)
        {
            int v = e[i].to;
            int w = e[i].w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (vis[v] == 0)
                {
                    vis[v] = 1;
                    s.push(v);
                }
            }
        }
    }
    if (flag == 1)
    {
        printf("-1\n");
    }
    else if (dis[n] == 0x3f3f3f3f)
        printf("-2\n");
    else
        printf("%d\n", dis[n]);
}
int main()
{
    while (~scanf("%d%d%d", &n, &ml, &dl))
    {
        cont = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < ml; i++)
        {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            add(x, y, w);
        }
        for (int i = 0; i < dl; i++)
        {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            add(y, x, -w);
        }
        SPFA();
    }
}