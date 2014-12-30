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
 the derived class HourlyEmployee adds the two member variables wage_rate and 
 hours,and it adds the new member functions named set_rate, get_rate, set_hours, 
 and get_hours
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
 Note that you do not give the declarations of the inherited member functions 
 except for those whose definitions you want to change.A derived class inherits 
 all the member functions (and member variables as well) that belong to the base 
 class. However, if a derived class requires a different implementation for an 
 inherited member function, the function may be redefined in the derived class. 
 When a member function is redefined, you must list its declaration in the 
 definition of the derived class even though the declaration is the same as in 
 the base class. If you do not wish to redefine a member function that is inherited 
 from the base class, then it is not listed in the definition of the derived class.
 *******************************************************************************
                       redefining versus overloading
 *******************************************************************************
 A function's signature is the function's name with the sequence of types in the 
 parameter list, not including the const keyword and not including the ampersand(&). 
 When you overload a function name, the two definitions of the function name must 
 have different signatures using this definition of signature. If a function has 
 the same name in a derived class as in the base class but has a different signature, 
 that is overloading, not redefinition.
 *******************************************************************************
                   Access to a Redefined Base Function
 *******************************************************************************
 Suppose you redefine a function so that it has a different definition in the
 derived class from what it had in the base class. The definition that was given
 in the base class is not completely lost to the derived class objects.if you 
 want to invoke the version of the function given in the base class with an object 
 in the derived class,you can use the scope resolution operator with the name of 
 the base class.
 The function print_check() is defined in both classes. Now suppose you have an 
 object of each class, as in
             Employee jane_e;
             HourlyEmployee sally_h;
 Then
             jane_e.print_check( );
 uses the definition of print_check given in the class Employee, and
             sally_h.print_check( ); 
 uses the definition of print_check given in the class HourlyEmployee.But,suppose 
 you want to invoke the version of print_check given in the definition of the base 
 class Employee with the derived class object sally_h as the calling object for 
 print_check. You do that as follows:
             sally_h.Employee::print_check( );
 Of course, you are unlikely to want to use the version of print_check given in 
 the particular class Employee, but with other classes and other functions, you 
 may occasionally want to use a function definition from a base class with a 
 derived class object.             
********************************************************************************/
	void print_check( ) ; /*want to change*/
private:
    double wage_rate;
    double hours;
};

}//employeessavitch
#endif //HOURLYMPLOYEE_H