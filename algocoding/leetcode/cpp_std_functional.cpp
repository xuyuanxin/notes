#include <iostream>
#include <stdlib.h>
#include <iostream>     // std::cout
#include <functional>   // std::less
#include <algorithm>    // std::sort, std::includes

using namespace std;

/* defining member function operator() */
struct show_value   
{   
    void operator()( int i )
	{
	    cout << "value " << i << endl;
	}
}; 

int cpp_functional_base()
{
    show_value show;
	
	show(1); /* output: value 1 */
	show(2); /* output: value 2 */

	return 0;
}

/*
 less example
 Output:
 foo includes bar.
 */
int cpp_functional_less () 
{
    int foo[]={10,20,5,15,25};
    int bar[]={15,10,20};
	
    std::sort(foo, foo+5, std::less<int>());  // 5 10 15 20 25
    std::sort(bar, bar+3, std::less<int>());  //   10 15 20
    
    if (std::includes (foo, foo+5, bar, bar+3, std::less<int>()))
        std::cout << "foo includes bar.\n";
	
    return 0;
}

/* 
 bind1st example

 output:
 There are 2 elements that are equal to 10.
 There are 2 elements that are greater to 10.
 There are 4 elements that are less to 10.
*/
int cpp_functional_bind1st () 
{
    int numbers[] = {10,20,30,40,50,10,5,4};
    int cx;
	
    cx = count_if(numbers, numbers+8, bind1st(equal_to<int>(),10) );	
    cout << "There are " << cx << " elements that are equal to 10.\n";
	
    cx = count_if(numbers, numbers+8, bind1st(greater<int>(),10) );/* 10 > x */	
    cout << "There are " << cx << " elements that are greater to 10.\n";	

    cx = count_if(numbers, numbers+8, bind1st(less<int>(),10) );/* 10 < x */	
    cout << "There are " << cx << " elements that are less to 10.\n";	
	return 0;
}


int main()
{
	cpp_functional_base();
    cpp_functional_bind1st();

	return 0;
}
