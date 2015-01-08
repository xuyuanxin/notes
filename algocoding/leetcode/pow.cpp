/*******************************************************************************
                         Pow(x, n)(Medium) 
 *******************************************************************************
 Implement pow(x, n).
 *******************************************************************************
                             interface
 *******************************************************************************
 class Solution {
 public:
	 double pow(double x, int n) {
		 
	 }
 };
 *******************************************************************************
                              algo
 *******************************************************************************

 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> /* abs */

using namespace std;


class Solution {
public:
double pow(double x, int n) {
    if (n < 0) {
		return 1.0 / power(x, -n);
    }else{
        return power(x, n);  
    }
}

/* n>=0 */
double power(double x, int n) {
    if (n == 0) return 1;
    double v = power(x, n / 2);
    if (n % 2 == 0) {
		return v * v;
    }else{
		return v * v * x;
    }
}


};

/*---------------------------------------------------------------------------------*/
void power_test(double x, int n)
{
    Solution solu;

	cout << x << "^" << n << " = " << solu.pow(x,n) << endl;	
}

int main()
{
    power_test(2,5);	
    power_test(-2,-2);

	return 0;
}
