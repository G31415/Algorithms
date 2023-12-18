// poj2506 Tiling

// 大意：有2 *n大小的房间，有两种瓷砖，分别为1 * 2和2 * 2，求有多少种不同的方案铺满这个房间？

// 递推，设 数组a，ai 表示房间大小为2 *i时不同的方案数。
// 对于大小为n的房间，可以将其最后一块竖放，前面n - 1块共有ai - 1种方案；
// 另外可以将最后2 * 2的空间分别可以横放两块1 * 2，竖放两块1 * 2，放一块2 * 2，每种有ai - 2种方案，共有3ai - 2种方案。
// 同时会有重复的统计的方案数，如果最后一块竖放，前面ai - 1中有部分方案，最后一个也是竖放1 * 2，与后面竖放两块1 * 2部分重复计数，所以需要减去a i - 2，所以递推式如下：
// ai = 1, i⩽1
// ai = (ai−1) + 2∗(ai−2), i > 1

// 188K	0MS
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <iterator>
#define dbg(x) cout << #x << " = " << x << endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

                 using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
const int mod = 1000000007;
char a[300][100], mul[10] = {"2"}, c[100];
void init();
void ADD(char str[], char add[]);
void revser(char str[], int len);
void Mulbigint(char str1[], char str2[], char str3[]);

int main()
{
    init();
    int n;
    while (~scanf("%d", &n))
    {
        printf("%s\n", a[n]);
    }
    return 0;
}

void init()
{
    a[0][0] = a[1][0] = '1';
    a[0][1] = a[1][1] = 0;
    for (int i = 2; i <= 260; i++)
    {
        a[i][0] = '0';
        a[i][1] = 0;
        memset(c, 0, sizeof(c));
        Mulbigint(a[i - 2], mul, c);
        ADD(a[i], a[i - 1]);
        ADD(a[i], c);
    }
}

void ADD(char str[], char add[])
{
    int len1 = strlen(str), len2 = strlen(add), i;
    revser(str, len1);
    revser(add, len2);
    for (i = 0; i < len1; i++)
        str[i] -= '0';
    for (i = len1; i <= len2; i++)
        str[i] = 0;
    for (i = 0; i < len2; i++)
        add[i] -= '0';
    for (i = 0; i < len2; i++)
        str[i] += add[i];
    len1 = max(len1, len2);
    for (i = 0; i < len1; i++)
        if (str[i] > 9)
            str[i] %= 10, str[i + 1]++;
    if (str[len1] != 0)
        len1++;
    revser(str, len1);
    for (i = 0; i < len1; i++)
        str[i] += '0';
    // 将add恢复原数组
    for (i = 0; i < len2; i++)
        add[i] += '0';
    revser(add, len2);
}

void Mulbigint(char str1[], char str2[], char str3[])
{
    int i, j, len1 = strlen(str1), len2 = strlen(str2), len3 = 0;
    revser(str1, len1), revser(str2, len2);
    for (i = 0; i < len1; i++)
        str1[i] -= '0';
    for (i = 0; i < len2; i++)
        str2[i] -= '0';
    // str3可以在主函数里初始化，也可以在函数里初始化
    // 但不要使用sizeof，那样初始化会有问题
    // memset(str3, 0, 1000);
    for (i = 0; i < len2; i++)
    {
        for (j = 0; j < len1; j++)
            str3[i + j] += str1[j] * str2[i];
        len3 = max(len3, i + len1);
        for (j = 0; j < len3; j++)
            if (str3[j] > 9)
                str3[j + 1] += str3[j] / 10, str3[j] %= 10;
        while (str3[len3] > 0)
            len3++;
    }
    i = len3 - 1;
    while (str3[i] == 0 && i != 0)
        len3--, i--;
    for (i = 0; i < len3; i++)
        str3[i] += '0';
    revser(str3, len3);
    // 将原数组还原
    revser(str1, len1), revser(str2, len2);
    for (i = 0; i < len1; i++)
        str1[i] += '0';
    for (i = 0; i < len2; i++)
        str2[i] += '0';
}

void revser(char str[], int len)
{
    for (int i = 0; i < len - 1 - i; i++)
        swap(str[i], str[len - 1 - i]);
}
