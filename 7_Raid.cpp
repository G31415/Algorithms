// poj3714 Raid

// 2496K 719MS
// 对点集先按 x xx 排序，再按 y yy 排序。假设有一个求解区间内最小点间距离的函数，对于某个区间，处理完左区间与右区间的点对后，只用对左区间右边界与右区间左边界，可能出现答案的点对计算距离。
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

#define inf 0x3f3f3f3f // 无穷大
#define maxn 100000    // 点集最大值

struct p
{
    int x; // 横坐标
    int y; // 纵坐标
    int z; // 标识，区分基地和士兵
    bool operator<(const p &a) const
    // 重载了小于运算符 <，使得在排序时按照 x 坐标升序排列，如果 x 坐标相同，则按照 y 坐标升序排列
    {
        if (x != a.x)
            return x < a.x;
        return y < a.y;
    }
} ps[maxn << 1];

double dist(int i, int j) // i和j点间的距离
{
    double dx = ps[i].x - ps[j].x, dy = ps[i].y - ps[j].y;
    return sqrt(dx * dx + dy * dy);
}

double solve(int l, int r) // 分治算法
{
    if (r - l <= 1) // 条带太窄，没有有效对，返回无穷大
        return inf;
    int m = (l + r) >> 1;
    int limitx = ps[m - 1].x;
    double res = min(solve(l, m), solve(m, r));
    for (int i = m - 1; i >= l; i--)
    {
        if (limitx - ps[i].x >= res)
            break;
        for (int j = m; j < r; j++)
        {
            if (ps[j].x - ps[i].x >= res || abs(ps[j].y - ps[i].y) >= res)
                break;
            if (ps[j].z != ps[i].z)
                res = min(res, dist(i, j));
        }
    }
    return res;
}

int main()
{
    int i, n, size;
    scanf("%d", &i);
    while (i--)
    {
        scanf("%d", &n);
        size = n << 1;
        for (int k = 0; k < size; k++)
        {
            scanf("%d%d", &ps[k].x, &ps[k].y);
            ps[k].z = k < n ? 0 : 1;
        }
        sort(ps, ps + size);
        printf("%.3f\n", solve(0, size));
    }
    return 0;
}