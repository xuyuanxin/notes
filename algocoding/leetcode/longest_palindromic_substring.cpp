/*******************************************************************************
                     Longest Palindromic Substring(Medium)
 *******************************************************************************
 Given a string S, find the longest palindromic substring in S. You may assume 
 that the maximum length of S is 1000, and there exists one unique longest 
 palindromic substring.

 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 string longestPalindrome(string s) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/
#include <iostream>	 
#include <string>
#include <algorithm>  /* reverse */
using namespace std;

 class Solution {
 public:

string longestPalindrome(string s) 
{
    int maxPalinLength = 0;  
    string longestPalindrome = NULL;  
    int length = s.length();

	if(1 == length || 0 == length) return s;

    for (int i = 0; i < length; i++) 
	{	
        for (int j = i + 1; j < length; j++) 
		{	
            int len = j - i;  
            string curr = s.substr(i, j + 1);
			
            if (isPalindrome(curr)) 
			{  
                if (len > maxPalinLength) 
				{  
                    longestPalindrome = curr;  
                    maxPalinLength = len;  
                }  
            }  
        }  
    }  

    return longestPalindrome;  
}

bool isPalindrome(string s) 
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);

    auto left = s.begin(), right = prev(s.end());

    while (left < right) 
    {
        if (!::isalnum(*left)) ++left;
        else if (!::isalnum(*right)) --right;
        else if (*left != *right) return false;
        else{ left++, right--; }
    }
    return true;		 
}


};


/******************************************************************************/ 

void longest_palindrome_test(string s)
{
	Solution solu;
	 
	cout << s << " (1): " << solu.longestPalindrome(s) << endl;
}
 
 
 int main()
 {	  
	 longest_palindrome_test("abbac");

	 return 0;
 }
