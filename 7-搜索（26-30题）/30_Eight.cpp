// poj1077 Eight

// IDA*
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <set>
#define ms(a, b) memset((a), (b), sizeof((a)))
using namespace std;
typedef long long LL;
const int INF = 2e9;
const LL LNF = 9e18;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 10;

int M[100];
int fac[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
char op[4] = {'u', 'd', 'l', 'r'};

int cantor(int s[]) // 获得哈希函数值
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        int num = 0;
        for (int j = i + 1; j < 9; j++)
            if (s[j] < s[i])
                num++;
        sum += num * fac[8 - i];
    }
    return sum + 1;
}

int dis_h(int s[]) // 获得曼哈顿距离
{
    int dis = 0;
    for (int i = 0; i < 9; i++)
        if (s[i] != 9)
        {
            int x = i / 3, y = i % 3;
            int xx = (s[i] - 1) / 3, yy = (s[i] - 1) % 3;
            dis += abs(x - xx) + abs(y - yy);
        }
    return dis;
}

char path[100];
bool IDAstar(int loc, int depth, int pre, int limit)
{
    int h = dis_h(M);
    if (depth + h > limit)
        return false;

    if (h == 0) // 搜到123456789
    {
        path[depth] = '\0';
        puts(path);
        return true;
    }

    int x = loc / 3;
    int y = loc % 3;
    for (int i = 0; i < 4; i++)
    {
        if (i + pre == 1 || i + pre == 5)
            continue; // 方向与上一步相反， 剪枝
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (xx >= 0 && xx <= 2 && yy >= 0 && yy <= 2)
        {
            swap(M[loc], M[xx * 3 + yy]);
            path[depth] = op[i];
            if (IDAstar(xx * 3 + yy, depth + 1, i, limit))
                return true;
            swap(M[loc], M[xx * 3 + yy]);
        }
    }
    return false;
}

int main()
{
    char str[50];
    while (gets(str))
    {
        int cnt = 0, loc;
        for (int i = 0; str[i]; i++)
        {
            if (str[i] == ' ')
                continue;
            if (str[i] == 'x')
                M[cnt] = 9, loc = cnt++;
            else
                M[cnt++] = str[i] - '0';
        }

        int limit;
        for (limit = 0; limit <= 100; limit++) // 迭代加深搜
            if (IDAstar(loc, 0, INF, limit))
                break;
        if (limit > 100)
            puts("unsolvable");
    }
}




/* 
// A*
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <set>
#define ms(a, b) memset((a), (b), sizeof((a)))
using namespace std;
typedef long long LL;
const int INF = 2e9;
const LL LNF = 9e18;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 10;
#define AIM 1 // 123456789的哈希值为1

struct node
{
    int status;
    int s[9];
    int loc;
    int g, h, f;
    bool operator<(const node x) const
    {
        return f > x.f;
    }
};

int vis[MAXN], fac[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
char op[4] = {'u', 'd', 'l', 'r'};
char path[MAXN];
int pre[MAXN];

int cantor(int s[]) // 获得哈希函数值
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        int num = 0;
        for (int j = i + 1; j < 9; j++)
            if (s[j] < s[i])
                num++;
        sum += num * fac[8 - i];
    }
    return sum + 1;
}

int dis_h(int s[]) // 获得曼哈顿距离
{
    int dis = 0;
    for (int i = 0; i < 9; i++)
        if (s[i] != 9) // ‘x’不能算进去，否则不能满足：“每次扩展的节点的 f 值 >= 父节点的 f 值小”
        {
            int x = i / 3, y = i % 3;
            int xx = (s[i] - 1) / 3, yy = (s[i] - 1) % 3;
            dis += abs(x - xx) + abs(y - yy);
        }
    return dis;
}

priority_queue<node> que;
bool Astar(node now)
{
    ms(vis, 0);
    while (!que.empty())
        que.pop();

    now.status = cantor(now.s);
    now.g = 0;
    now.h = dis_h(now.s);
    now.f = now.f + now.h;
    pre[now.status] = -1; // 开始状态的上一个状态为-1，用于输出路径时“刹车”
    vis[now.status] = 1;
    que.push(now);

    node tmp;
    while (!que.empty())
    {
        now = que.top();
        que.pop();
        if (now.status == AIM) // 找到了123456789的状态
            return true;

        int x = now.loc / 3;
        int y = now.loc % 3;
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dir[i][0];
            int yy = y + dir[i][1];
            if (xx >= 0 && xx <= 2 && yy >= 0 && yy <= 2)
            {
                tmp = now;
                tmp.s[x * 3 + y] = tmp.s[xx * 3 + yy]; // 交换位置，下同
                tmp.s[xx * 3 + yy] = 9;
                tmp.status = cantor(tmp.s);
                if (!vis[tmp.status])
                {
                    vis[tmp.status] = 1;
                    tmp.loc = xx * 3 + yy;
                    tmp.g++;                      // g
                    tmp.h = dis_h(tmp.s);         // h
                    tmp.f = tmp.g + tmp.h;        // f
                    pre[tmp.status] = now.status; // tmp.status的上一个状态为now.status
                    path[tmp.status] = op[i];     // 保存操作
                    que.push(tmp);
                }
            }
        }
    }
    return 0;
}

void Print(int status)
{
    if (pre[status] == -1)
        return;
    Print(pre[status]); // 追溯上一个状态
    putchar(path[status]);
}

int main()
{
    char str[50];
    while (gets(str))
    {
        node now;
        int cnt = 0;
        for (int i = 0; str[i]; i++)
        {
            if (str[i] == ' ')
                continue;
            if (str[i] == 'x')
                now.s[cnt] = 9, now.loc = cnt++;
            else
                now.s[cnt++] = str[i] - '0';
        }
        if (!Astar(now))
            puts("unsolvable");
        else
            Print(AIM), putchar('\n');
    }
} 
*/



