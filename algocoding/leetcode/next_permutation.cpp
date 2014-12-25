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

 
 第一步以后，a[k]以后的是一个递减序列，已经是最大的了，再折腾也没用；
 第二步，如果带上a[k]，那么lexicographical order的下一个一定是以比a[k]大的一个数
 打头的，从后面找到刚好比a[k]大的那一个，假设是a[l]； 
 第三步，将a[l]提到前面，与a[k]互换，这时候，a[k]后面的仍然是降序的。
 第四步，把a[k]后面的逆转一下，从降序到升序，这样就得到了恰好比之前序列大一号的
 序列（打头的是刚好更大的那个，后面的是升序）。  
 ******************************************************************************/

#include <iostream>
#include <string>
#include <unordered_map> /* g++ -std=c++11 */
#include <map>
#include <vector>
using namespace std;


class Solution {
	
public:
void nextPermutation(vector<int> &num) 
{
    next_permutation(num.begin(), num.end());
}

template<typename BidiIt>
bool next_permutation(BidiIt first, BidiIt last) 
{
    const auto rfirst = reverse_iterator<BidiIt>(last);
    const auto rlast = reverse_iterator<BidiIt>(first);

    auto pivot = next(rfirst);// Begin from the second last element to the first element.

    while (pivot != rlast && *pivot >= *prev(pivot))
        ++pivot;
	
    // No such elemenet found, current sequence is already the largest
    // permutation, then rearrange to the first permutation and return false.
    if (pivot == rlast) 
	{
        reverse(rfirst, rlast);
        return false;
    }
	
    // Scan from right to left, find the first element that is greater than `pivot`.
    auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
	
    swap(*change, *pivot);
    reverse(rfirst, pivot);
	
    return true;
}



};


/******************************************************************************/

void next_permutation_test01()
{
    vector<int> v;
	Solution solu;

    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(3);
    v.push_back(1);
	

	solu.nextPermutation(v);

    for (unsigned int i = 0; i < v.size( ); i++)
        cout << "v: " << v[i] << endl;	
}

int main()
{
    next_permutation_test01();
}

