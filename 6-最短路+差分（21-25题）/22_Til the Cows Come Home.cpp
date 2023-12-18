// poj2387 Til the Cows Come Home

// 大意：有N个点，给出从a点到b点的距离，当然a和b是互相可以抵达的，问从1到n的最短距离

// 模版题，这题要注意的是有重边，dijkstra的算法需要考虑下，bellman-ford和spfa可以忽略这个问题

// dijkstra  4100K	125MS
#include <iostream>
    using namespace std;
#define inf 1 << 29
#define MAXV 1005

int map[MAXV][MAXV];
int n, m;

void dijkstra()
{
    int i, j, min, v;
    int d[MAXV];
    bool vis[MAXV];

    for (i = 1; i <= n; i++)
    {
        vis[i] = 0;
        d[i] = map[1][i];
    }

    for (i = 1; i <= n; i++)
    {
        min = inf;
        for (j = 1; j <= n; j++)
            if (!vis[j] && d[j] < min)
            {
                v = j;
                min = d[j];
            }
        vis[v] = 1;

        for (j = 1; j <= n; j++)
            if (!vis[j] && d[j] > map[v][j] + d[v])
                d[j] = map[v][j] + d[v];
    }
    printf("%d\n", d[n]);
}

int main()
{
    int i, j, a, b, c;
    while (~scanf("%d%d", &m, &n))
    {
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (i == j)
                    map[i][i] = 0;
                else
                    map[i][j] = map[j][i] = inf;

        for (i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            if (map[a][b] > c)
                map[a][b] = map[b][a] = c;
        }
        dijkstra();
    }
    return 0;
}


/* 
// bellman-ford  156K  63MS
#include <iostream>
using namespace std;
#define inf 1 << 29
#define MAXM 2005
#define MAXV 1005

typedef struct
{
    int a, b, w;
} Edge;

Edge edge[MAXM];
int n, m;

void bellman_ford()
{
    int i, j;
    int d[MAXV];
    for (i = 2; i <= n; i++)
        d[i] = inf;
    d[1] = 0;

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            if (d[edge[j].a] > edge[j].w + d[edge[j].b])
                d[edge[j].a] = edge[j].w + d[edge[j].b];
            if (d[edge[j].b] > edge[j].w + d[edge[j].a])
                d[edge[j].b] = edge[j].w + d[edge[j].a];
        }
    }
    printf("%d\n", d[n]);
}

int main()
{
    int i, a, b, c;
    while (~scanf("%d%d", &m, &n))
    {
        for (i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            edge[i].a = a;
            edge[i].b = b;
            edge[i].w = c;
        }
        bellman_ford();
    }
    return 0;
} 
*/


/* 
// spfa 248K  0MS
#include <iostream>
#include <queue>
using namespace std;
#define inf 1 << 29
#define MAXM 4005
#define MAXV 1005

typedef struct
{
    int a, b, w, next;
} Edge;

Edge edge[MAXM];
int n, m, headlist[MAXV];

void spfa()
{
    int i, d[MAXV], v, vis[MAXV];
    queue<int> q;
    for (i = 2; i <= n; i++)
    {
        d[i] = inf;
        vis[i] = 0;
    }
    d[1] = 0;
    vis[1] = 1;
    q.push(1);
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        vis[v] = 0;

        for (i = headlist[v]; i != -1; i = edge[i].next)
            if (d[v] + edge[i].w < d[edge[i].b])
            {
                d[edge[i].b] = d[v] + edge[i].w;
                if (!vis[edge[i].b])
                {
                    vis[edge[i].b] = 1;
                    q.push(edge[i].b);
                }
            }
    }
    printf("%d\n", d[n]);
}

int main()
{
    int i, a, b, c;
    while (~scanf("%d%d", &m, &n))
    {
        for (i = 1; i <= n; i++)
            headlist[i] = -1;
        for (i = 1; i <= 2 * m; i += 2)
        {
            scanf("%d%d%d", &a, &b, &c);
            edge[i].a = a;
            edge[i].b = b;
            edge[i].w = c;
            edge[i].next = headlist[a];
            headlist[a] = i;
            edge[i + 1].a = b;
            edge[i + 1].b = a;
            edge[i + 1].w = c;
            edge[i + 1].next = headlist[b];
            headlist[b] = i + 1;
        }
        spfa();
    }
    return 0;
} 
*/