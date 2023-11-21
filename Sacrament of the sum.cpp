// poj2366 Sacrament of the sum
// 376K 63MS
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int *a = new int[n];
    int k = 0;
    for (int i = 0; i < n; i++)
    {

        scanf("%d", &k);
        a[i] = 10000 - k;
    }
    int m;
    scanf("%d", &m);
    int *b = new int[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &b[i]);
    }
    k = 0;
    int j = 0;
    int flag = 0;
    while (k < n && j < m)
    {
        if (a[k] < b[j])
            j++;
        else if (a[k] > b[j])
            k++;
        else
        {
            flag = 1;
            break;
        }
    }
    if ((k == n) && (j < m - 1) && (!flag))
    {
        for (; j < m; j++)
        {
            if (a[n - 1] == b[j])
            {
                flag = 1;
                break;
            }
        }
    }
    else if ((k < n - 1) && (j == m) && (!flag))
    {
        for (; k < n; k++)
        {
            if (a[k] == b[m - 1])
            {
                flag = 1;
                break;
            }
        }
    }
    if (flag)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}