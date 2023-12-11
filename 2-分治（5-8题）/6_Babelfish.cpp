// poj2503 Babelfish

// 大意: 字典搜索

// 将外语和英语建立成字典，再以外语字符串建立Hash表，储存在字典的位置，Next作为索引解决Key值相同的情况

// 3264K  218ms
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <sstream>

#define Max 0x186a0

std::vector<int> Hash(Max, -1);
std::vector<int> Next(Max);

struct Node
{
    char eng_word[12];
    char forn_word[12];
} dict[Max];

// 字符串hash算法ELFhas
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
    return (int)(h % Max);
}

// 建立哈希表
void addToHash(const char *eng_word, const char *forn_word, int &n)
{
    int key = ELFhash(forn_word);
    Next[n] = Hash[key]; // 如果key重复，将上一个n加入Next作为上一个值的索引
    Hash[key] = n;        // 记录forn_word所对应的字典排序
    strncpy(dict[n].eng_word, eng_word, sizeof(dict[n].eng_word));
    strncpy(dict[n].forn_word, forn_word, sizeof(dict[n].forn_word));
    n++;
}

// 建立字典
void buildDictionary()
{
    char ss[30];
    int n = 0;
    std::fill(Hash.begin(), Hash.end(), -1);
    while (fgets(ss, sizeof(ss), stdin))
    {
        if (sscanf(ss, "%s%s", dict[n].eng_word, dict[n].forn_word) != 2)
            break;
        else
            addToHash(dict[n].eng_word, dict[n].forn_word, n);
    }
}

// 翻译word
const char *translate(const char *word)
{
    int i = Hash[ELFhash(word)];
    while (i != -1)
    {
        if (!strcmp(dict[i].forn_word, word)) // 相同则返回值
            return dict[i].eng_word;
        i = Next[i]; // 不相同则利用索引查下一个单词
    }
    return "eh";
}

int main()
{
    buildDictionary();
    char ss[30];
    while (~scanf("%s", ss))
        printf("%s\n", translate(ss));
    return 0;
}
