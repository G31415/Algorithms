#include <bits/stdc++.h>
using namespace std;
const int INF = 99999999;
int main()
{
    int e[10][10], n, m, t1, t2, t3;
    cin >> n >> m; // n表示顶点个数，m表示边的条数
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                e[i][j] = 0;
            else
                e[i][j] = INF;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> t1 >> t2 >> t3;
        e[t1][t2] = t3;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (e[i][j] / 100 == 999999)
                printf("INF ");
            else
                printf("%3d ", e[i][j]);
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;

    // 核心代码
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (e[i][j] > e[i][k] + e[k][j])
                    e[i][j] = e[i][k] + e[k][j];
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (e[i][j] / 100 == 999999)
                    printf("INF ");
                else
                    printf("%3d ", e[i][j]);
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }

    return 0;
}

/*
6 10
1 5 -1
2 1 1
2 4 2
3 2 2
3 6 -8
4 1 -4
4 5 3
5 2 7
6 2 5
6 3 10
*/

/*
5 9
1 2 3
1 3 8
1 5 -4
2 4 1
2 5 7
3 2 4
4 1 2
4 3 -5
5 4 6
 */