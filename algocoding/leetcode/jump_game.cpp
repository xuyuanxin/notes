/*******************************************************************************
                             Jump Game(Medium)
 *******************************************************************************
 Given an array of non-negative integers, you are initially positioned at the first 
 index of the array.
 Each element in the array represents your maximum jump length at that position. 
 Determine if you are able to reach the last index.
 
 For example:
 A = [2,3,1,1,4], return true. 
 A = [3,2,1,0,4], return false.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 bool canJump(int A[], int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
  
 ******************************************************************************/

#include <iostream>
#include <string>
//#include <unordered_map> /* g++ -std=c++11 */
#include <map>
#include <vector>
using namespace std;

 class Solution {
 public:


bool canJump(int A[], int n) 
{
    int reach,i,can;

	if(1 == n) return true;

	i = 0;
	reach = 0;
	can = false;
	
	while(i < n)
	{
	    reach = max(reach,i+A[i]);

		if(reach <= i) break;

		if(reach >= n-1) 
		{
		    can = true;
			break;
		}

		i++;
	}
	
	return can;	 
}



};


void can_jump_test01()
{
    int a[5] = {2,3,1,1,4};
	int b[5] = {3,2,1,0,4};
	Solution solu;

	if(solu.canJump(a,5)) cout << "a true" << endl;
	
	if(solu.canJump(b,5)) cout << "b true" << endl;
}


int main()
{
    can_jump_test01();

	return 0;
}


