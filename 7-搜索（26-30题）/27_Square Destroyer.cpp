
// poj1084 Square Destroyer

// 大意：给你(n+1)*n*2根由火柴组成的正方形图案（n≤5），已经帮你删除了k个火柴棒，
// 请问最少还要删除几根火柴棒，使得由火柴组成的图形没有一个完整的正方形.

// 先将每个正方形的所有边的编号预处理出来.
// 这一部分要耐心观察原图形找规律，可以发现每个正方形上下两组边是公差为1的等差数列，只要求出数列的首项即可 :
// 左右两组边是公差为2n+1的等差数列，同理求出首项即可.

// 然后问题变成最少选出多少边，使得每个正方形中至少被选出一条边这是一个经典的重复覆盖问题，可以用Dancing Links求解.
// 这里我们不适用DLX这个数据结构，直接求解.

// 估计函数 : 枚举所有未被删掉的正方形，将其所有边全部删掉，只记删除一条边。这样估计出的值一定不大于真实值，满足IDA*.
// 对估价函数的要求。其实这也是Dancing Links求解重复覆盖问题时的估价函数.
// 搜索顺序优化 : 找出最小的未被删除的正方形，依次枚举删除每条边.

// 176K 0MS
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 61;      // 网格最大是 5 * 5 的，其中最多会有 5 * (5 + 1) * 2 = 60 个正方形，所以要开到 61
int n, idx;            // n 为网格规模，idx 为正方形数量
int max_depth;         // IDA* 的 max_depth
vector<int> square[N]; // 存每个正方形边上的火柴的编号
bool used[N];          // 存每个火柴是否已经被破坏

// 新加一个左上角坐标为 (r, c)，边长为 len 的正方形
void add(int r, int c, int len)
{
    int d = n << 1 | 1; // 由于用到的 2n + 1 比较多，这里先用一个变量代替掉 2n + 1
    vector<int> &s = square[idx];
    s.clear(); // 有多组测试数据，需要上一组数据的内容清空
    for (int i = 0; i < len; i++)
    {
        s.push_back(1 + r * d + c + i);               // 上边第 i 个
        s.push_back(1 + (r + len) * d + c + i);       // 下边第 i 个
        s.push_back(1 + n + r * d + c + i * d);       // 左边第 i 个
        s.push_back(1 + n + r * d + c + i * d + len); // 右边第 i 个
    }
    idx++;
}
// 判断正方形 s 是否完整
bool check(vector<int> &s)
{
    for (int i = 0; i < (int)s.size(); i++)
        if (used[s[i]])
            return false; // 如果其中有一条边已经被破坏了，那么说明不完整
    return true;          // 如果每条边都没被破坏，说明完整
}
// 估价函数
int f()
{
    static bool backup[N];             // 由于要改动 used，需要先新建一个备份数组
    memcpy(backup, used, sizeof used); // 将 used 复制到备份数组中
    int res = 0;
    for (int i = 0; i < idx; i++) // 枚举所有正方形
        if (check(square[i]))     // 如果某个正方形是完整的，
        {
            res++; // 那么 res ++ ，并将该正方形所有的边都删去
            for (int j = 0; j < (int)square[i].size(); j++)
                used[square[i][j]] = true;
        }
    memcpy(used, backup, sizeof used); // 复制回来
    return res;
}
// IDA*
bool dfs(int depth)
{
    if (depth + f() > max_depth)
        return false;
    for (int i = 0; i < idx; i++) // 枚举所有的正方形
        if (check(square[i]))     // 如果第 i 个正方形还没被破坏
        {                         // 那么枚举该正方形的所有边编号，去掉该边并继续爆搜
            for (int j = 0; j < (int)square[i].size(); j++)
            {
                used[square[i][j]] = true;
                if (dfs(depth + 1))
                    return true;
                used[square[i][j]] = false;
            }
            return false; // 如果每条边都爆搜不成功，那么说明删掉 max_depth 个火柴无法破坏该正方形
        }
    return true; // 如果所有的正方形都被破坏了，返回 true
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), idx = 0;          // 初始化 idx
        memset(used, false, sizeof used);  // 初始化 used
        for (int len = 1; len <= n; len++) // 枚举 len, r, c，预处理每个正方形
            for (int r = 0; r + len <= n; r++)
                for (int c = 0; c + len <= n; c++)
                    add(r, c, len);
        int k;
        scanf("%d", &k);
        while (k--) // 读入所有已经被破坏的边
        {
            int x;
            scanf("%d", &x);
            used[x] = true;
        }
        max_depth = 0; // IDA*
        while (!dfs(0))
            max_depth++;
        printf("%d\n", max_depth);
    }
    return 0;
}
