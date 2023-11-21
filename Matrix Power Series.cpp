// poj3233 Matrix Power Series

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;
#define Max 30
int a[Max][Max];
int n, k, m;

int calculator(int **a, int **b)
{
}

int solve()
{
}
int main()
{

    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    printf("%d", solve());
    return 0;
}