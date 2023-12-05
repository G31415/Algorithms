// poj3233 Node Power Series

// 大意: 定一个 n × n 矩阵A和一个正整数 k，求和 S = A + A 2 + A 3 + ... + A  k ,以与给定 A 相同的方式输出 S 模 m 的元素

// 运用离散数学的知识，将k转化成2进制，然后就可以将k看成2的i次方相加
// 指数则是相乘（数论中指数求模时用到）
// S = A + A 2 + A 3 + ... + A  k = (A + A 2 + A 3 + ... + A k/2)*A k/2 + (A + A 2 + A 3 + ... + A k/2)
// K奇数则是(A + A 2 + A 3 + ... + A k/2)*A k/2 + (A + A 2 + A 3 + ... + A k/2) + (A k/2)2 *A
// 设 Bn = A + A 2 + A 3 + ... + A k/2 , Cn = A k/2
// 根据二进制分解，则可以从最高位开始依次计算 Bn 和 Cn ，遇到1则Cn+1 = Cn的平方 * A ，遇到0则Cn+1 = Cn的平方，
// Bn = Bn-1 * Cn-1 + Bn-1

// 188K 141MS
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int k, n, base;

struct Node
{
    int n; // 阶数
    int m[33][33];
    void operator+=(const Node &b) // 矩阵相加运算（求模，不然会溢出）
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                m[i][j] = (m[i][j] + b.m[i][j]) % base;
    }
} a, b, c;

Node operator*(const Node &a, const Node &b) // 矩阵乘法运算（求模，不然会溢出）
{
    Node c;
    c.n = n;
    memset(c.m, 0, sizeof(c.m));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j]) % base;
    return c;
}

int main()
{
    scanf("%d%d%d", &n, &k, &base);
    a.n = b.n = c.n = n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &a.m[i][j]);
            b.m[i][j] = a.m[i][j];
            c.m[i][j] = a.m[i][j];
        }

    int i;
    for (i = 0; (1 << i) <= k; i++) // 寻找k的最高位
        ;
    for (i -= 2; i >= 0; i--)
    {
        b += c * b;
        c = c * c;
        if (((1 << i) & k) > 0) // 判断k的二进制表示中第i位是否为1
            c = c * a, b += c;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < n; j++)
            printf("%d ", b.m[i][j]);
        printf("%d\n", b.m[i][n]);
    }
    return 0;
}
