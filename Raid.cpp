// // poj3714 Raid
// #include <iostream>
// #include <cmath>
// #include <iomanip>
// using namespace std;

// struct Node
// {
//     double x;
//     double y;
// };

// float Gzz(Node *stations, Node *agents, int k)
// {
//     double min = sqrt(pow(stations[0].x - agents[0].x, 2) + pow(stations[0].y - agents[0].y, 2));
//     for (int i = 0; i < k; i++)
//     {
//         for (int j = 0; j < k; j++)
//         {
//             if (abs(stations[i].x - agents[j].x) > min || abs(stations[i].y - agents[j].y) > min)
//                 continue;
//             else
//             {
//                 double distance = sqrt(pow(stations[i].x - agents[j].x, 2) + pow(stations[i].y - agents[j].y, 2));
//                 if (min > distance)
//                     min = distance;
//             }
//         }
//     }
//     return min;
// }

// int main()
// {
//     int i;
//     cin >> i;
//     for (int i0 = 0; i0 < i; i0++)
//     {
//         int k;
//         cin >> k;
//         Node *stations = new Node[k];
//         Node *agents = new Node[k];
//         for (int n = 0; n < k; n++)
//         {
//             cin >> stations[n].x >> stations[n].y;
//         }
//         for (int n = 0; n < k; n++)
//         {
//             cin >> agents[n].x >> agents[n].y;
//         }
//         double min = Gzz(stations, agents, k);
//         cout << fixed << setprecision(3) << min << endl;

//         // Remember to free the allocated memory
//         delete[] stations;
//         delete[] agents;
//     }
//     return 0;
// }

// // 2496K 766MS

// // 对点集先按 x xx 排序，再按 y yy 排序。假设有一个求解区间内最小点间距离的函数，对于某个区间，处理完左区间与右区间的点对后，只用对左区间右边界与右区间左边界，可能出现答案的点对计算距离。

// //     一开始爆 T TT，然后认识到了宏定义 m i n minmin 里面放递归函数的危险。函数执行完后，宏定义的 m i n minmin 还会再计算一次，随递归深度 O(2 n) O(2 ^ n) O(2 n) 地计算。
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
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
} ps[maxn << 1];

double dist(int i, int j)
{
    double dx = ps[i].x - ps[j].x, dy = ps[i].y - ps[j].y;
    return sqrt(dx * dx + dy * dy);
}

double solve(int l, int r)
{
    if (r - l <= 1)
        return inf;
    int m = (l + r) >> 1, limitx = ps[m - 1].x;
    double res = min(solve(l, m), solve(m, r));
    for (int i = m - 1; i >= l; i--)
    {
        if (limitx - ps[i].x >= res)
            break;
        for (int j = m; j < r; j++)
        {
            if (ps[j].x - ps[i].x >= res || ps[j].y - ps[i].y >= res)
                break;
            if (ps[j].id != ps[i].id)
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
        for (int k = 0; k < n; k++)
        {
            scanf("%d%d", &ps[k].x, &ps[k].y);
            ps[k].id = 0;
        }
        for (int k = n; k < size; k++)
        {
            scanf("%d%d", &ps[k].x, &ps[k].y);
            ps[k].id = 1;
        }
        sort(ps, ps + size);
        printf("%.3f\n", solve(0, size));
    }
    return 0;
}

// #include <algorithm>
// #include <cmath>
// #include <cstdio>
// #include <cstring>

// #define inf 0x3f3f3f3f
// #define maxn 100005

// using namespace std;

// struct Point
// {
//     int x, y, id;
//     bool operator<(const Point &a) const
//     {
//         return x < a.x || (x == a.x && y < a.y);
//     }
// } map[maxn << 1], tmp[maxn << 1];

// double distance(Point a, Point b)
// {
//     double dx = a.x - b.x, dy = a.y - b.y;
//     return sqrt(dx * dx + dy * dy);
// }

// double closestPair(int l, int r)
// {
//     if (r - l <= 1)
//     {
//         return inf;
//     }
//     int m = (l + r) >> 1;
//     double midX = map[m].x;
//     double d = min(closestPair(l, m), closestPair(m, r));

//     merge(map + l, map + m, map + m, map + r, tmp);
//     copy(tmp, tmp + r - l, map + l);

//     int k = 0;
//     for (int i = l; i < r; i++)
//     {
//         if (fabs(midX - map[i].x) < d)
//         {
//             for (int j = k - 1; j >= 0 && map[i].y - tmp[j].y < d; j--)
//             {
//                 d = min(d, distance(map[i], tmp[j]));
//             }
//             tmp[k++] = map[i];
//         }
//     }
//     return d;
// }

// int main()
// {
//     int t, n, size, x, y;
//     scanf("%d", &t);
//     while (t--)
//     {
//         scanf("%d", &n);
//         size = n << 1;
//         for (int i = 0; i < size; i++)
//         {
//             scanf("%d%d", &x, &y);
//             map[i].x = x, map[i].y = y, map[i].id = i < n ? 0 : 1;
//         }
//         sort(map, map + size);
//         printf("%.3f\n", closestPair(0, size));
//     }
//     return 0;
// }
