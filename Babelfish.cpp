// poj2503 Babelfish
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
using namespace std;

#define MAX 1000
#define max 100

char a[MAX][max];
char b[MAX][max];

int main()
{
    int i = 0;
    char temp[max * 2 + 3];
    while (gets(temp) && (int)strlen(temp) != 0)
    {

        sscanf(temp, "%s %s", a[i], b[i]); // 输入格式
        printf("%s %s", a[i], b[i]);
        i++;
    }

    return 0;
}

// char c[MAX][max];

// {

//     x[c] = b;
// }
// while (gets(a))
// {
//     if (x.find(a) != x.end())
//         cout << x[a] << endl;
//     else
//         cout << "eh" << endl;
// }
// return 0;
