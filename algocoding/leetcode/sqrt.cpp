/*******************************************************************************
                         Sqrt(x)(Medium) 
 *******************************************************************************
 Implement int sqrt(int x). 
 Compute and return the square root of x.
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 int sqrt(int x) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************
 二分
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /* abs */

using namespace std;

class Solution {
public:
int sqrt(int x) {
	unsigned long long begin = 0;
	unsigned long long end = (x)/2;
	unsigned long long mid;
	unsigned long long tmp;
	while(begin < end)
	{
		mid = begin + (end-begin)/2;
		tmp = mid*mid;
		if(tmp==x){
			return mid;
		}else if(tmp<x) { 
		    begin = mid+1;
		}else {
		    end = mid-1;
		}
	}
	tmp = end*end;
	if(tmp > x)
		return end-1;
	else
		return end;
}

double sqrt2(int x) {
    if (x <=0 )
        return 0;
    double pre;
    double cur = 1;
    do
    {
        pre = cur;
        cur = x / (2 * pre) + pre / 2.0;
    } while (abs(cur - pre) > 0.00001);
    return cur;
}

int sqrt3(int x) {
    int left = 1, right = x / 2;
    int last_mid; 
    if (x < 2) return x;
    while(left <= right) {
        const int mid = left + (right - left) / 2;
        if(x / mid > mid) { /* not use x > mid*mid overflow*/
            left = mid + 1;
            last_mid = mid;
        } else if(x / mid < mid) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return last_mid;
}

int sqrt5(int x) {
    int mid,left,right,value;
    if(x < 2) return x;
	left = 1; /* avoid x/0 */
	right = x/2;
	while(left <= right){
		mid = left + (right - left)/2;
		if(x/mid > mid){
			left = mid+1;
			value = mid;
		}else if(x/mid < mid){
		    right = mid - 1;
		}else{
		    return mid;
		}
	}

	return value;
}


};


/*---------------------------------------------------------------------------------*/
void sqrt_test(int x)
{
    Solution solu;

	cout << "sqrt(" << x << ") = " << solu.sqrt(x);	
	cout << " " << solu.sqrt5(x);
	
	cout << " " << solu.sqrt2(x);
	cout << endl;
	
}

int main()
{
    sqrt_test(-2);
    sqrt_test(-1);
    sqrt_test(0);
    sqrt_test(1);
    sqrt_test(2);
    sqrt_test(3);
    sqrt_test(4);
    sqrt_test(5);
    sqrt_test(6);
    sqrt_test(7);
    sqrt_test(8);
    sqrt_test(9);
    sqrt_test(10);
    sqrt_test(11);
    sqrt_test(12);

	return 0;
}
