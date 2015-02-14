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
<<<<<<< HEAD
暴力搜索O(N^3)
=======
Violence searchO(N^3)
>>>>>>> 5db512b8979d9137e5e6f1e963ff842b59523857
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
<<<<<<< HEAD
动态规划

定义函数P[i,j]=字符串区间[i,j]是否为palindrome。
=======
dynamic programming

P[i,j]==1,  if string between i,j is palindrome
>>>>>>> 5db512b8979d9137e5e6f1e963ff842b59523857
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

<<<<<<< HEAD
/*-----------------------------------------------------------------------------------
中心扩展法
    因为回文字符串是以中心轴对称的，所以如果我们从下标 i 出发，用2个指针向 i 的两边扩
    展判断是否相等，那么只需要对0到n-1的下标都做此操作，就可以求出最长的回文子串。但需
    要注意的是，回文字符串有奇偶对称之分，即"abcba"与"abba"2种类型，因此需要在代码编写
    时都做判断。

http://blog.csdn.net/zhouworld16/article/details/16842467
-----------------------------------------------------------------------------------*/
=======
/* symmetric(N^2) */
>>>>>>> 5db512b8979d9137e5e6f1e963ff842b59523857
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
 
<<<<<<< HEAD
 
 int main()
 {	  
	 longest_palindrome_test("abbac");
	 longest_palindrome_test("ccabbaabc");

	 return 0;
 }

=======
int main()
{	  
    longest_palindrome_test("abbac");
    longest_palindrome_test("ccabbaabc");
    longest_palindrome_test("abccba");
    longest_palindrome_test("aaaaaaaaaaaa");
    longest_palindrome_test("a");

    return 0;
}
>>>>>>> 5db512b8979d9137e5e6f1e963ff842b59523857
