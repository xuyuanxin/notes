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

When you make a function virtual, you are telling the compiler ¡°I do not know 
how this function is implemented. Wait until it is used in a program, and then 
get the implementation from the object instance.¡± The technique of waiting until 
run-time to determine the implementation of a procedure is called late binding 
or dynamic binding. Virtual functions are the way C++ provides late binding. But 
enough introduction. We need an example to make this come alive (and to teach 
you how to use virtual functions in your programs). 


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


/*******************************************************************************
Consider the following code, where SomeClass is a class with a destructor that is 
not virtual:
        SomeClass *p = new SomeClass;
        . . .
        delete p;
When delete is invoked with p, the destructor of the class SomeClass is automatically 
invoked.

suppose Derived is a derived class of the class Base and suppose the destructor
in the class Base is marked virtual. Now consider the following code:
        Base *pBase = new Derived;
        . . .
       delete pBase;
When delete is invoked with pBase, a destructor is called. Since the destructor
in the class Base was marked virtual and the object pointed to is of type Derived, 
the destructor for the class Derived is called (and it in turn calls the destructor 
for the class Base). If the destructor in the class Base had not been declared as 
virtual, then only the destructor in the class Base would be called.

when a destructor is marked as virtual, then all destructors of derived classes 
are automatically virtual(whether or not they are marked virtual).
*******************************************************************************/
