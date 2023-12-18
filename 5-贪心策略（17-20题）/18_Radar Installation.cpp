// poj1328 Radar Installation

// 大意：x轴上方有n个点，雷达距离是d，从x轴上找点以d画圆来包含点，求用最少点

// 每个点要被包含，则可在x轴选择一段距离，将所有线段以左边排序
// 每次选取最右的点，往下如果左边小于则跳过，大于则用下一个雷达

// 2520K 750MS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define Max 0x400

using namespace std;

int n;
int d;

typedef struct
{
    double left;
    double right;
} Node;

Node s[Max];

bool cmp(Node a, Node b)
{
    return a.right < b.right;
}

int main()
{
    int i, x, y, sum, num = 1;
    double le;
    while (true)
    {
        sum = 1;
        scanf("%d %d", &n, &d);
        if (n == 0 && d == 0)
            break;
        for (i = 0; i < n; i++)
        {
            scanf("%d %d", &x, &y);
            if (y > d)
                sum = -1;                                   // 超出雷达范围，不成立
            le = sqrt(pow((float)d, 2) - pow((float)y, 2)); // 计算左右距离
            s[i].left = x - le;
            s[i].right = x + le;
        }
        if (sum == -1)
        {
            cout << "Case " << num++ << ": " << sum << endl;
            continue;
        }
        sort(s, s + n, cmp);     // s已经按照线段右侧进行了排序
        double tmp = s[0].right; // 初始设置一个雷达
        for (i = 1; i < n; i++)
        {
            if (tmp >= s[i].left)
                continue;
            else
            {
                sum++;
                tmp = s[i].right;
            }
        }
        cout << "Case " << num++ << ": " << sum << endl;
    }
}
