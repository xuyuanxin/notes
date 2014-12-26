/*******************************************************************************
                         Implement strStr(Easy)
 *******************************************************************************
 Implement strStr().

 old
 Returns a pointer to the first occurrence of needle in haystack, or null if needle 
 is not part of haystack.

 new
 Returns the index of the first occurrence of needle in haystack, or -1 if needle 
 is not part of haystack.
 
 Update (2014-11-02):
 The signature of the function had been updated to return the index instead of 
 the pointer. If you still see your function signature returns a char * or String, 
 please click the reload button xx to reset your code definition.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int strStr(char *haystack, char *needle) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 
 ******************************************************************************/
#include <iostream>     // std::cout
using namespace std;

class Solution {
public:

int strStr(char *haystack, char *needle)
{
    int h,n,first;

	if(NULL == haystack || NULL == needle) return -1;
	if('\0' == needle[0]) return 0;	
	
    h = 0;
	n = 0;
	
	while(haystack[h] != '\0')
	{		
        if(haystack[h] == needle[n])
		{
			if('\0' == needle[n+1])
			{
		        return h-n;
			}

			if(0 == n) first = h;
			
            n++;
			h++;
        }
		else
		{
			if(0 != n)
			{
			    h = first+1;
		        n = 0;
			}
			else
			{
			    h++;
			}
		}
	}

	return -1;
}




};

void strstr_test00(char *place,char *haystack, char *needle)
{
    int i;
	Solution solu;

    cout << place << endl;
	cout << "haystack: " << haystack << endl;	
	cout << "needle  : " << needle << endl;
	
	i = solu.strStr(haystack,needle);
	
	cout << "index   : " << i << endl;

	return ;
}


/*
Input:	"", ""
Expected:	0

Input:	"a", ""
Expected:	0 ( 1 think shout output -1 or size of haystack)

Input:	"mississippi", "issip"
Expected:	4
*/
int main()
{
    strstr_test00((char *)"----> test01 (expect -1)",(char *)"abcde",(char *)"f");
    strstr_test00((char *)"----> test02 (expect  4)",(char *)"abcde",(char *)"e");
    strstr_test00((char *)"----> test03 (expect  0)",(char *)"abcde",(char *)"a");
    strstr_test00((char *)"----> test04 (expect  0)",(char *)"abcde",(char *)"ab");
    strstr_test00((char *)"----> test04 (expect  0)",(char *)"abcde",(char *)"abcde");
    strstr_test00((char *)"----> test04 (expect  1)",(char *)"abcde",(char *)"bcde");	
    strstr_test00((char *)"----> test04 (expect  0)",(char *)"",(char *)"");
    strstr_test00((char *)"----> test05 (expect  4)",(char *)"mississippi",(char *)"issip");

	return 0;
}
