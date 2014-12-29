//This is the interface for the class DiscountSale. 
//This is the file discountsale.h

#ifndef DISCOUNTSALE_H
#define DISCOUNTSALE_H
#include "sale.h"

namespace salesavitch
{

class DiscountSale : public Sale
{
public:
    DiscountSale();
    DiscountSale(double the_price, double the_discount);
    virtual double bill() const;
protected:
    double discount;
};


}//salesavitch

#endif //DISCOUNTSALE_H

