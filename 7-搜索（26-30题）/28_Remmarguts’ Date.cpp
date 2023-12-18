// poj2449 Remmarguts’ Date

// 大意：给一个有向图,求起点s到终点e的第K短路长度,没有就输出 -1.

// 这道题如果直接优先队列跑的话,最坏时间复杂度为O(K*(N+M)*(log(N+M))O(K∗(N+M)∗(log(N+M)),因为我们要跑K次路径.
// 现提供A∗做法:
// 比起普通优先队列,A∗多了一个估价函数f(x),为了保证最优解,f(x)要满足一个基本准则
// 设当前状态state 到目标状态所需代价的估计值为f(state).
// 实际所需价值为g(state).
// 对于任意的state,应该有f(state)≤ g(state)

// 这种带有估计函数的优先队列BFS就称为A*(A Star).只要保证f(state) ≤ g(state) ,
// A*就一定能在目标状态第一次从堆中取出时得到最优解,并且在搜索过程中每个状态只需要被拓展一次.

// 下面给出简要证明：
// 设当前状态S SS并不是最优解,
// 则S的 “当前代价”+f(S)≥当前处在未来最优路径上的T的“代价”+f(T),所以T先拓展,S则被忽略.

// 第K短路则运用了A∗的排除多余状态与优先队列BFS,第几次取出ed,即求到第几短路的性质来解决问题,A∗主要起优化作用.
// 先反向求从ed跑到st的最短路,得到估价函数f
// 后正常BFS即可.

// 19780K	344MS
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

const int N = 1e3 + 10;
const int inf = 0x3f3f3f3f;
const int M = 1e5 + 10;
struct edge
{
    int x, y, d, next;
} a[M], b[M];

int len, last1[N], last2[N];
void ins(int x, int y, int d)
{
    a[++len].x = x, a[len].y = y;
    a[len].d = d;
    a[len].next = last1[x];
    last1[x] = len;
    b[len].x = y;
    b[len].y = x;
    b[len].d = d;
    b[len].next = last2[y];
    last2[y] = len;
}
struct nde
{
    int x, d;
    nde() {}
    nde(int x, int d) : x(x), d(d) {}
    bool operator<(const nde a) const { return d > a.d; }
};

int f[N];
bool v[N];
int st, ed;
void dijk_p()
{
    priority_queue<nde> q;
    memset(f, 0x3f, sizeof(f));
    memset(v, false, sizeof(v));
    q.push(nde(ed, 0));
    f[ed] = 0;
    while (!q.empty())
    {
        nde t = q.top();
        q.pop();
        int x = t.x;
        if (v[x])
            continue;
        v[x] = true;
        for (int k = last2[x]; k; k = b[k].next)
        {
            int y = b[k].y;
            if (f[y] > f[x] + b[k].d)
            {
                f[y] = f[x] + b[k].d;
                q.push(nde(y, f[y]));
            }
        }
    }
}
struct node
{
    int x, d, f;
    node() {}
    node(int x, int d, int f) : x(x), d(d), f(f) {}
    bool operator<(const node a) const { return f == a.f ? d > a.d : f > a.f; }
};
int kl;
void dijk_AS()
{
    priority_queue<node> q;
    int cnt = 0;
    if (f[st] == inf)
    {
        puts("-1");
        return;
    }
    q.push(node(st, 0, f[st]));
    while (!q.empty())
    {
        node t = q.top();
        q.pop();
        if (t.x == ed)
            cnt++;
        if (kl == cnt)
        {
            printf("%d\n", t.d);
            return;
        }
        int x = t.x;
        for (int k = last1[x]; k; k = a[k].next)
        {
            int y = a[k].y;
            int d = t.d + a[k].d;
            q.push(node(y, d, d + f[y]));
        }
    }
    puts("-1");
}

int main()
{
    int n, m;
    len = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int x, y, d;
        scanf("%d%d%d", &x, &y, &d);
        ins(x, y, d);
    }
    scanf("%d%d%d", &st, &ed, &kl);
    if (st == ed)
        kl++;
    dijk_p();
    dijk_AS();
    return 0;
}
