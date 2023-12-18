// poj1636 Prison rearrangement

// 有的犯人如果要换的话需要一次性调换好几个，才能使他们不冲突。
// 这样想的话。就是求连通分量，每个连通分量就是一种调换，
// 就是说，这个连通分量中有第一个监狱X人，第二个监狱Y人，我们要做的就是交换X，Y。
// f[i][j] 表示从第二个监狱向第一个监狱调换了j人，从第二个监狱向第一个监狱调换了i人这个状态是否能到达。
// 答案就是f[max][max];
// f[i][j] = f[i][j] || f[i - wx[i]][i - wy[i]];

// 588K 79MS
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define maxn 500
#define Clear(a, b) memset(a, b, sizeof(a))

vector<int> links[maxn];

bool dp[maxn][maxn];
int vis[maxn], mark[maxn], sum[2], wy[maxn], wx[maxn];

int dfs(int k)
{
    int m, i;
    if (vis[k])
        return 0;
    vis[k] = 1;
    sum[mark[k]]++;
    m = links[k].size();
    for (i = 0; i < m; i++)
    {
        dfs(links[k][i]);
    }
    return 0;
}

int work()
{
    int m, r, i, j, k, a, b, n, e, len = 0;

    Clear(vis, 0);
    Clear(mark, 0);
    Clear(dp, 0);
    Clear(wx, 0);
    Clear(wy, 0);
    // freopen("test.txt", "r", stdin);
    scanf("%d%d", &m, &e);

    for (i = 1; i <= m * 2; i++)
        links[i].clear();

    for (i = 1; i <= m; i++)
    {
        mark[i] = 0;
        mark[i + m] = 1;
    }
    for (i = 1; i <= e; i++)
    {
        scanf("%d%d", &a, &b);
        b += m;
        links[a].push_back(b);
        links[b].push_back(a);
    }
    for (i = 1; i <= m * 2; i++)
    {
        Clear(sum, 0);
        dfs(i);
        if (sum[0] > 0 || sum[1] > 0)
        {
            wx[++len] = sum[0];
            wy[len] = sum[1];
        }
    }
    n = m / 2;
    dp[0][0] = 1;
    // for(i = 1;i <= len;i++) printf("%d %d\n",wx[i],wy[i]);
    for (i = 1; i <= len; i++)
        for (j = n; j >= wx[i]; j--)
            for (k = n; k >= wy[i]; k--)
                dp[j][k] = dp[j][k] || dp[j - wx[i]][k - wy[i]];
    i = n;

    while (dp[i][i] != 1)
        i--;
    printf("%d\n", i);
    return 0;
}

int main()
{
    int t;

    scanf("%d", &t);
    while (t--)
        work();
    return 0;
}