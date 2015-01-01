//This is the header file sale.h.
//This is the interface for the class Sale.
//Sale is a class for simple sales.
#ifndef SALE_H
#define SALE_H

#include <iostream>
using namespace std;

namespace salesavitch
{

/*******************************************************************************
When you label a function virtual,you are telling the C++ environment¡°Wait until 
this function is used in a program, and then get the implementation corresponding 
to the calling object.¡±

If a function will have a different definition in a derived class than in the base 
class and you want it to be a virtual function, you add the keyword virtual to the 
function declaration in the base class. You do not need to add the reserved word 
virtual to the function declaration in the derived class. If a function is virtual 
in the base class, then it is automatically virtual in the derived class. (However, 
it is a good idea to label the function declaration in the derived class virtual, 
even though it is not required.)

The reserved word virtual is added to the function declaration and not to the 
function definition.

Since virtual functions are so great, why not make all member functions virtual? 
Almost the only reason for not always using virtual functions is efficiency. The 
compiler and the run-time environment need to do much more work for virtual 
functions, and so if you label more member functions virtual than you need to, 
your programs will be less efficient.
*******************************************************************************
                                 Overriding
*******************************************************************************
When a virtual function definition is changed in a derived class,programmers often 
say the function definition is overridden. In the C++ literature,a distinction is 
sometimes made between the terms redefined and overridden. Both terms refer to 
changing the definition of the function in a derived class. If the function is a 
virtual function,it's called overriding.If the function is not a virtual function, 
it's called redefining.This may seem like a silly distinction to you,the programmer, 
since you do the same thing in both cases, but the two cases are treated differently 
by the compiler.
*******************************************************************************/
class Sale
{
public:
    Sale();
    Sale(double the_price);
    virtual double bill() const;
    double savings(const Sale& other) const;
protected:
    double price;
};

bool operator < (const Sale& first, const Sale& second);

}//salesavitch

#endif // SALE_H


