/*******************************************************************************
                           Simplify Path(Medium)
 *******************************************************************************
 Given an absolute path for a file (Unix-style), simplify it.
 
 For example,
 path = "/home/", => "/home"
 path = "/a/./b/../../c/", => "/c"
 
 Corner Cases:
 Did you consider the case where path = "/../"?
 In this case, you should return "/".
 Another corner case is the path might contain multiple slashes '/' together, 
 such as "/home//foo/".In this case, you should ignore redundant slashes and 
 return "/home/foo".
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 string simplifyPath(string path) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
string simplifyPath(string path) 
{
	vector<string> dirs;
	
	for (auto i = path.begin(); i != path.end();) 
	{
	    ++i;
	    auto j = find(i, path.end(), '/');
	    auto dir = string(i, j);
		
	    if (!dir.empty() && dir != ".") {// 当有连续 '///' 时， dir 为空
	        if (dir == "..") {
	            if (!dirs.empty())
	                dirs.pop_back();
	        } else {
	            dirs.push_back(dir);
	        }	
	    }
		
	    i = j;
	}
	 
	string simple_path;
	
	if (dirs.empty()) {
	    simple_path = "/";
	} else {
        for (auto dir : dirs){
			simple_path += ('/' + dir);
        }	
    }
	
    return simple_path;
}


};

/******************************************************************************/

int simplity_path_test(string path,string expect)
{
    Solution solu;
	
    cout << path << " -> " << solu.simplifyPath(path);
	cout << " (" << expect << ")" << endl;
	return 0;
}

int main()
{
    simplity_path_test("","");
    simplity_path_test("///","/");	
    simplity_path_test("/../","/");	
    simplity_path_test("/","/");
	simplity_path_test("/home/","/home");
    simplity_path_test("/home//foo/","/home/foo");
    simplity_path_test("/a/./b/../../c/","/c");

	return 0;
}

