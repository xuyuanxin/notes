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
#include <cstring>    /* memset */
#include <algorithm>  /* reverse */
using namespace std;

class Solution {
public:

#if 0
/*
Violence searchO(N^3)
*/
string longestPalindrome_v1(string s) 
{
    int maxlen = 0;  
    string maxstr = NULL;  
    int length = s.length();

	if(1 == length || 0 == length) {
		return s;
	}
    for (int i = 0; i < length; i++)  {	
        for (int j = i + 1; j < length; j++) {	
            int len = j - i;  
            string curr = s.substr(i, j + 1);
            if (isPalindrome(curr) && (len > maxlen) ) {  
                    maxstr = curr;  
                    maxlen = len;  
            }  
        }  
    }  
    return maxstr;  
}

bool isPalindrome(string s) 
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);

    auto left = s.begin(), right = prev(s.end());

    while (left < right) {
        if (!::isalnum(*left)) {
			++left;
        } else if (!::isalnum(*right)) {
            --right;
        } else if (*left != *right) {
            return false;
        } else { 
            left++, right--; 
		}
    }
    return true;		 
}
#endif

/*-----------------------------------------------------------------------------------
dynamic programming

P[i,j]==1,  if string between i,j is palindrome
1 if(i == j) 
      P[i,j]==1
2 if(j==i+1) 
      if(S[i] ==S[j]) P[i,j]==1
3 if(j>i+1)
      if(S[i] == S[j] && P[i+1][j-1]) P[i,j]==1

http://codingtmd.azurewebsites.net/leetcode-longest-palindromic-substring-%E8%A7%A3%E9%A2%98%E6%8A%A5%E5%91%8A/
-----------------------------------------------------------------------------------*/
string longestPalindrome_v2(string s) 
{  
    int len = s.size();  
    int P[len][len];  
    memset(P, 0, len*len*sizeof(int));  
    int maxL=0, start=0, end=0;  
    for(int i =0; i< s.size(); i++) {  
        for(int j =0; j<i; j++) {  
            P[j][i] = (s[j] == s[i] && (i-j<2 || P[j+1][i-1]));  
            if(P[j][i] && maxL < (i-j+1)) {  
                maxL = i-j+1;  
                start = j;  
                end = i;  
            }  
        }  
        //P[i][i] =1;
    }  
    return s.substr(start, end-start +1);  
}

/* symmetric(N^2) */
string longestPalindrome_v3(string s) 
{
    size_t n = s.length();
    int pos = 0;
    int maxlen = 1,len = 0,beg = 0;;
    for (int i = 0; i < n; ++i) {
        len = palindrome_len(s,i,pos);
		if(len > maxlen) {
			maxlen = len;
			beg = pos;
		}
    }
    return s.substr(beg,maxlen);
}

/*-----------------------------------------------------------------------------------
  i==2      
  |
cabad        return 3 index==1
   
  i==2      
  |
cabbad       return 4 index==1

  i==2      
  |
abcd         return 1 index==2
-----------------------------------------------------------------------------------*/
int palindrome_len(const string &str,int i,int &index)
{
    size_t n = str.length();
    int len1 = 0,len2 = 0,maxlen = 0,left = 0,right = 0;

	left  = i-1; right = i+1; /* case: aba */
    while (left >= 0 && right < n && str[left] == str[right]) {
		--left;
        ++right;
    }
    len1 = (right-1) - (left+1) + 1;
	index = left+1;

	left  = i; right = i+1; /* case: abba */
    while (left >= 0 && right < n && str[left] == str[right]) {
		--left;
        ++right;
    }
    len2 = (right-1) - (left+1) + 1;

	if(len1 > len2) {
		maxlen = len1;
	} else {
	    maxlen = len2;
		index  = left+1;
	}
	
    return maxlen;
}


};


/*---------------------------------------------------------------------------------*/ 
void longest_palindrome_test(string s)
{
	Solution solu;

	cout << "string: " << s << endl;
	cout << "(V2)  : " << solu.longestPalindrome_v2(s) << endl;
	cout << "(V3)  : " << solu.longestPalindrome_v3(s) << endl;
}
 
int main()
{	  
    longest_palindrome_test("abbac");
    longest_palindrome_test("ccabbaabc");
    longest_palindrome_test("abccba");
    longest_palindrome_test("aaaaaaaaaaaa");
    longest_palindrome_test("a");

    return 0;
}
