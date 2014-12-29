//This is the header file hourlyemployee.h.
//This is the interface for the class HourlyEmployee.
#ifndef HOURLYEMPLOYEE_H
#define HOURLYEMPLOYEE_H
#include <string>
#include "employee.h"
using namespace std;
namespace employeessavitch
{

/*******************************************************************************
the derived class HourlyEmployee adds the two member variables wage_rate and hours, 
and it adds the new member functions named set_rate, get_rate, set_hours, and get_hours
*******************************************************************************/
class HourlyEmployee : public Employee
{
public:
    HourlyEmployee( );
    HourlyEmployee(string the_name, string the_ssn,double the_wage_rate, double the_hours);
    void set_rate(double new_wage_rate);
    double get_rate( ) const;
    void set_hours(double hours_worked);
	double get_hours( ) const;

/*******************************************************************************
Note that you do not give the declarations of the inherited member functions except 
for those whose definitions you want to change
********************************************************************************/
	void print_check( ) ; /*want to change*/
private:
    double wage_rate;
    double hours;
};

}//employeessavitch
#endif //HOURLYMPLOYEE_H