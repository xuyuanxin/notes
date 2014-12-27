/*******************************************************************************
                    Regular Expression Matching(Hard)
 *******************************************************************************
 Implement regular expression matching with support for '.' and '*'.
 
 '.' Matches any single character.
 '*' Matches zero or more of the preceding element.
 
 The matching should cover the entire input string (not partial).
 
 The function prototype should be:
 bool isMatch(const char *s, const char *p)
 
 Some examples:
 isMatch("aa","a") -> false
 isMatch("aa","aa")  -> true
 isMatch("aaa","aa")  -> false
 isMatch("aa", "a*")  -> true
 isMatch("aa", ".*")  -> true
 isMatch("ab", ".*")  -> true
 isMatch("aab", "c*a*b")  -> true
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 bool isMatch(const char *s, const char *p) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/
 
#include <iostream>	 
#include <string>
using namespace std;




class Solution {
public:

bool isMatch(const char *s, const char *p) 
{
    if(*p == '\0') return *s == '\0';
	   
    if(*(p + 1) != '*')
	{
        return (*s == *p || (*p == '.' && *s != '\0')) && isMatch(s+1 , p+1);
    }
	else
    {
        while(*p == *s || (*p == '.' && *s != '\0'))
		{
            if(isMatch(s , p+2)) return true; //match 1,2,3,4....n
            s++;
        }

        return isMatch(s , p+2); //match 0
    }
}



};


void is_match_test(const char *s, const char *p)
{
    Solution solu;

	cout << s << endl;
	cout << p << "  :" << solu.isMatch(s,p) << endl;

	cout << endl;
	
}


int main()
{ 
    is_match_test((char *)"*",(char *)"*");
    is_match_test((char *)"**",(char *)"*");
    is_match_test((char *)"**",(char *)"**");
    is_match_test((char *)"***",(char *)"**");

    is_match_test((char *)"aaaab",(char *)"*b");

    is_match_test((char *)"ab",(char *)"ab");	
    is_match_test((char *)"aab",(char *)"c*a*b");
    is_match_test((char *)"caab",(char *)"c*a*b");
    is_match_test((char *)"daab",(char *)"c*a*b");
    is_match_test((char *)"daab",(char *)"*a*b");
    is_match_test((char *)"aab",(char *)"*a*b");
    is_match_test((char *)"aab",(char *)"**aa");
	
    is_match_test((char *)"daab",(char *)".*");	
    is_match_test((char *)"daaa",(char *)".*a");
    is_match_test((char *)"*",(char *)"**");
	
	return 0;
}
