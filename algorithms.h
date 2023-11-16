#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max_number 1000;

//交换两个数的值
void exchange(int &a,int &b)//交换两个数的值
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}

//计算函数运行时间(部分语句)
double calculateRuntime(void (*function)())//计算函数运行时间
{
    clock_t start, end;
    double runtime;
    start = clock(); // 获取开始时钟周期数
    (*function)();   // 调用待测函数
    end = clock();   // 获取结束时钟周期数
    runtime = (double)(end - start) / CLOCKS_PER_SEC;// 计算运行时间单位为ms
    return runtime;
}

//冒泡排序
void bubble_sort(int a[], int n)//冒泡排序
{
    int i,j,temp;
    for(i=0;i<n-1;i++)//用n-1次交换保证正确性
    {
        for(j=0;j<n-1-i;j++)//大小相反则交换
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

//鸡尾酒排序，冒泡升级版
void cocktail_sort(int arr[], int n)//鸡尾酒排序，冒泡升级版
{
    int start = 0;
    int end = n - 1;
    int swapped = 1;
    while (swapped) {
        swapped = 0;//设置flag作为判断条件，减少循环次数
        for (int i = start; i < end; i++)//左到右遍历序列，比较相邻元素并交换
        {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        end--;
        if (!swapped) break;
        for (int i = end; i > start; i--)//从右到左遍历序列，比较相邻元素并交换
        {
            if (arr[i] < arr[i - 1]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        start++;
        if (!swapped) break;
    }
}

//插入排序
void insertion_sort(int a[], int n)//插入排序
{
    int i,j,key;
    for(i=1;i<n;i++)//从1往后不断插入元素
    {
        key=a[i];
        for(j=i-1;a[j]>key&&j>=0;j--)//选择插入位置
            a[j+1]=a[j];
        a[j+1]=key;
    }
}

//选择排序
void select_sort(int a[],int n)//选择排序
{
    int i,j,k,temp;
    for(i=0;i<n-1;i++)//从前往后交换
    {
        k=i;
        for(j=i+1;j<n;j++)//从i+1往后寻找最小数
            if(a[k]>a[j])//不断比较记录下值与位置
            k=j;
        temp=a[k];
        a[k]=a[i];
        a[i]=temp;
    }
}

//归并排序
void merge(int a[],int l,int temp,int r)//对两组数进行排序
{
    int i,j,k;
    int n1=temp-l+1;//要加一
    int n2=r-temp;
    int L[n1],R[n2];
    for(i=0;i<n1;i++) L[i]=a[i+l];//分成两组并复制
    for(j=0;j<n2;j++) R[j]=a[j+temp+1];
    for(i=0,j=0,k=l;i<n1&&j<n2;k++)//每次比较放入后的起始位，并将小的放入
    {
        if(L[i]>R[j])
        {
            a[k]=R[j];
            j++;
        }
        else{
            a[k]=L[i];
            i++;
        }
    }
    for(;i<n1;i++,k++)  a[k]=L[i];//当其中一个放完后，直接将另一组剩下的放入
    for(;j<n2;j++,k++)  a[k]=R[j];
        
}
void merge_sort(int a[],int l,int r)//归并排序
{
    if(l<r)
    {
        int temp=(r+l)/2;//求取中间值分组
        merge_sort(a,l,temp);//分别递归左右组
        merge_sort(a,temp+1,r);
        merge(a,l,temp,r);//到l=r结束后开始排序
    }
}

//最大子数组
int* find_max_crossing_subarray(int*a,int low,int mid,int high)//找到最大跨中间的最大子数组
{
    int* max_crossing=(int *)malloc(3*sizeof(int));
    int left_sum,right_sum;
    int temp=mid;
    int sum=0;
    for(max_crossing[1]=left_sum=0;temp>=low;--temp){
        sum+=a[temp];
        if(sum>left_sum) {
            left_sum=sum;
            max_crossing[1]=temp;
        }
        
    }
    temp=mid+1;sum=0;
    for(max_crossing[2]=right_sum=0;temp<=high;++temp){
        sum+=a[temp];
        if(sum>right_sum){
            right_sum=sum; 
            max_crossing[2]=temp;
        } 
    }
    max_crossing[0]=right_sum+left_sum;
    return max_crossing;
}
int* find_maximum_subarray(int* a,int low,int high)//找到最大子数组
{
    if(low==high){
        int* max=(int *)malloc(3*sizeof(int));
        max[0]=a[low];
        max[1]=low;
        max[2]=low;
        return max;
    }
    else {
        int mid=(high+low-1)/2;
        int* max_left;
        max_left=find_maximum_subarray(a,low,mid);
        int* max_right;
        max_right=find_maximum_subarray(a,mid+1,high);
        int* max_crossing;
        max_crossing=find_max_crossing_subarray(a,low,mid,high);
        if(max_crossing[0]>=max_left[0]&&max_crossing[0]>=max_right[0]) return max_crossing;
        if(max_left[0]>=max_right[0]&&max_left[0]>=max_crossing[0]) return max_left;
        if(max_right[0]>=max_left[0]&&max_right[0]>=max_crossing[0]) return max_right;
    }
    return NULL;
}
int* the_max_subarray(int* a,int n)//结合
{
    if(a){
        int* the_max;
        the_max=find_maximum_subarray(a,0,n-1);
        return the_max;
    }
    else return 0;
}

//堆排序
void max_heaplfy(int* a,int i,int n)//维护最大堆的步骤，使父子中最大值交换到父节点
{
    int l=2*i+1;
    int r=2*i+2;
    int large=i;
    if(l<n&&a[large]<a[l]) large=l;
    if(r<n&&a[large]<a[r]) large=r;
    if(large!=i){
        exchange(a[i],a[large]);
        max_heaplfy(a,large,n);
    }
}
void build_max_heap(int* a,int n)//对前一半有子树的结点维护
{
    int i=n/2-1;
    for(;i>=0;i--)  max_heaplfy(a,i,n);
}
void heap_sort(int* a,int n)//交换最大值到最后，依次进行
{
    build_max_heap(a,n);
    for(int i=n-1;i>0;i--){
        exchange(a[0],a[i]);
        max_heaplfy(a,0,i);
    }
}

//快速排序
int partition(int *a,int l,int r)//选出q并使其左边小右边大
{
    int i=l-1;
    for(int j=l;j<r;j++){
        if(a[j]<=a[r]){
            i++;
            exchange(a[i],a[j]);
        }
    }
    exchange(a[++i],a[r]);
    return i;
}
void quick_sort(int *a,int l,int r)//递归q的左右两边
{
    if(l<r){
        int q;
        q=partition(a,l,r);
        quick_sort(a,l,q-1);
        quick_sort(a,q+1,r);
    }
}