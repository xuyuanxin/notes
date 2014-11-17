/*LeetCode, Palindrome Partitioning
 时间复杂度 O(2^n) ，空间复杂度 O(n)*/

#include <iostream>
#include <vector>
using namespace std;

class Solution 
{
public:
    vector<vector<string>> partition(string s) 
	{
        vector<vector<string>> result;
        vector<string> path; /* 一个 partition 方案*/
        dfs(s, path, result, 0, 1);
        return result;
    }
	
/* s[0, prev-1] 之间已经处理，保证是回文串
 prev 表示 s[prev-1] 与 s[prev] 之间的空隙位置， start 同理*/ 
void dfs(string &s, vector<string>&path,vector<vector<string>> &result, size_t prev, size_t start) 
{
    if (start == s.size()) 
	{
        if (isPalindrome(s, prev, start - 1)) 
		{ // 必须使用
            path.push_back(s.substr(prev, start - prev));
            result.push_back(path);
            path.pop_back();
        }
        return;
    }
// 不断开
    dfs(s, path, result, prev, start + 1);
// 如果 [prev, start-1] 是回文，则可以断开，也可以不断开（上一行已经做了）
    if (isPalindrome(s, prev, start - 1)) 
	{
    // 断开
        path.push_back(s.substr(prev, start - prev));
        dfs(s, path, result, start, start + 1);
        path.pop_back();
    }
}

bool isPalindrome(const string &s, int start, int end) 
{
    while (start < end && s[start] == s[end]) 
	{
        ++start;
        --end;
    }
    return start >= end;
}

};

