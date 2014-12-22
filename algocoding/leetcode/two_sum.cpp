/*******************************************************************************
                             Two Sum(Medium)
 *******************************************************************************
 Given an array of integers, find two numbers such that they add up to a specific 
 target number.
 
 The function twoSum should return indices of the two numbers such that they add 
 up to the target, where index1 must be less than index2. Please note that your 
 returned answers (both index1 and index2) are not zero-based.
 
 You may assume that each input would have exactly one solution.
 
 Input: numbers={2, 7, 11, 15}, target=9
 Output: index1=1, index2=2
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 vector<int> twoSum(vector<int> &numbers, int target) {
		 
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
vector < int > twoSum(vector < int > &numbers, int target) 
{
    map<int, int> value_map; /*value:index*/
    vector<int> result;
	int i,gap;
	
    for (i = 0; i < numbers.size(); i++)
        value_map[numbers[i]] = i;

    for (i = 0; i < numbers.size(); i++) 
	{
        gap = target - numbers[i];
		
        if (value_map.find(gap) != value_map.end() && value_map[gap] > i) 
		{
            result.push_back(i+1);/* index from 1 */
            result.push_back(value_map[gap]+1);
            break;
        }
    }
	
    return result;		 
}




};


void two_sum_test01()
{
    vector<int> v;
    vector<int> ret;
	int target;
	Solution solu;

    v.push_back(49);
    v.push_back(50);
    v.push_back(51);
    v.push_back(99);
    v.push_back(101);
	
	target = 100;

	ret = solu.twoSum(v,target);

    for (unsigned int i = 0; i < ret.size( ); i++)
        cout << "index: " << ret[i]-1 << " value: " << v[ret[i]-1] << endl;	
}

int main()
{
    two_sum_test01();
}
