 *******************************************************************************
 Given an array of integers, every element appears twice except for one. Find that 
 single one.
 
 Note:
 Your algorithm should have a linear runtime complexity. Could you implement it 
 without using extra memory?
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int singleNumber(int A[], int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/

class Solution {
public:

int singleNumber(int A[], int n) 
{
    int x = 0;
	
    for (size_t i = 0; i < n; ++i)
        x ^= A[i];
	
    return x;        
}


};
