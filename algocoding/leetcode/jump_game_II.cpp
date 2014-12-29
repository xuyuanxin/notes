/*******************************************************************************
                             Jump Game II(Hard)
 *******************************************************************************
 Given an array of non-negative integers, you are initially positioned at the first 
 index of the array.
 Each element in the array represents your maximum jump length at that position. 
 Your goal is to reach the last index in the minimum number of jumps.
 
 For example:
 Given array A = [2,3,1,1,4]
 
 The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 
 0 to 1, then 3 steps to the last index.)
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int jump(int A[], int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 选择能把自己送的最远的那个下一跳，贪心算法，局部最优，此时也是全局最优 
 ******************************************************************************/
	 
#include <iostream>
#include <string>
//#include <unordered_map> /* g++ -std=c++11 */
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
int jump(int A[], int n) 
{
    int i,j,step,next_hop;

	if(1 == n) return 0;

	i = 0;
	step = 1;

	while(i < n)
	{
        if(i + A[i] >= n-1) break;

		step++;
		next_hop = 1;
		
	    for(j = 2; j <= A[i]; ++j)
	    {
	        if( (A[i+j] + j) >= (A[i+next_hop] + next_hop))
	        {
	            next_hop = j;
	        }
	    }

		i += next_hop;
	}

	return step;
}



};


void jump_test01()
{
    int a01[5] = {2,3,1,1,4};
	Solution solu;

	cout << "a01 min jump(expect 2): " << solu.jump(a01,5) << endl;
	
}

void jump_test02()
{
    int a02[5] = {1,1,1,1,1};
	Solution solu;

	cout << "a02 min jump(expect 4): " << solu.jump(a02,5) << endl;	
}

void jump_test03()
{
    int a03[5] = {4,1,1,1,1};
	Solution solu;

	cout << "a03 min jump(expect 1): " << solu.jump(a03,5) << endl;	
}

void jump_test04()
{
    int a04[1] = {0};
	Solution solu;

	cout << "a04 min jump(expect 0): " << solu.jump(a04,1) << endl;	
}

int main()
{
    jump_test01();
	jump_test02();
	jump_test03();
	jump_test04();

	return 0;
}

