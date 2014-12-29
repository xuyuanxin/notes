//This is the file discountsale.cpp

#include "discountsale.h"

namespace salesavitch
{

DiscountSale::DiscountSale() : Sale(), discount(0)
{
}

DiscountSale::DiscountSale(double the_price, double the_discount)
: Sale(the_price), discount(the_discount)
{
}

double DiscountSale::bill() const
{
    double fraction = discount/100;
    return (1 - fraction)*price;
}


}//salesavitch

