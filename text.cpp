// By SiriusRen
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, xx[] = {1, -1, 0, 0}, yy[] = {0, 0, 1, -1};
struct Point
{
    int x, y;
} point[10005];
bool cmp1(Point a, Point b) { return a.x < b.x; }
bool cmp2(Point a, Point b) { return a.y < b.y; }
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &point[i].x, &point[i].y);
    if (n & 1)
    {
        int ans = 0, l, r;
        sort(point + 1, point + 1 + n, cmp1);
        int ansx = point[n / 2 + 1].x;
        sort(point + 1, point + 1 + n, cmp2);
        int ansy = point[n / 2 + 1].y;
        for (l = n / 2 + 1; l >= 1; l--)
            if (point[l].y != point[l - 1].y)
                break;
        for (r = n / 2 + 1; r <= n; r++)
            if (point[r].y != point[r + 1].y)
                break;
        for (int i = l; i <= r; i++)
        {
            if (i == r)
            {
                for (int i = 1; i <= n; i++)
                {
                    ans += fabs(point[i].x - ansx);
                    ans += fabs(point[i].y - ansy);
                }
                printf("%d 1\n", ans);
                return 0;
            }
            if (ansx == point[i].x)
                goto end;
        }
    end:
        int answer = 0x3ffffff, temp;
        for (int i = 0; i <= 3; i++)
        {
            ans = 0;
            int tempx = ansx + xx[i];
            int tempy = ansy + yy[i];
            for (int i = 1; i <= n; i++)
            {
                ans += fabs(point[i].x - tempx);
                ans += fabs(point[i].y - tempy);
            }
            if (answer > ans)
                answer = ans, temp = 1;
            else if (answer == ans)
                temp++;
        }
        printf("%d %d\n", answer, temp);
    }
    else
    {
        sort(point + 1, point + 1 + n, cmp1);
        int ansx = point[n / 2].x, ans = 0, ansx2 = point[n / 2 + 1].x, recs = 0;
        sort(point + 1, point + 1 + n, cmp2);
        int ansy = point[n / 2].y, ansy2 = point[n / 2 + 1].y;
        for (int i = 1; i <= n; i++)
            ans += fabs(point[i].x - ansx), ans += fabs(point[i].y - ansy);
        for (int i = 1; i <= n; i++)
            if (point[i].x >= ansx && point[i].x <= ansx2 && point[i].y >= ansy && point[i].y <= ansy2)
                recs++;
        printf("%d %d\n", ans, (ansx2 - ansx + 1) * (ansy2 - ansy + 1) - recs);
    }
}