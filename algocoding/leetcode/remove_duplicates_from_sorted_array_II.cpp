/*******************************************************************************
                 Remove Duplicates from Sorted Array(Medium)
 *******************************************************************************
 Follow up for "Remove Duplicates":
 What if duplicates are allowed at most twice?
 
 For example,
 Given sorted array A = [1,1,1,2,2,3],
 
 Your function should return length = 5, and A is now [1,1,2,2,3].
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
    int i,nums = 0,cnt = 1;

    if(0 == n) return 0;

	for(i = 1; i < n; ++i)
	{
	    if(A[nums] == A[i])
	    {
	        cnt++;

			if(cnt > 2) continue;

			nums++;
			A[nums] = A[i];
	    }
		else
		{		
		    nums++;
			A[nums] = A[i];
			
		    if(1 != cnt) cnt = 1;
		}	
	}

	return nums+1;
}

 int removeDuplicates2(int A[], int n) 
 {
	 int i,nums = 0,cnt = 1;
 
	 if(0 == n) return 0;
 
	 for(i = 1; i < n; ++i)
	 {
		 if(A[nums] == A[i])
		 {
			 cnt++;
			 if(cnt > 2) continue;
		 }
		 else
		 {		 
			 if(1 != cnt) cnt = 1;
		 }
		 
		 nums++;
		 A[nums] = A[i];
	 }
 
	 return nums+1;
 }


 };



