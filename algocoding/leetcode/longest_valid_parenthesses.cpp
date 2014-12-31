/*******************************************************************************
                      Longest Valid Parentheses(Hard)
 *******************************************************************************
 Given a string containing just the characters '(' and ')', find the length of 
 the longest valid (well-formed) parentheses substring.
 
 For "(()", the longest valid parentheses substring is "()", which has length = 2.
 
 Another example is ")()())", where the longest valid parentheses substring is 
 "()()", which has length = 4.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int longestValidParentheses(string s) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/
#include <iostream>
#include <string>
#include <stack>
using namespace std;


class Solution {
public:	
int longestValidParentheses(string s) 
{
	int max_len = 0;
	
	deque<int> stack;
	
	if(s.size() <= 0)
		return 0;
	
	int last = -1;
	
	for(int i = 0; i < s.size(); i ++) {
		if(s[i] == '(') {
			stack.push_back(i);
		}else{
			if(stack.empty()) {
				last = i;
			}else{
				stack.pop_back();
				if(stack.empty()) {
					max_len = max(max_len, i-last);
				}else{
					max_len = max(max_len, i-stack.back());
				}
				 
			}
		}
	}
	
	return max_len;
}



};

int longest_valid_parentheses(string s,int expect)
{
    Solution solu;
	
    cout << s << " : " << solu.longestValidParentheses(s) << " (" << expect << ")" << endl;

	return 0;
}

int main()
{
    longest_valid_parentheses(")()())",4);	
    longest_valid_parentheses("))))",0);
	return 0;
}
