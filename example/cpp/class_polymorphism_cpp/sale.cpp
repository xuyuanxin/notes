//This is the implementation file: sale.cpp
//This is the implementation for the class Sale.
//The interface for the class Sale is in the header file sale.h.
#include "sale.h"

namespace salesavitch
{

Sale::Sale() : price(0)
{
}

Sale::Sale(double the_price) : price(the_price)
{
}

double Sale::bill() const
{    
	cout << "bill: I am sale(base) version" << endl;
    return price;
}

/*******************************************************************************
Since bill is declared to be a virtual function, we can later define derived classes 
of the class Sale and define their versions of the function bill, and the definitions
of the member function savings and the overloaded operator <, which we gave with 
the class Sale, will use the version of the function bill that corresponds to the 
object of the derived class.
*******************************************************************************/
double Sale::savings(const Sale& other) const
{
    return ( bill() - other.bill()  );
}

bool operator < (const Sale& first, const Sale& second)
{
    return (first.bill() < second.bill() );
}

}//salesavitch

