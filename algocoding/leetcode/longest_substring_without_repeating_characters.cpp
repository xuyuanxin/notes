/*******************************************************************************
            Longest Substring Without Repeating Characters (Medium)
 *******************************************************************************
 Given a string, find the length of the longest substring without repeating characters. 
 For example, the longest substring without repeating letters for "abcabcbb" is "abc", 
 which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int lengthOfLongestSubstring(string s) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 从左往右扫描，当遇到重复字母时，以上一个重复字母的 index+1，作为新的搜索起始位置，
 直到最后一个字母，复杂度是 O ( n )。
 ******************************************************************************/
#include <iostream>	 
#include <string>
using namespace std;


 class Solution {
 public:

int lengthOfLongestSubstring(string s) {
    int last[256];  /* 记录字符上次出现过的位置 */
    int start = 0; /* 记录当前子串的起始位置 */
	int max_len = 0;
	
    fill(last, last + 256, -1);

    for (int i = 0; i < s.size(); i++) {
        if (last[s[i]] >= start) {
            max_len = max(i - start, max_len);
            start = last[s[i]] + 1;
        }
        last[s[i]] = i;
    }
	
    return max((int)s.size() - start, max_len); /* 别忘了最后一次，例如"abcd" */    		 
}


};



int longest_substring_test(string s,int expect)
{
    Solution solu;

	cout << "longest len: " << solu.lengthOfLongestSubstring(s);
	cout << " (" << expect << ")" << endl;
}

int main()
{
	longest_substring_test("#$%^",4);
	longest_substring_test("abcd)(+~!a",9);

	return 0;
}

