//Demonstrates the performance of the virtual function bill.
#include <iostream>
#include "sale.h" //Not really needed, but safe due to ifndef.
#include "discountsale.h"
using namespace std;
using namespace salesavitch;

/*******************************************************************************
Polymorphism
The term polymorphism refers to the ability to associate multiple meanings to one 
function name by means of late binding. Thus, polymorphism, late binding, and virtual 
functions are really all the same topic.


In the C++ literature,a distinction is sometimes made between the terms redefined 
and overridden. Both terms refer to changing the definition of the function in a
derived class. If the function is a virtual function, it¡¯s called overriding. If
the function is not a virtual function, it¡¯s called redefining. This may seem like 
a silly distinction to you, the programmer, since you do the same thing in both 
cases, but the two cases are treated differently by the compiler.

*******************************************************************************/

int main()
{
    Sale simple(10.00);//One item at $10.00.
    DiscountSale discount(11.00, 10);//One item at $11.00 with a 10% discount.

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    if (discount < simple)
    {
        cout << "Discounted item is cheaper.\n";
        cout << "Savings is $" << simple.savings(discount)  << endl;
    }
    else
        cout << "Discounted item is not cheaper.\n";

    return 0;
}

