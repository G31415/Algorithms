#include <cstdio>
#include <map>
#include <string.h>
#include <iostream>
using namespace std;
map<string, string> x;
int main(void)
{
    char a[100], b[50], c[50];
    while (gets(a) && strlen(a) != 0)
    {
        int i, j, k;
        for (i = 0; a[i] != ' '; i++)
            b[i] = a[i];
        b[i] = '\0';
        for (j = i + 1, k = 0; j <= strlen(a); k++, j++)
            c[k] = a[j];
        x[c] = b;
    }
    while (gets(a))
    {
        if (x.find(a) != x.end())
            cout << x[a] << endl;
        else
            cout << "eh" << endl;
    }
    return 0;
}
