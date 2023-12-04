#include <iostream>
#include <cstring>
using namespace std;

int maxsub(int a[], int n)
{
    int i, max = 0, b = 0;
    for (i = 0; i < n; i++)
    {
        if (b > 0)
            b += a[i];
        else
            b = a[i];
        if (b > max)
            max = b;
    }
    return max;
}

int main()
{
    int n, i, j, k, maxsubrec, maxsubarr;
    int dp[101][101], arr[101];
    while (cin >> n)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                cin >> dp[i][j];
        maxsubrec = 0;
        for (i = 0; i < n; i++)
        {
            memset(arr, 0, sizeof(arr));
            for (j = i; j < n; j++)
            {
                for (k = 0; k < n; k++)
                    arr[k] += dp[j][k];
                maxsubarr = maxsub(arr, n);
                if (maxsubarr > maxsubrec)
                    maxsubrec = maxsubarr;
            }
        }
        cout << maxsubrec << endl;
    }
}