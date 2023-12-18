// poj1324 Holedox Moving

// 题意：给出一个n *m的贪吃蛇地图，以及贪吃蛇现在身体各个块所在的位置，求它的头走到（1, 1）位置最少需要多少步。
// 注意：蛇在移动的过程中不能走到障碍物上，也不能撞到自己的身体上。

// 直接BFS，不过这里的vis状态表示要注意。由于蛇最长为8格。所以用vis[21][21][1 << 14] 表示蛇的这种状态是否已经出现.其中vis的前两维表示蛇头的坐标,后一维的二进制形式的每2位(可表0 - 3) 表示从1到L - 1开始该蛇的身体在该蛇身体的前一格的方向.这样就能用最小的空间表示完整个蛇在迷宫的状态了.

// 现在要求最小距离,不用dist[][][] 了, 因为太耗空间了.用Node节点, Node中有x, y, st, dist 4个属性, 前3个属性对应vis数组的前三维.最后一个属性是当前状态的最小距离.

//  在BFS扩展的时候,对于4个方向, 计算得到nx和ny, 然后判断nx和ny是否越界, 是否是障碍, 是否会与蛇的旧身体位置冲突.如果以上情况都不会发生, 那么就生成了一个蛇与迷宫的新状态.

// 注意,由于vis数组很大, 如果对于每个kase都初始化vis数组浪费时间, 所以在申请了全局变量vis之后, 对于每个kase, 都只用当前的kase值去标记vis表示当前状态已出现.

// 23480K	1735MS
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxr = 21;
const int maxc = 21;
int vis[maxr][maxc][1 << 14]; // vis第三维的高位二进制表示紧接着蛇头的那格在蛇头的相对方向
int maze[maxr][maxc];
int R, C;
struct Node // 注意这里记录的st状态中的方向是指,后面一个格子处于前面一个格子的哪个方向
{
    int x, y;
    int st, dist;
    Node(int x, int y, int st, int dist) : x(x), y(y), st(st), dist(dist) {}
};

int L;                    // 蛇长
int kase = 0;             // 当前实例
int dir[10];              // 用来保存解码后的方向
int dx[] = {1, 0, -1, 0}; // 下,左,上,右
int dy[] = {0, -1, 0, 1};

bool check(int x, int y, Node node) // 判断x,y坐标是否处于node状态的蛇身
{
    for (int i = L - 1; i >= 1; i--)
    {
        dir[i] = node.st & 3; // 提取相对方向
        node.st >>= 2;
    }
    int xx = node.x, yy = node.y;
    for (int i = 1; i < L; i++)
    {
        xx += dx[dir[i]];
        yy += dy[dir[i]];
        if (xx == x && yy == y)
            return true; // 表示冲突
    }
    return false; // 表示无冲突
}

queue<Node> Q;

int BFS(Node nod)
{
    kase++;
    if (nod.x == 1 && nod.y == 1)
        return 0;
    while (!Q.empty())
        Q.pop();
    Q.push(nod);
    vis[nod.x][nod.y][nod.st] = kase;
    while (!Q.empty())
    {
        Node node = Q.front();
        Q.pop();
        int x = node.x, y = node.y, st = node.st, dist = node.dist;
        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx == 1 && ny == 1)
                return dist + 1;
            if (nx < 1 || nx > R || ny < 1 || ny > C || maze[nx][ny] == 1 || check(nx, ny, node))
                continue;
            int ndist = dist + 1, nst = (st >> 2) + (((d + 2) % 4) << (2 * (L - 2))); // 新距离,新状态,注意这里(d+2)%4表示对d取反向
            if (vis[nx][ny][nst] == kase)
                continue; // 之前走过
            Q.push(Node(nx, ny, nst, ndist));
            vis[nx][ny][nst] = kase;
        }
    }
    return -1;
}

