//This is the file: hourlyemployee.cpp
//This is the implementation for the class HourlyEmployee.
//The interface for the class HourlyEmployee is in
//the header file hourlyemployee.h.
#include <string>
#include <iostream>
#include "hourlyemployee.h"
using namespace std;

namespace employeessavitch
{

/*******************************************************************************
If a constructor definition for a derived class does not include an invocation of 
a constructor for the base class, then the default (zero-argument) version of the 
base class constructor will be invoked automatically. So, the following definition 
of the default constructor for the class HourlyEmployee (with Employee( )  omitted) 
is equivalent to the version we just discussed:
    HourlyEmployee::HourlyEmployee( ) : wage_rate(0), hours(0)
    {
         //deliberately empty
    }
The call to the base class constructor is the first action taken by a derived
class constructor.     
*******************************************************************************/
HourlyEmployee::HourlyEmployee( ) : Employee( ), wage_rate(0), hours(0)
{
    //deliberately empty
}

/*******************************************************************************
Note that you do not give definitions for the inherited member functions unless 
the definition of the member function is changed in the derived class
*******************************************************************************/

/*******************************************************************************
The portion after the colon is the initialization section of the constructor 
definition for the constructor HourlyEmployee::HourlyEmployee. The part
Employee(the_name, the_number) is an invocation of the two-argument constructor 
for the base class Employee. Note that the syntax for invoking the base class 
constructor is analogous to the syntax used to set member variables:The entry 
wage_rate(the_wage_rate) sets the value of the member variable wage_rate to 
the_wage_rate; the entry Employee(the_name, the_number) invokes the base class 
constructor Employee with the arguments the_name and the_number. Since all the 
work is done in the initialization section, the body of the constructor definition 
is empty.
*******************************************************************************/
HourlyEmployee::HourlyEmployee(string the_name, string the_number,double the_wage_rate, double the_hours)
: Employee(the_name, the_number), wage_rate(the_wage_rate), hours(the_hours)
{
    //deliberately empty
}

void HourlyEmployee::set_rate(double new_wage_rate)
{
    wage_rate = new_wage_rate;
}

double HourlyEmployee::get_rate( ) const
{
    return wage_rate;
}

void HourlyEmployee::set_hours(double hours_worked)
{
    hours = hours_worked;
}

double HourlyEmployee::get_hours( ) const
{
    return hours;
}

/*******************************************************************************
The definition of an inherited member function can be changed in the definition 
of a derived class so that it has a meaning in the derived class that is different 
from what it is in the base class. This is called redefining the inherited member 
function. For example, the member function print_check( ) is redefined in the 
definition of the derived class HourlyEmployee. 
*******************************************************************************
A member variable (or member function) that is private in a base class is not 
accessible by name in the definition of a member function for any other class, 
not even in a member function definition of a derived class. 
The member variable net_pay is a private member variable in the class Employee, 
and although a derived class like HourlyEmployee inherits the variable net_pay, 
it cannot access it directly.
*******************************************************************************/
void HourlyEmployee::print_check( )
{
    set_net_pay(hours * wage_rate);
    cout << "\n________________________________________________\n";
    cout << "Pay to the order of " << get_name( )  << endl;
    cout << "The sum of " << get_net_pay( )  << " Dollars\n";
    cout << "________________________________________________\n";
    cout << "Check Stub: NOT NEGOTIABLE\n";
    cout << "Employee Number: " << get_ssn( )  << endl;
    cout << "Hourly Employee. \nHours worked: " << hours
    << " Rate: " << wage_rate << " Pay: " << get_net_pay( )  << endl;
    cout << "_________________________________________________\n";
}

}//employeessavitch


/*******************************************************************************
Since HourlyEmployee is a derived class of the class Employee, every object of 
the class HourlyEmployee can be used anywhere an object of the class Employee 
can be used. In particular, you can use an argument of type HourlyEmployee when 
a function requires an argument of type Employee. You can assign an object of
the class HourlyEmployee to a variable of type Employee. (But be warned: You 
cannot assign a plain old Employee object to a variable of type HourlyEmployee. 
After all, an Employee is not necessarily an HourlyEmployee.) Of course, the 
same remarks apply to any base class and its derived class. You can use an 
object of a derived class anywhere that an object of its base class is allowed.
*******************************************************************************/


/*******************************************************************************
When a derived class constructor is called, these member variables need to be 
allocated memory and should be initialized. This allocation of memory for the 
inherited member variables must be done by a constructor for the base class, and 
the base class constructor is the most convenient place to initialize these 
inherited member variables. That is why you should always include a call to one 
of the base class constructors when you define a constructor for a derived class. 
If you do not include a call to a base class constructor (in the initialization 
section of the definition of a derived class constructor), then the default 
(zero-argument) constructor of the base class is called automatically. (If there 
is no default constructor for the base class, that is an error condition.)
*******************************************************************************/


/*******************************************************************************
        access to a redefined base function
********************************************************************************
Consider the base class Employee and the derived class HourlyEmployee. The function 
print_check( ) is defined in both classes. Now suppose you have an object of each 
class, as in
            Employee jane_e;
            HourlyEmployee sally_h;
Then
            jane_e.print_check( );
uses the definition of print_check given in the class Employee, and
            sally_h.print_check( );
uses the definition of print_check given in the class HourlyEmployee.
But, suppose you want to invoke the version of print_check given in the definition 
of the base class Employee with the derived class object sally_h as the calling 
object for print_check. You do that as follows:
            sally_h.Employee::print_check( );
*******************************************************************************/