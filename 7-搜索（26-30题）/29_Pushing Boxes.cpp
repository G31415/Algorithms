// poj1475 Pushing Boxes

// 大意：
// 给出多个地图，求把箱子推到T的最少推的次数，若有多个方案，输出走路最少的，输出路径，大写字母表示推箱子，小写字母表示人走。

// A *搜索，H值是题目天然给出的推箱子数，每次搜索，注意更新，然后其实不难写，就是看着比较宽。
// 注意记录路径，倒着装回去再输出。

// 9400K 250MS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
    using namespace std;

const int Max = 20;

struct node
{
    int x, y;
    node() {}
    node(int a, int b) { x = a, y = b; }
    bool operator==(const node &X) const
    {
        return x == X.x && y == X.y;
    }
} S, B, T;
struct A
{
    int pu, wl;
    node p, b;
    A() {}
    A(int a, int x, node c, node d) { pu = a, wl = x, p = c, b = d; }
    bool operator>(const A &X) const
    {
        if (pu == X.pu)
            return wl > X.wl;
        return pu > X.pu;
    }
};

int N, M;
char map[Max + 5][Max + 5], rt[1000];
int dd[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int H[Max + 5][Max + 5][Max + 5][Max + 5][2], fa[Max + 5][Max + 5][Max + 5][Max + 5][4];

bool Check_Move(node t)
{
    if (t.x < 1 || t.y < 1 || t.x > N || t.y > M)
        return 0;
    return map[t.x][t.y] != '#';
}
bool Check_now_better(A t)
{
    if (H[t.p.x][t.p.y][t.b.x][t.b.y][0] == t.pu)
        return t.wl < H[t.p.x][t.p.y][t.b.x][t.b.y][1];
    return t.pu < H[t.p.x][t.p.y][t.b.x][t.b.y][0];
}

void Print(node p, node b, int mvs)
{
    int x1, y1, x2, y2;
    char tmp;
    rt[mvs + 1] = 0;
    for (; mvs; --mvs)
    {
        x1 = fa[p.x][p.y][b.x][b.y][0],
        y1 = fa[p.x][p.y][b.x][b.y][1],
        x2 = fa[p.x][p.y][b.x][b.y][2],
        y2 = fa[p.x][p.y][b.x][b.y][3];
        if (x2 != b.x || y2 != b.y)
            tmp = 'A';
        else
            tmp = 'a';
        if (p.x - x1 == 1)
            rt[mvs] = 'S' - 'A' + tmp;
        if (p.y - y1 == 1)
            rt[mvs] = 'E' - 'A' + tmp;
        if (p.x - x1 == -1)
            rt[mvs] = 'N' - 'A' + tmp;
        if (p.y - y1 == -1)
            rt[mvs] = 'W' - 'A' + tmp;
        p.x = x1, p.y = y1, b.x = x2, b.y = y2;
    }
    printf("%s\n", rt + 1);
}

void Astar()
{
    memset(H, 0x3f, sizeof H);
    memset(fa, 0x3f, sizeof fa);
    priority_queue<A, vector<A>, greater<A>> Q;
    A t = A(0, 0, S, B), newin;
    Q.push(t);
    while (!Q.empty())
    {
        t = Q.top();
        Q.pop();
        if (t.b == T)
        {
            Print(t.p, t.b, t.pu + t.wl);
            return;
        }
        for (int i = 0; i < 4; ++i)
        {
            newin.p.x = t.p.x + dd[i][0];
            newin.p.y = t.p.y + dd[i][1];
            if (!Check_Move(newin.p))
                continue;
            if (newin.p == t.b)
            { // 推箱子走
                newin.b.x = t.b.x + dd[i][0];
                newin.b.y = t.b.y + dd[i][1];
                if (!Check_Move(newin.b))
                    continue;
                newin.pu = t.pu + 1;
                newin.wl = t.wl;
            }
            else
                newin.b = t.b, newin.wl = t.wl + 1, newin.pu = t.pu; // 人走
            if (Check_now_better(newin))
            {
                fa[newin.p.x][newin.p.y][newin.b.x][newin.b.y][0] = t.p.x;
                fa[newin.p.x][newin.p.y][newin.b.x][newin.b.y][1] = t.p.y;
                fa[newin.p.x][newin.p.y][newin.b.x][newin.b.y][2] = t.b.x;
                fa[newin.p.x][newin.p.y][newin.b.x][newin.b.y][3] = t.b.y;
                H[newin.p.x][newin.p.y][newin.b.x][newin.b.y][0] = newin.pu;
                H[newin.p.x][newin.p.y][newin.b.x][newin.b.y][1] = newin.wl;
                Q.push(newin);
            }
        }
    }
    puts("Impossible.");
}

int main()
{
    int cas = 0;
    while (~scanf("%d%d", &N, &M) && N)
    {
        for (int i = 1; i <= N; ++i)
            scanf("%s", map[i] + 1);
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= M; ++j)
            {
                if (map[i][j] == 'S')
                    S = node(i, j);
                if (map[i][j] == 'B')
                    B = node(i, j);
                if (map[i][j] == 'T')
                    T = node(i, j);
            }
        printf("Maze #%d\n", ++cas);
        Astar();
        putchar(10);
    }
    return 0;
}
/*
1 7
SB....T
1 7
SB..#.T
7 11
###########
#T##......#
#.#.#..####
#....B....#
#.######..#
#.....S...#
###########
8 4
....
.##.
.#..
.#..
.#.B
.##S
....
###T
8 9
#########
#......T#
#.S.....#
##B######
#.......#
#.......#
#.......#
#########
0 0
SSesswNNNNwnEEEEE
*/