int main()
{
    while (scanf("%d%d%d", &R, &C, &L) == 3)
    {
        if (R == 0 && C == 0 && L == 0)
            break;
        int x, y, nx, ny;
        Node node(0, 0, 0, 0);
        scanf("%d%d", &node.x, &node.y);
        x = node.x, y = node.y;
        for (int i = 1; i < L; i++)
        {
            scanf("%d%d", &nx, &ny);
            for (int d = 0; d < 4; d++)
            {
                if (x + dx[d] == nx && y + dy[d] == ny)
                {
                    node.st = (node.st << 2) + d;
                    break;
                }
            }
            x = nx, y = ny;
        }
        int blocks;
        scanf("%d", &blocks);
        memset(maze, 0, sizeof(maze));
        for (int i = 1; i <= blocks; i++)
        {
            scanf("%d%d", &x, &y);
            maze[x][y] = 1;
        }
        printf("Case %d: %d\n", kase, BFS(node));
    }
    return 0;
}

/*
// BFS+状态压缩
// 两位二进制(4个方向)记录后一个蛇身相对前一个的位置，以此将蛇身记录为数值
// 25480K	1313MS

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAX = 22;
const int MAXN = 1000000;
const int MAXLEN = 1 << 14 + 1;

struct Snake
{
    int x, y;
} snake[10];

struct State
{
    Snake h; // 头部坐标
    unsigned hash;
    int step;
} s[MAXN];

int row, col, len;
bool map[MAX][MAX];       // 是否存在障碍
bool v[MAX][MAX][MAXLEN]; // 状态记录
int mov[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int get_next_hash(int hash, Snake pre, Snake next)
{
    const int INF = (1 << ((len - 1) << 1)) - 1;
    int dx = pre.x - next.x;
    int dy = pre.y - next.y;
    for (int i = 0; i < 4; i++)
    {
        if (mov[i][0] == dx && mov[i][1] == dy)
        {
            hash <<= 2;
            hash &= INF;
            hash |= i;
            break;
        }
    }
    return hash;
}
// 是否撞到自己或障碍
bool judge(State cur, Snake t)
{
    if (t.x > 0 && t.x <= row && t.y > 0 && t.y <= col && !map[t.x][t.y])
    {
        for (int i = 1; i < len; i++)
        {
            int key = (1 << 2) - 1;
            key &= cur.hash;
            cur.hash >>= 2;
            cur.h.x += mov[key][0];
            cur.h.y += mov[key][1];
            if (cur.h.x == t.x && cur.h.y == t.y) // 撞到了
                return false;
        }
        return true;
    }
    return false;
}
void bfs()
{
    int front = 0, tail = 1;
    s[0].step = 0;
    if (s[0].h.x == 1 && s[0].h.y == 1)
    {
        printf("0\n");
        return;
    }
    while (front < tail)
    {
        for (int i = 0; i < 4; i++)
        {
            Snake t;
            t.x = s[front].h.x + mov[i][0];
            t.y = s[front].h.y + mov[i][1];
            if (t.x == 1 && t.y == 1)
            {
                printf("%d\n", s[front].step + 1);
                return;
            }
            if (judge(s[front], t))
            {
                s[tail].hash = get_next_hash(s[front].hash, s[front].h, t);
                if (!v[t.x][t.y][s[tail].hash])
                {
                    v[t.x][t.y][s[tail].hash] = true;
                    s[tail].h = t;
                    s[tail].step = s[front].step + 1;
                    tail++;
                }
            }
        }
        front++;
    }
    printf("-1\n");
}
// 初始化蛇的开始位置
void init_snake()
{
    s[0].h = snake[0];
    s[0].hash = 0;
    for (int i = len - 1; i > 0; i--)
        s[0].hash = get_next_hash(s[0].hash, snake[i], snake[i - 1]);
    v[s[0].h.x][s[0].h.y][s[0].hash] = true;
}

int main()
{
    int counter = 0;
    while (scanf("%d%d%d", &row, &col, &len), row && col && len)
    {
        memset(map, false, sizeof(map));
        memset(v, false, sizeof(v));
        for (int i = 0; i < len; i++)
            scanf("%d%d", &snake[i].x, &snake[i].y);
        int m, x, y;
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d", &x, &y);
            map[x][y] = true;
        }
        init_snake();
        printf("Case %d: ", ++counter);
        bfs();
    }
    return 0;
}
*/