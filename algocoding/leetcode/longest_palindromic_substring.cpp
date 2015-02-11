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
暴力搜索O(N^3)
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
动态规划

定义函数P[i,j]=字符串区间[i,j]是否为palindrome。
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

/*-----------------------------------------------------------------------------------
中心扩展法
    因为回文字符串是以中心轴对称的，所以如果我们从下标 i 出发，用2个指针向 i 的两边扩
    展判断是否相等，那么只需要对0到n-1的下标都做此操作，就可以求出最长的回文子串。但需
    要注意的是，回文字符串有奇偶对称之分，即"abcba"与"abba"2种类型，因此需要在代码编写
    时都做判断。

http://blog.csdn.net/zhouworld16/article/details/16842467
-----------------------------------------------------------------------------------*/
string longestPalindrome_v3(string s) 
{
    size_t n = s.length();
    int startPos = 0;
    int max = 1;
    for (int i = 0; i < n; ++i) {
        int oddLen = 0, evenLen = 0, curLen;
        oddLen = Palindromic(s,i,i);
        
        if (i + 1 < n) {
            evenLen = Palindromic(s,i,i+1);
        }
        
        curLen = oddLen > evenLen? oddLen : evenLen;
        
        if (curLen > max) {
            max = curLen;
            if (max & 0x1) {
              startPos = i - max / 2;
            } else  {
              startPos = i - (max - 1) / 2;
            }
        }
    }
    
    return s.substr(startPos,max);
}
    
int Palindromic(const string &str, int i, int j)
{
    size_t n = str.length();
    int curLen = 0;

    while (i >= 0 && j < n && str[i] == str[j]) {
		--i;
        ++j;
    }
    curLen = (j-1) - (i+1) + 1;
    return curLen;
}



};




/*---------------------------------------------------------------------------------*/ 

void longest_palindrome_test(string s)
{
	Solution solu;
	 
	cout << s << " (V2): " << solu.longestPalindrome_v2(s) << endl;
}
 
 
 int main()
 {	  
	 longest_palindrome_test("abbac");
	 longest_palindrome_test("ccabbaabc");

	 return 0;
 }

