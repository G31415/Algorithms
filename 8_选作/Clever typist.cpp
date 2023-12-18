// poj1184 聪明的打字员

// 6064K	16MS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;

int pos[6] = {100000, 10000, 1000, 100, 10, 1};
bool v[1000005][6];
int target, tar[6];
struct node
{
    int num;
    int cursor;
    int step;
    node(int n, int c, int s) : num(n), cursor(c), step(s) {}
};
node n(0, 0, 0);

int swap(int num, int p1, int p2)
{
    int v1 = (num / pos[p1]) % 10;
    int v2 = (num / pos[p2]) % 10;
    num += (v2 - v1) * pos[p1];
    num += (v1 - v2) * pos[p2];
    return num;
}
int up(int num, int p)
{
    return num + pos[p];
}
int down(int num, int p)
{
    return num - pos[p];
}

int bfs()
{
    memset(v, false, sizeof(v));
    queue<node> q;
    q.push(n);
    v[n.num][0] = true;
    while (!q.empty())
    {
        node t = q.front();
        q.pop();
        int num = t.num, cursor = t.cursor, step = t.step;
        if (num == target)
            return step;
        step++;
        if (cursor != 0)
        {
            int temp = swap(num, 0, cursor);
            if (!v[temp][cursor])
            {
                q.push(node(temp, cursor, step));
                v[temp][cursor] = true;
            }
        }
        if (cursor != 5)
        {
            int temp = swap(num, 5, cursor);
            if (!v[temp][cursor])
            {
                q.push(node(temp, cursor, step));
                v[temp][cursor] = true;
            }
        }
        int val = (num / pos[cursor]) % 10;
        if (val != 9 && val != tar[cursor])
        {
            int temp = up(num, cursor);
            if (!v[temp][cursor])
            {
                q.push(node(temp, cursor, step));
                v[temp][cursor] = true;
            }
        }
        if (val != 0 && val != tar[cursor])
        {
            int temp = down(num, cursor);
            if (!v[temp][cursor])
            {
                q.push(node(temp, cursor, step));
                v[temp][cursor] = true;
            }
        }
        if (cursor != 0 && (val == tar[cursor] || cursor == 5))
        {
            if (!v[num][cursor - 1])
            {
                q.push(node(num, cursor - 1, step));
                v[num][cursor - 1] = true;
            }
        }
        if (cursor != 5 && (val == tar[cursor] || cursor == 0))
        {
            if (!v[num][cursor + 1])
            {
                q.push(node(num, cursor + 1, step));
                v[num][cursor + 1] = true;
            }
        }
    }
    return -1;
}

int main()
{
    char a[10], b[10];
    scanf("%s %s", a, b);
    for (int i = 0; i < 6; ++i)
    {
        tar[i] = a[i] - '0';
        n.num += tar[i] * pos[i];
    }
    for (int i = 0; i < 6; ++i)
    {
        tar[i] = b[i] - '0';
        target += tar[i] * pos[i];
    }
    printf("%d\n", bfs());
}