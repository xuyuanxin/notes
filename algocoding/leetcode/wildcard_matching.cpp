/*******************************************************************************
                     Wildcard Matching(Hard)
 *******************************************************************************
 Implement wildcard pattern matching with support for '?' and '*'.
 
 '?' Matches any single character.
 '*' Matches any sequence of characters (including the empty sequence).
 
 The matching should cover the entire input string (not partial).
 
 The function prototype should be:
 bool isMatch(const char *s, const char *p)
 
 Some examples:
 isMatch("aa","a") -> false
 isMatch("aa","aa") -> true
 isMatch("aaa","aa") -> false
 isMatch("aa", "*") -> true
 isMatch("aa", "a*") -> true
 isMatch("ab", "?*") -> true
 isMatch("aab", "c*a*b") -> false

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
	bool star = false;
	const char *str, *ptr;
	const char *pa; /* 碰到p中的'*'时，pa指向此时s遍历到的位置 */
	const char *pb; /* pb指向此时p中'*'的下一个字符 */
	
	for (str = s, ptr = p; *str != '\0'; str++, ptr++) {
		switch (*ptr) {
		case '?':
			break;
		case '*':
			star = true;
			pa = str;
			pb = ptr;
			
			while (*pb == '*') pb++; //skip continuous '*'
			
			if (*pb == '\0') return true;
			
			str = pa - 1;
			ptr = pb - 1;
			break;
		default:
			if (*str != *ptr) {
				if (!star) return false;
				pa++;
				str = pa - 1;
				ptr = pb - 1;
			} else {
				//do nothing
			}
		}
	}
	
	while (*ptr == '*') ptr++;

	return (*ptr == '\0');
};
	
bool isMatch2(const char *s, const char *p) 
{
	//? match one
	//* match 0,1,2,3..
	// aaaabc *c true
	const char* star = NULL;
	const char* rs = NULL;
	
    while(*s) 
	{
		if(*s == *p || *p == '?')  /* match */
		{ 
			s++; p++;
			continue;
		}
		
		if(*p == '*') 
		{ 
			star = p; // record star
			p++; //match from next p
			rs = s; // record the position of s , star match 0
			continue;
		} 
		if(star != NULL) { //if have star in front then backtrace
			p = star + 1; //reset the position of p 
			s = rs + 1; 
			rs ++; //star match 1,2,3,4,5....
			continue;
		}
		return false; //if not match return false
	}
	
	while(*p == '*') p++; //skip continue star
	return *p == '\0'; // successful match
}

/* timeout */
bool isMatch3(const char *s, const char *p) 
{
    if (*p == '*') {
        while (*p == '*') ++p; //skip continuous '*'
        if (*p == '\0') return true;
        while (*s != '\0' && !isMatch(s, p)) ++s;
        return *s != '\0';
    }
    else if (*p == '\0' || *s == '\0') return *p == *s;
    else if (*p == *s || *p == '?') return isMatch(++s, ++p);
    else return false;
}


};

void is_match_test(const char *s, const char *p)
{
    Solution solu;

	cout << s << "->" << p << " :" << solu.isMatch(s,p) << endl;
	cout << s << "->" << p << " :" << solu.isMatch2(s,p) << endl;
	
}

int main()
{
    is_match_test((char *)"a",(char *)"a");
    is_match_test((char *)"aa",(char *)"aa");
	
	is_match_test((char *)"",(char *)"");
	is_match_test((char *)"acb",(char *)"");

	is_match_test((char *)"acb",(char *)"?cb");
	is_match_test((char *)"acb",(char *)"a?b");	
	
	is_match_test((char *)"acb",(char *)"*ab");
	is_match_test((char *)"acb",(char *)"*ac");
	
	is_match_test((char *)"zzabzzcd",(char *)"*ab*cd");
	
	is_match_test((char *)"acb",(char *)"****");

	return 0;
}

