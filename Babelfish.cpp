// poj2503 Babelfish
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
// using namespace std;

// #define MAX 1000
// #define max 100

// char a[MAX][max];
// char b[MAX][max];

// int main()
// {
//     int i = 0;
//     char temp[max * 2 + 3];
//     while (gets(temp) && (int)strlen(temp) != 0)
//     {
//         sscanf(temp, "%s %s", a[i], b[i]); // 输入格式
//         printf("%s %s", a[i], b[i]);
//         i++;
//     }
//     return 0;
// }

/* -------------------------------------------------------------------------- */
// 3264K  218ms
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <sstream>

const int mm = 100003;

struct Node
{
    char english[12];
    char qlish[12];
};

std::vector<Node> dict(mm);
std::vector<int> hashn(mm, -1);
std::vector<int> nextn(mm);

int ELFhash(const char *key)
{
    long long h = 0;
    long long g;
    while (*key)
    {
        h = (h << 4) + *key++;
        g = h & 0xf0000000L;
        if (g)
            h ^= g >> 24;
        h &= ~g;
    }
    return (int)(h % mm);
}

void addToHash(const char *english, const char *qlish, int &n)
{
    int key = ELFhash(qlish);
    nextn[n] = hashn[key];
    hashn[key] = n;
    strncpy(dict[n].english, english, sizeof(dict[n].english));
    strncpy(dict[n].qlish, qlish, sizeof(dict[n].qlish));
    n++;
}

void buildDictionary()
{
    char ss[30];
    int n = 0;
    std::fill(hashn.begin(), hashn.end(), -1);
    while (fgets(ss, sizeof(ss), stdin))
    {
        if (sscanf(ss, "%s%s", dict[n].english, dict[n].qlish) != 2)
            break;
        else
            addToHash(dict[n].english, dict[n].qlish, n);
    }
}

const char *translate(const char *word)
{
    int i = hashn[ELFhash(word)];
    while (i != -1)
    {
        if (!strcmp(dict[i].qlish, word))
            return dict[i].english;
        i = nextn[i];
    }
    return "eh";
}

