//Demonstrates the performance of the virtual function bill.
#include <iostream>
#include "sale.h" //Not really needed, but safe due to ifndef.
#include "discountsale.h"
using namespace std;
using namespace salesavitch;

/*******************************************************************************
                                Polymorphism
********************************************************************************
The term polymorphism refers to the ability to associate multiple meanings to one 
function name by means of late binding.Thus, polymorphism,late binding,and virtual 
functions are really all the same topic.

When you make a function virtual, you are telling the compiler ¡°I do not know 
how this function is implemented. Wait until it is used in a program, and then 
get the implementation from the object instance.¡± The technique of waiting until 
run-time to determine the implementation of a procedure is called late binding 
or dynamic binding. Virtual functions are the way C++ provides late binding. 

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

/*******************************************************************************
Notice that the class DiscountSale requires a different definition for its version 
of the function bill. Nonetheless, when the member function savings and the 
overloaded operator < are used with an object of the class DiscountSale, they will 
use the version of the function definition for bill that was given with the class
DiscountSale.This is indeed a pretty fancy trick for C++ to pull off.Consider the
function call 
			d1.savings(d2)	// objects d1 and d2 of the class DiscountSale.
The definition of the function savings(even for an object of the class DiscountSale) 
is given in the implementation file for the base class Sale,which was compiled before 
we ever even thought of the class DiscountSale.Yet,in the function call d1.savings(d2), 
the line that calls the function bill knows enough to use the definition of the 
function bill given for the class DiscountSale.
How does this work? When you label a function virtual, you are telling the C++
environment ¡°Wait until this function is used in a program, and then get the
implementation corresponding to the calling object.¡±
*******************************************************************************/

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
                            Make Destructors Virtual
********************************************************************************
Consider the following code, where SomeClass is a class with a destructor that is 
not virtual:
            SomeClass *p = new SomeClass;
            . . .
            delete p;
When delete is invoked with p,the destructor of the class SomeClass is automatically 
invoked.

suppose Derived is a derived class of the class Base and suppose the destructor in 
the class Base is marked virtual. Now consider the following code:
            Base *pBase = new Derived;
            . . .
           delete pBase;
When delete is invoked with pBase, a destructor is called. Since the destructor in 
the class Base was marked virtual and the object pointed to is of type Derived,the 
destructor for the class Derived is called (and it in turn calls the destructor for 
the class Base).If the destructor in the class Base had not been declared as  virtual, 
then only the destructor in the class Base would be called.

when a destructor is marked as virtual, then all destructors of derived classes are 
automatically virtual(whether or not they are marked virtual).
********************************************************************************
                   why all destructors should be virtual
********************************************************************************
Suppose the class Base has a member variable pB of a pointer type,the constructor 
for the class Base creates a dynamic variable pointed to by pB,and the destructor 
for the class Base deletes the dynamic variable pointed to by pB.And suppose the 
destructor for the class Base is not marked virtual. Also suppose that the class 
Derived (which is derived from Base) has a member variable pD of a pointer type, 
the constructor for the class Derived creates a dynamic variable pointed to by pD, 
and the destructor for the class Derived deletes the dynamic variable pointed to 
by pD. Consider the following code:
            Base *pBase = new Derived;
             . . .
            delete pBase;
Since the destructor in the base class is not marked virtual, only the destructor 
for the class Base will be invoked. This will return to the freestore the memory 
for the dynamic variable pointed to by pB,but the memory for the dynamic variable 
pointed to by pD will never be returned to the freestore(until the program ends).
On the other hand, if the destructor for the base class Base were marked virtual, 
then when delete is applied to pBase, the destructor for the class Derived would 
be invoked (since the object pointed to is of type Derived).The destructor for 
the class Derive would delete the dynamic variable pointed to by pD and then 
automatically invoke the destructor for the base class Base,and that would delete 
the dynamic variable pointed to by pB. So, with the base class destructor marked 
as virtual,all the memory is returned to the freestore.To prepare for eventualities 
such as these, it is best to always mark destructors as virtual. 
*******************************************************************************/
