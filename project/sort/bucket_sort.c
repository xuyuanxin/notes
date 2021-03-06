/************************************************************************************
 http://blog.csdn.net/houapple/article/details/6480100
 
 桶排序 (Bucket sort)或所谓的箱排序，是一个排序算法，工作的原理是将阵列分到有限数量的
 桶子里。每个桶子再个别排序（有可能再使用别的排序算法或是以递回方式继续使用桶排序进行
 排序）。桶排序是鸽巢排序的一种归纳结果。当要被排序的阵列内的数值是均匀分配的时候，桶
 排序使用线性时间（Θ（n））。但桶排序并不是 比较排序，他不受到 O(n log n) 下限的影响。

 例如要对大小为[1..1000]范围内的n个整数A[1..n]排序，可以把桶设为大小为10的范围，具体而
 言，设集合B[1]存储[1..10]的整数，集合B[2]存储(10..20]的整数，……集合B[i]存储((i-1)*10, 
 i*10]的整数，i = 1,2,..100。总共有100个桶。然后对A[1..n]从头到尾扫描一遍，把每个A[i]放
 入对应的桶B[j]中。 然后再对这100个桶中每个桶里的数字排序，这时可用冒泡，选择，乃至快排，
 一般来说任何排序法都可以。最后依次输出每个桶里面的数字，且每个桶中的数字从小到大输出，
 这样就得到所有数字排好序的一个序列了。 
 
 假设有n个数字，有m个桶，如果数字是平均分布的，则每个桶里面平均有n/m个数字。如果对每个
 桶中的数字采用快速排序，那么整个算法的复杂度是O(n+m*n/m*log(n/m))=O(n+nlogn-nlogm)   
 从上式看出，当m接近n的时候，桶排序复杂度接近O(n)。当然，以上复杂度的计算是基于输入的n个
 数字是平均分布这个假设的。这个假设是很强的，实际应用中效果并没有这么好。如果所有的数字
 都落在同一个桶中，那就退化成一般的排序了。
*/

#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>   
  
extern void sort_quick(int a[], int p, int q);/* not necessary */  
  
struct barrel {   
    int node[10];   
    int count;/* the num of node */  
};   
  
void bucket_sort(int data[], int size)   
{   
    int max, min, num, pos;   
    int i, j, k;   
    struct barrel *pBarrel;   
  
    max = min = data[0];   
    for (i = 1; i < size; i++) {   
        if (data[i] > max) {   
            max = data[i];   
        } else if (data[i] < min) {   
            min = data[i];   
        }   
    }   
    num = (max - min + 1) / 10 + 1;
    pBarrel = (struct barrel*)malloc(sizeof(struct barrel) * num);
    memset(pBarrel, 0, sizeof(struct barrel) * num);   
  
    /* put data[i] into barrel which it belong to */  
    for (i = 0; i < size; i++) {   
        k = (data[i] - min + 1) / 10;/* calculate the index of data[i] in barrel */  
        (pBarrel + k)->node[(pBarrel + k)->count] = data[i];   
        (pBarrel + k)->count++;   
    }   
       
    pos = 0;   
    for (i = 0; i < num; i++) {   
        sort_quick((pBarrel+i)->node, 0, (pBarrel+i)->count);/* sort node in every barrel */  
  
        for (j = 0; j < (pBarrel+i)->count; j++) {   
            data[pos++] = (pBarrel+i)->node[j];   
        }   
    }   
    free(pBarrel);   
}   
  
int main_t()   
{   
    int data[] = {78, 17, 39, 26, 72, 94, 21, 12, 23, 91}, i;   
    int size = sizeof(data) / sizeof(int);   
    bucket_sort(data, size);   
  
    for (i = 0; i < size; i++)   
        printf("%d ", data[i]); 

	return 0;
}  

