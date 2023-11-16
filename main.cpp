#include"algorithms.h"

int main(){
    int *a;
    int size = 0;
    int num;
    printf("输入数字:\n");
    a = (int *)malloc(sizeof(int));
    while (1) {
        scanf("%d", &num);
        if (num == -1)  break;
        a = (int *)realloc(a, (size + 1) * sizeof(int));
        a[size] = num;
        size++;
    }
    int*a1;
    a1 = (int *)malloc(size*sizeof(int));
    for(int i=0;i<size;i++) {a1[i]=a[i];printf("%d ",a1[i]);}
    printf("\n");
    quick_sort(a1,0,size-1);
    for (int i = 0; i < size; i++) printf("%d ", a1[i]); printf("\n");
    // int* max;
    // max=the_max_subarray(a,size);
    // printf("\n%d %d %d ",max[0],max[1],max[2]);
    // max=the_max_subarray(a1,size);
    // printf("\n%d %d %d ",max[0],max[1],max[2]);
    free(a);free(a1);
    getchar();getchar();
    return 0;
}