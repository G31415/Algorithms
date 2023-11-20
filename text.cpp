#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define inf 0x3f3f3f3f
#define maxn 100000

struct p
{
    int x, y, id;
    bool operator<(const p &a) const
    {
        if (x != a.x)
            return x < a.x;
        return y < a.y;
    }
};

double dist(const p &a, const p &b)
{
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double solve(int l, int r, p ps[])
{
    if (r - l <= 1)
        return inf;
    if (r - l <= 3)
    {
        double minDist = inf;
        for (int i = l; i < r; i++)
        {
            for (int j = i + 1; j < r; j++)
            {
                if (ps[i].id != ps[j].id)
                    minDist = min(minDist, dist(ps[i], ps[j]));
            }
        }
        return minDist;
    }

    int m = (l + r) >> 1, limitx = ps[m - 1].x;
    double res = min(solve(l, m, ps), solve(m, r, ps));

    // 构建 strip 数组
    vector<p> strip;
    for (int i = l; i < r; i++)
    {
        if (abs(ps[i].x - limitx) < res)
            strip.push_back(ps[i]);
    }
    sort(strip.begin(), strip.end(), [](const p &a, const p &b)
         { return a.y < b.y; });

    // 在 strip 数组中寻找最小距离
    for (int i = 0; i < strip.size(); i++)
    {
        for (int j = i + 1; j < strip.size() && strip[j].y - strip[i].y < res; j++)
        {
            if (strip[i].id != strip[j].id)
                res = min(res, dist(strip[i], strip[j]));
        }
    }

    return res;
}

int main()
{
    int t, n, size;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        size = n << 1;
        p *ps = new p[size]; // dynamic allocation
        for (int k = 0; k < size; k++)
        {
            scanf("%d%d", &ps[k].x, &ps[k].y);
            ps[k].id = k < n ? 0 : 1;
        }
        sort(ps, ps + size);
        printf("%.3f\n", solve(0, size, ps));
        delete[] ps; // deallocate the memory
    }
    return 0;
}
