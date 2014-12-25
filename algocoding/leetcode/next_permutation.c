/*******************************************************************************
                           Next Permutation(Medium)
 *******************************************************************************
 Implement next permutation, which rearranges numbers into the lexicographically 
 next greater permutation of numbers.
 
 If such arrangement is not possible, it must rearrange it as the lowest possible 
 order (ie, sorted in ascending order).
 
 The replacement must be in-place, do not allocate extra memory.
 
 Here are some examples. Inputs are in the left-hand column and its corresponding 
 outputs are in the right-hand column.
 1,2,3 -> 1,3,2
 3,2,1 -> 1,2,3
 1,1,5 -> 1,5,1
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 void nextPermutation(vector<int> &num) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 1 from right to left, find the first digit (PartitionNumber) which violate the 
   increase trend.  
 2 From right to left, find the first digit which larger than PartitionNumber, 
   call it ChangeNumber	
 3 Swap the PartitionNumber and ChangeNumber;  
 4 Reverse all the digits on the right of partition index  

 µÚÒ»²½ÒÔºó£¬a[k]ÒÔºóµÄÊÇÒ»¸öµÝ¼õÐòÁÐ£¬ÒÑ¾­ÊÇ×î´óµÄÁË£¬ÔÙÕÛÌÚÒ²Ã»ÓÃ£»
 µÚ¶þ²½£¬Èç¹û´øÉÏa[k]£¬ÄÇÃ´lexicographical orderµÄÏÂÒ»¸öÒ»¶¨ÊÇÒÔ±Èa[k]´óµÄÒ»¸öÊý
 ´òÍ·µÄ£¬´ÓºóÃæÕÒµ½¸ÕºÃ±Èa[k]´óµÄÄÇÒ»¸ö£¬¼ÙÉèÊÇa[l]£» 
 µÚÈý²½£¬½«a[l]Ìáµ½Ç°Ãæ£¬Óëa[k]»¥»»£¬ÕâÊ±ºò£¬a[k]ºóÃæµÄÈÔÈ»ÊÇ½µÐòµÄ¡£
 µÚËÄ²½£¬°Ña[k]ºóÃæµÄÄæ×ªÒ»ÏÂ£¬´Ó½µÐòµ½ÉýÐò£¬ÕâÑù¾ÍµÃµ½ÁËÇ¡ºÃ±ÈÖ®Ç°ÐòÁÐ´óÒ»ºÅµÄ
 ÐòÁÐ£¨´òÍ·µÄÊÇ¸ÕºÃ¸ü´óµÄÄÇ¸ö£¬ºóÃæµÄÊÇÉýÐò£©¡£  
 ******************************************************************************/
#include <stdio.h> 
#include <stdlib.h>
 
void array_reverse(int a[],int n)
{
    int mid = 0,right,left,tmp;
	
    if(0 == n || 1 == n) return;

    if(n&0x1)
		mid = n/2;
	else
		mid = n/2-1;

	left = n-1;
	right = 0;

	for(right = 0; right<=mid; ++right,--left)
	{
	    tmp = a[left];
		a[left] = a[right];
		a[right] = tmp;
	}

	return ;	
}

void next_permutation(int a[],int n)
{
    int i,j,tmp;
	
    if(0 == n || 1 == n) return;
    
	for(i = 1; i < n; ++i) /* step 1 */
	{
		if(a[i] < a[i-1]) break;
	}

	if(i >= n) 
	{
	    array_reverse(a,n);
	    return;
	}
   
    for(j = 0; j < n; ++j) /* step 2 */
    {
        if(a[j] > a[i]) break;
   	}

    tmp = a[i];  /* step 3 */
    a[i] = a[j];
    a[j] = tmp;
   
    array_reverse(a,i); /*step 4 */
	
    return ;
}

/******************************************************************************/

void array_show(int a[],int n,char *string)
{
    int i;
	
    if(0 == n) return;

	if(NULL != string)
        printf("\r\n%s\r\n",string);
	
	for(i = n-1; i >= 0; --i)
		printf("%d ",a[i]);

	printf("\r\n");
} 


/*
   a[3] a[2] a[1] a[0]
    4     1    3    2    ---->
    4     2    1    3
*/
void next_permutation_test01()
{	
	int a[4] = {2,3,1,4}; 

	array_show(a,4,"test01 [4 1 3 2] -> [4 2 1 3]");
	next_permutation(a,4);
	array_show(a,4,NULL);
	
	return;
}


/*
   a[3] a[2] a[1] a[0]
    1     2    3    4    ---->
    1     2    4    3
*/
void next_permutation_test02()
{	
	int a[4] = {4,3,2,1}; 

	array_show(a,4,"test02 [1 2 3 4] -> [1 2 4 3]");
	next_permutation(a,4);
	array_show(a,4,NULL);
	
	return;
}

int main(int argc, char *argv[])
{
	next_permutation_test01();
	next_permutation_test02();
	
    return 0;
}
