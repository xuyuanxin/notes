/*******************************************************************************
                 Remove Duplicates from Sorted Array(Easy)
 *******************************************************************************
 Given a sorted array, remove the duplicates in place such that each element 
 appear only once and return the new length.
 Do not allocate extra space for another array, you must do this in place with 
 constant memory.
 
 For example,
 Given input array A = [1,1,2],
 
 Your function should return length = 2, and A is now [1,2].
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int removeDuplicates(int A[], int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 ******************************************************************************/

 class Solution {
 public:

int removeDuplicates(int A[], int n) 
{
    int i,nums=0;

    if(0 == n)
 	    return 0;

     for(i = 1; i < n; i++)
     {
         if(A[nums] != A[i])
         {
             nums++;
		     A[nums] = A[i];
         }
     }

     return nums+1;
}


};