int main()
{
    buildDictionary();

    char ss[30];
    while (~scanf("%s", ss))
    {
        printf("%s\n", translate(ss));
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
// 3264K	282MS
//  #include <iostream>
//  #include <cstdio>
//  #include <cstring>
//  const int mm = 100003;
//  using namespace std;
//  struct NODE
//  {
//      char english[12];
//      char qlish[12];
//  } dict[mm];
//  int hashn[mm], nextn[mm];
//  int ELFhash(char *key) // 字符串hash
//  {
//      long long h = 0;
//      long long g;
//      while (*key)
//      {
//          h = (h << 4) + *key++;
//          g = h & 0xf0000000L;
//          if (g)
//              h ^= g >> 24;
//          h &= ~g;
//      }
//      return h % mm;
//  }
//  int main()
//  {
//      // freopen("C:\\in.txt", "r", stdin);
//      char ss[30];
//      int n = 0;
//      memset(hashn, -1, sizeof(hashn));
//      while (gets(ss))
//      {
//          if (sscanf(ss, "%s%s", dict[n].english, dict[n].qlish) != 2) // sscanf从字符串中读进与指定格式相符的数据。
//              break;
//          else
//          {
//              int key = ELFhash(dict[n].qlish); // 拉链法解决冲突，模拟链表。
//              nextn[n] = hashn[key];
//              hashn[key] = n;
//              n++;
//          }
//      }
//      while (~scanf("%s", ss))
//      {
//          int i = hashn[ELFhash(ss)];
//          while (i != -1)
//          {
//              if (!strcmp(dict[i].qlish, ss))
//                  break;
//              i = nextn[i];
//          }
//          if (i == -1)
//              printf("eh\n");
//          else
//              printf("%s\n", dict[i].english);
//      }
//      return 0;
//  }

/* -------------------------------------------------------------------------- */
// 11884K	907MS
//  #include <iostream>
//  #include <cstdio>
//  #include <cstring>
//  #include <algorithm>
//  const int maxn = 100010;
//  using namespace std;
//  struct node
//  {
//      char e[60], s[60];
//  } dic[maxn];
//  char t[60];
//  int pos;
//  int cmp(node a, node b)
//  {
//      return strcmp(a.s, b.s) < 0;
//  }
//  int binserch(char *s)
//  {
//      int l = 0, r = pos - 1;
//      while (l <= r)
//      {
//          int mid = (l + r) / 2;
//          if (strcmp(dic[mid].s, s) == 0)
//              return mid;
//          else if (strcmp(dic[mid].s, s) > 0)
//              r = mid - 1;
//          else
//              l = mid + 1;
//      }
//      return -1;
//  }
//  int main()
//  {
//      // freopen("C:\\in.txt", "r", stdin);
//      pos = 0;
//      char z;
//      while (scanf("%s%c", dic[pos].e, &z) != EOF)
//      {
//          if (z == '\n')
//          {
//              strcpy(t, dic[pos].e);
//              break;
//          }
//          scanf("%s", dic[pos++].s);
//      }
//      sort(dic, dic + pos, cmp);
//      int num = binserch(t);
//      if (num >= 0)
//          printf("%s\n", dic[num].e);
//      else
//          printf("eh\n");
//      while (scanf("%s", t) != EOF)
//      {
//          num = binserch(t);
//          if (num >= 0)
//              printf("%s\n", dic[num].e);
//          else
//              printf("eh\n");
//      }
//      return 0;
//  }

/* -------------------------------------------------------------------------- */
// 3108K 625MS
// #include <iostream>
// #include <string>
// #include <stdio.h>  //包含sscanf函数
// #include <stdlib.h> //包含bsearch函数
// using namespace std;
// struct Dic
// {
//     char engl[15];
//     char fore[15];
// } dic[100005];
// int cmp(const void *a, const void *b)
// {
//     return strcmp(((Dic *)a)->fore, ((Dic *)b)->fore);
// }
// int main()
// {
//     Dic *p, key;
//     char str[30];
//     int i = 0;
//     while (cin.getline(str, 30), strlen(str) != 0) // 为了想一个能输入字符串和回车的函数想了好久，之前用cin一直不把回车当回事
//     {
//         sscanf(str, "%s%s", dic[i].engl, dic[i].fore); // 这个函数的功能是将空格前的一段字符付给engl，后段付给fore
//         i++;
//     }
//     qsort(dic, i, sizeof(Dic), cmp);
//     while (scanf("%s", key.fore) != EOF)
//     {
//         p = (Dic *)bsearch(&key, dic, i, sizeof(Dic), cmp); // 用besearch实现二分查找的功能
//         if (p)
//             cout << p->engl << endl;
//         else
//             cout << "eh" << endl;
//     }
//     return 0;
// }

/* -------------------------------------------------------------------------- */
// 2484K 485MS
// #include "iostream"
// #include "cstdio"
// #include "cstring"
// #include "cstdlib"
// #include "algorithm"
// #define N 100005

// using namespace std;

// typedef struct node
// {
//     char english[12];
//     char foreign[12];
// } point;

// point data[N];
// int number;

// bool cmp(point x, point y)
// {
//     int k = strcmp(x.foreign, y.foreign);
//     if (k > 0)
//         return false;
//     else
//         return true;
// }

// void find(int left, int right, char *f)
// {
//     int mid = (left + right) / 2;
//     while (left <= right)
//     {
//         int k = strcmp(data[mid].foreign, f);
//         if (k > 0)
//             right = mid - 1;
//         else if (k < 0)
//             left = mid + 1;
//         else
//         {
//             printf("%s\n", data[mid].english);
//             return;
//         }
//         mid = (left + right) / 2;
//     }
//     printf("eh\n");
//     return;
// }

// int main()
// {
//     char e[12];
//     char f[12];
//     char ppp[30];
//     while (gets(ppp) && ppp[0] != '\0')
//     {
//         sscanf(ppp, "%s%s", &e, &f);
//         number++;
//         strcpy(data[number].english, e);
//         strcpy(data[number].foreign, f);
//     }
//     sort(data + 1, data + 1 + number, cmp);
//     while (gets(f))
//     {
//         find(1, number, f);
//     }
//     return 0;
// }