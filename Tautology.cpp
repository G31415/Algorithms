// poj3295  Tautology
// 128K 0MS
#include <algorithm>
#include <stdio.h>
#include <string.h>
#define N 110
char a[N]; // 字符串数组
int S[N];  // 数字栈
int p, q, r, s, t;
void gzz() // 从后往前进行运算，把数字进栈，遇到运算符就出栈运算后在进栈
{
    int k = 0, t1, t2;
    int l = strlen(a);
    for (int i = l - 1; i >= 0; i--)
    {
        if (a[i] == 'p')
            S[k++] = p;
        else if (a[i] == 'q')
            S[k++] = q;
        else if (a[i] == 'r')
            S[k++] = r;
        else if (a[i] == 's')
            S[k++] = s;
        else if (a[i] == 't')
            S[k++] = t;
        else if (a[i] == 'K')
        {
            t1 = S[--k];
            t2 = S[--k];
            S[k++] = (t1 && t2);
        }
        else if (a[i] == 'A')
        {
            t1 = S[--k];
            t2 = S[--k];
            S[k++] = (t1 || t2);
        }
        else if (a[i] == 'N')
        {
            t1 = S[--k];
            S[k++] = (!t1);
        }
        else if (a[i] == 'C')
        {
            t1 = S[--k];
            t2 = S[--k];
            if (t1 == 1 && t2 == 0)
                S[k++] = 0;
            else
                S[k++] = 1;
        }
        else if (a[i] == 'E')
        {
            t1 = S[--k];
            t2 = S[--k];
            if (t1 == t2)
                S[k++] = 1;
            else
                S[k++] = 0;
        }
    }
}
bool change(int i) // 赋值后运算
{
    int binary[5] = {0}; // 用于存储二进制形式的每一位
    int index = 4;       // 从最低位开始填充

    // 将整数转换为二进制形式
    while (i > 0 && index >= 0)
    {
        binary[index] = i % 2;
        i /= 2;
        index--;
    }
    p = binary[4];
    q = binary[3];
    r = binary[2];
    s = binary[1];
    t = binary[0];
    gzz();
    return S[0];
}
bool solve_all(char *a)
{
    for (int i = 0; i < 32; i++)
    {
        if (!change(i))
            return 0;
    }
    return 1;
}
int main()
{
    while (gets(a) && a[0] != '0')
    {
        if (solve_all(a))
            printf("tautology\n");
        else
            printf("not\n");
    }
    return 0;
}

/* ------------------------------------------------------------------------------------------------------ */

// 与上面差不多，用栈的方法，采用5套循环枚举

// #include <algorithm>
// #include <stdio.h>
// #include <string.h>
// #define N 110
// char a[N];
// int S[N];
// int p, q, r, s, t;
// void fore()
// {
//     int k = 0, t1, t2;
//     int l = strlen(a);
//     for (int i = l - 1; i >= 0; i--)
//     {
//         if (a[i] == 'p')
//             S[k++] = p;
//         else if (a[i] == 'q')
//             S[k++] = q;
//         else if (a[i] == 'r')
//             S[k++] = r;
//         else if (a[i] == 's')
//             S[k++] = s;
//         else if (a[i] == 't')
//             S[k++] = t;
//         else if (a[i] == 'K')
//         {
//             t1 = S[--k];
//             t2 = S[--k];
//             S[k++] = (t1 && t2);
//         }
//         else if (a[i] == 'A')
//         {
//             t1 = S[--k];
//             t2 = S[--k];
//             S[k++] = (t1 || t2);
//         }
//         else if (a[i] == 'N')
//         {
//             t1 = S[--k];
//             S[k++] = (!t1);
//         }
//         else if (a[i] == 'C')
//         {
//             t1 = S[--k];
//             t2 = S[--k];
//             if (t1 == 1 && t2 == 0)
//                 S[k++] = 0;
//             else
//                 S[k++] = 1;
//         }
//         else if (a[i] == 'E')
//         {
//             t1 = S[--k];
//             t2 = S[--k];
//             if (t1 == t2)
//                 S[k++] = 1;
//             else
//                 S[k++] = 0;
//         }
//     }
// }
// bool slove()
// {
//     for (p = 0; p <= 1; p++)
//         for (q = 0; q <= 1; q++)
//             for (r = 0; r <= 1; r++)
//                 for (s = 0; s <= 1; s++)
//                     for (t = 0; t <= 1; t++)
//                     {
//                         fore();
//                         if (!S[0])
//                             return 0;
//                     }
//     return 1;
// }
// int main()
// {
//     while (gets(a) && a[0] != '0')
//     {
//         if (slove())
//             printf("tautology\n");
//         else
//             printf("not\n");
//     }
//     return 0;
// }

/* ------------------------------------------------------------------------------------------------------ */

// 采用递归的方式计算运算符里的算式
// 超时

// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// using namespace std;

// char a[110];
// static int temp = 0;

// int change(char *a, int i)
// {
//     int binary[5] = {0}; // 用于存储二进制形式的每一位
//     int index = 4;       // 从最低位开始填充

//     // 将整数转换为二进制形式
//     while (i > 0 && index >= 0)
//     {
//         binary[index] = i % 2;
//         i /= 2;
//         index--;
//     }

//     // 将二进制值应用到字符串中
//     for (int k = 0; k < strlen(a); k++)
//     {
//         if (a[k] >= 'p' && a[k] <= 't')
//         {
//             a[k] = binary[a[k] - 'p']; // 将字符 'p' 到 't' 转换为对应的二进制值
//         }
//         if (!((a[k] >= 'p' && a[k] <= 't') || (a[i] == 'K' || a[i] == 'A' || a[i] == 'C' || a[i] == 'E' || a[i] == 'N')))
//             return 0;
//     }
//     return 1;
// }

// bool calculator(char a, int k1, int k2)
// {
//     switch (a)
//     {
//     case 'K':
//         temp += 2;
//         return k1 * k2;
//         break;
//     case 'A':
//         temp += 2;
//         return k1 + k2;
//         break;
//     case 'C':
//         temp += 2;
//         return (!k1) + k2;
//         break;
//     case 'E':
//         temp += 2;
//         return k1 == k2;
//         break;
//     case 'N':
//         temp++;
//         return !k1;
//     default:
//         break;
//     }
// }

// int Gzz(char *a, int temp)
// {
//     for (int i = temp; i < (int)strlen(a); i++)
//     {
//         if (a[i] == 'K' || a[i] == 'A' || a[i] == 'C' || a[i] == 'E')
//         {
//             temp++;
//             return calculator(a[i], Gzz(a, temp), Gzz(a, temp));
//         }
//         if (0 <= a[i] && a[i] <= 1)
//         {
//             temp++;
//             return a[i];
//         }
//         if (a[i] == 'N')
//         {
//             temp++;
//             return calculator(a[i], Gzz(a, temp), 0);
//         }
//     }
//     return 0;
// }

// int solve(char *a)
// {
//     for (int i = 0; i < 32; i++)
//     {
//         if (!change(a, i))
//             return 0;
//         if (!Gzz(a, 0))
//             return 0;
//     }
//     return 1;
// }

// int main()
// {
//     while (gets(a) && a[0] != '0')
//     {
//         if (solve(a))
//             printf("tautology\n");
//         else
//             printf("not\n");
//     }
//     return 0;
// }