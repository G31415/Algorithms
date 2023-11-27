// poj3233 Matrix Power Series
//  164K	157MS
#include <cstdio>
#include <iostream>

using namespace std;

int k, n, base;

struct matrix
{
    int n;
    int m[33][33];
    void clear()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                m[i][j] = 0;
    }
    void in(int t)
    {
        n = t;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                scanf("%d", &m[i][j]);
    }
    void out()
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j < n; j++)
                printf("%d ", m[i][j]);
            printf("%d\n", m[i][n]);
        }
    }
    void operator+=(const matrix &b)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                m[i][j] = (m[i][j] + b.m[i][j]) % base;
    }
} a, b, f;

matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    c.n = n;
    c.clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j]) % base;
    return c;
}
int main()
{
    scanf("%d%d%d", &n, &k, &base);
    a.in(n);
    b = a;
    f = a;
    int i;
    for (i = 0; (1 << i) <= k; i++)
        ;
    for (i -= 2; i >= 0; i--)
    {
        f += b * f;
        b = b * b;
        if (((1 << i) & k) > 0)
            b = b * a, f += b;
    }
    f.out();
    return 0;
}

// #include <iostream>
// #include <vector>

// const int MOD = 10000; // m from the input constraints

// class Matrix
// {
// public:
//     std::vector<std::vector<int>> mat;

//     // Default constructor
//     Matrix() {}

//     Matrix(int n)
//     {
//         mat.resize(n, std::vector<int>(n, 0));
//     }

//     static Matrix identity(int n)
//     {
//         Matrix result(n);
//         for (int i = 0; i < n; ++i)
//         {
//             result.mat[i][i] = 1;
//         }
//         return result;
//     }

//     static Matrix multiply(const Matrix &a, const Matrix &b)
//     {
//         int n = a.mat.size();
//         Matrix result(n);
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = 0; j < n; ++j)
//             {
//                 result.mat[i][j] = 0; // Initialize to 0
//                 for (int k = 0; k < n; ++k)
//                 {
//                     result.mat[i][j] = (result.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
//                 }
//             }
//         }
//         return result;
//     }

//     static void precomputePowers(const Matrix &base, std::vector<Matrix> &powers, int maxPower)
//     {
//         int n = base.mat.size();
//         powers.resize(maxPower + 1);
//         powers[0] = identity(n);

//         for (int i = 1; i <= maxPower; ++i)
//         {
//             powers[i] = multiply(powers[i - 1], base);
//         }
//     }

//     static Matrix power(const std::vector<Matrix> &powers, int exp)
//     {
//         int n = powers[0].mat.size();
//         Matrix result = identity(n);

//         for (int i = 0; exp > 0; ++i, exp /= 2)
//         {
//             if (exp % 2 == 1)
//             {
//                 result = multiply(result, powers[i]);
//             }
//         }

//         return result;
//     }
// };

// int main()
// {
//     int n, k, m;
//     std::cin >> n >> k >> m;

//     Matrix A(n);
//     std::vector<Matrix> powers;

//     // Input matrix A
//     for (int i = 0; i < n; ++i)
//     {
//         for (int j = 0; j < n; ++j)
//         {
//             std::cin >> A.mat[i][j];
//         }
//     }

//     Matrix::precomputePowers(A, powers, k);

//     Matrix result = Matrix::power(powers, k);

//     // Output the elements of S modulo m
//     for (int i = 0; i < n; ++i)
//     {
//         for (int j = 0; j < n; ++j)
//         {
//             std::cout << result.mat[i][j] % MOD << " ";
//         }
//         std::cout << "\n";
//     }

//     return 0;
// }

// 556K 2032MS
// #include <iostream>
// #include <cstring>
// #include <algorithm>
// #include <cstdio>
// using namespace std;
// int n, m, k;
// struct Mar
// {
//     int aa[40][40];
// };
// Mar a, res;
// Mar cheng(Mar a, Mar b)
// {
//     Mar c;
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= n; j++)
//         {
//             c.aa[i][j] = 0;
//             for (int k = 1; k <= n; k++)
//                 c.aa[i][j] = (c.aa[i][j] + (a.aa[i][k] * b.aa[k][j]) % m) % m;
//         }
//     return c;
// }
// Mar qpow(Mar a, int k)
// {
//     Mar c;
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= n; j++)
//             if (i == j)
//                 c.aa[i][j] = 1;
//             else
//                 c.aa[i][j] = 0;
//     for (; k; k >>= 1, a = cheng(a, a))
//         if (k & 1)
//             c = cheng(c, a);
//     return c;
// }
// void work(int k)
// {
//     if (k == 1)
//     {
//         res = a;
//         return;
//     }
//     work(k / 2);
//     Mar c = qpow(a, k / 2);
//     for (int i = 1; i <= n; i++)
//         c.aa[i][i]++;
//     res = cheng(res, c);
//     if (k % 2 != 0)
//     {
//         Mar p = qpow(a, k);
//         for (int i = 1; i <= n; i++)
//             for (int j = 1; j <= n; j++)
//                 res.aa[i][j] = (res.aa[i][j] + p.aa[i][j]) % m;
//     }
// }
// int main()
// {
//     scanf("%d%d%d", &n, &k, &m);
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= n; j++)
//             scanf("%d", &a.aa[i][j]);
//     work(k);
//     for (int i = 1; i <= n; i++, printf("\n"))
//         for (int j = 1; j <= n; j++)
//             printf("%d ", res.aa[i][j]);
//     return 0;
// }

// 176K	641MS
// #include <stdio.h>
// #include <string.h>
// int b[65][65], x[65][65];
// int n, k, m;
// void mul(int a[65][65], int x[65][65])
// {
//     int i, j, k;
//     int t[65][65];
//     memset(t, 0, sizeof(t));
//     for (i = 0; i < n; i++)
//         for (j = 0; j < n; j++)
//             for (k = 0; k < n; k++)
//                 t[i][j] = (t[i][j] + a[i][k] * x[k][j]) % m;
//     memcpy(a, t, sizeof(t));
// }
// int main()
// {
//     int i, j;
//     scanf("%d%d%d", &n, &k, &m);
//     for (i = 0; i < n; i++)
//         for (j = 0; j < n; j++)
//             scanf("%d", &x[i][j]);
//     for (i = 0; i < n; i++)
//     {
//         x[i + n][i] = 1;
//         x[i + n][i + n] = 1;
//         b[i][i] = 1;
//         b[i][i + n] = 1;
//     }
//     n <<= 1;
//     for (i = 0; (1 << i) <= k; i++)
//     {
//         if (k & (1 << i))
//             mul(b, x);
//         mul(x, x);
//     }
//     n >>= 1;
//     for (i = 0; i < n; i++)
//         b[i][i] = (b[i][i] - 1 + m) % m;
//     for (i = 0; i < n; i++)
//     {
//         for (j = 0; j < n - 1; j++)
//             printf("%d ", b[i][j]);
//         printf("%d\n", b[i][n - 1]);
//     }
//     return 0;
// }