/* 
// 双向BFS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <set>
#define ms(a, b) memset((a), (b), sizeof((a)))
using namespace std;
typedef long long LL;
const int INF = 2e9;
const LL LNF = 9e18;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 10;

struct node
{
    int status;
    int s[9];
    int loc;
    int id; // id标记正反方向
};

int fac[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int dir[2][4][2] = {-1, 0, 1, 0, 0, -1, 0, 1, 0, 1, 0, -1, 1, 0, -1, 0}; // 正方向
char op[2][4] = {'u', 'd', 'l', 'r', 'l', 'r', 'u', 'd'};

char path[2][MAXN];
int pre[2][MAXN];

int cantor(int s[])
{
    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        int num = 0;
        for (int j = i + 1; j < 9; j++)
            if (s[j] < s[i])
                num++;
        sum += num * fac[8 - i];
    }
    return sum + 1;
}

queue<node> que;
int vis[2][MAXN];
int bfs(node now) // 把两个bfs缩在一起写， 精简代码
{
    ms(vis, 0);
    while (!que.empty())
        que.pop();

    now.status = cantor(now.s);
    now.id = 0;
    pre[0][now.status] = -1;
    vis[0][now.status] = 1;
    que.push(now);

    for (int i = 0; i < 9; i++)
        now.s[i] = i + 1;
    now.loc = 8;
    now.status = cantor(now.s);
    now.id = 1;
    pre[1][now.status] = -1;
    vis[1][now.status] = 1;
    que.push(now);

    while (!que.empty())
    {
        node now = que.front();
        que.pop();

        if (vis[!now.id][now.status])
            return now.status;

        int x = now.loc / 3;
        int y = now.loc % 3;
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dir[now.id][i][0];
            int yy = y + dir[now.id][i][1];
            if (xx >= 0 && xx <= 2 && yy >= 0 && yy <= 2)
            {
                node tmp = now;
                tmp.s[x * 3 + y] = tmp.s[xx * 3 + yy];
                tmp.s[xx * 3 + yy] = 9;
                tmp.status = cantor(tmp.s);
                if (!vis[now.id][tmp.status])
                {
                    vis[now.id][tmp.status] = 1;
                    tmp.loc = xx * 3 + yy;
                    path[now.id][tmp.status] = op[now.id][i];
                    pre[now.id][tmp.status] = now.status;
                    que.push(tmp);
                }
            }
        }
    }
}

void Print1(int status) // 输出正方向的路径
{
    if (pre[0][status] == -1)
        return;
    Print1(pre[0][status]);
    putchar(path[0][status]);
}

void Print2(int status) // 输出反方向的路径
{
    if (pre[1][status] == -1)
        return;
    putchar(path[1][status]);
    Print2(pre[1][status]);
}

int main()
{
    char tmp[50];
    while (gets(tmp))
    {
        node beg;
        int cnt = 0;
        for (int i = 0; tmp[i]; i++)
        {
            if (tmp[i] == ' ')
                continue;
            if (tmp[i] == 'x')
                beg.s[cnt] = 9, beg.loc = cnt++;
            else
                beg.s[cnt++] = tmp[i] - '0';
        }
        int status = bfs(beg);
        if (status == -1)
            puts("unsolvable");
        else
        {
            Print1(status);
            Print2(status); // 输出路径
            putchar('\n');
        }
    }
} 
*/