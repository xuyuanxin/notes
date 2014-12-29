//Program to demonstrate the class BankAccount.
#include <iostream>
#include <stdlib.h>
using namespace std;

/*******************************************************************************
 Classes and Objects
 A class is a type whose variables are objects. These objects can have both member 
 variables and member functions. The syntax for a class definition is as follows.
 SYNTAX
 class Class_Name
 {
 public:
     Member_Specification_1
     Member_Specification_2
		.
		.
		.
     Member_Specification_n
 private:
     Member_Specification_n+1
     Member_Specification_n+2
		.
		.
		.
 };
 Each Member_Specification_i is either a member variable declaration or a member 
 function declaration. (Additional public and private sections are permitted.)
*******************************************************************************
 constructor
 A constructor is a member function of a class that has the same name as the class. 
 A constructor is called automatically when an object of the class is declared. 
 Constructors are used to initialize objects. A constructor must have the same 
 name as the class of which it is a member
 1 A constructor must have the same name as the class
 2 A constructor definition cannot return a value
 3 A constructor cannot be called in the same way as an ordinary member function 
   is called
 ******************************************************************************/
class BankAccount
{
public:
	BankAccount(int dollars, int cents, double rate);/*constructor*/
	BankAccount(int dollars, double rate);
	/*A constructor that can be called with no arguments is called a default constructor*/
	BankAccount( );/*default constructor*/
    void set(int dollars, int cents, double rate);
    void set(int dollars, double rate);/*The member function @set is overloaded.*/
    void update( );
    double get_balance( );
    double get_rate( );
    void output(ostream& outs);
	
/*******************************************************************************
 Private member variables (and private member functions) cannot normally be 
 referenced in the body of a function unless the function is a member function, 
	  BankAccount account; //This line is OK.
      account.balance = 12;//ILLEGAL
      account.interest_rate = 25;//ILLEGAL
*******************************************************************************/
private:
    double balance;       /*private member variables*/
    double interest_rate; /*private member variables*/
    double fraction(double percent); /* private member functions*/
};

int main( )
{

	BankAccount account1(100, 2.3);
	BankAccount account2; /*call the default constructor*/

    //BankAccount account2( );//WRONG! DO NOT DO THIS!
    
	cout << "account1 initialized as follows:\n";
	account1.output(cout);
	cout << "account2 initialized as follows:\n";
	account2.output(cout);
	
	/*An explicit call to the constructor BankAccount::BankAccount*/
	account1 = BankAccount(999, 99, 5.5);
												 	
	cout << "account1 reset to the following:\n";
	account1.output(cout);
	
    cout << "Start of Test:\n";
    account1.set(123, 99, 3.0);
    cout << "account1 initial statement:\n";
    account1.output(cout);
    account1.set(100, 5.0);  /*Calls to the overloaded member function set*/
    cout << "account1 with new setup:\n";
    account1.output(cout);
    account1.update( );
    cout << "account1 after update:\n";
    account1.output(cout);

	/*use the assignment operator with objects
	BankAccount account1, account2;
	The following is then perfectly legal 
	account2 = account1;
	The previous assignment is equivalent to the following:
	account2.balance = account1.balance;
	account2.interest_rate = account1.interest_rate;
	Moreover, this is true even though the member variables named @balance and
	@interest_rate are private members of the class BankAccount.*/	
    account2 = account1;/*use the assignment operator with objects*/
    cout << "account2:\n";
    account2.output(cout);
    return 0;
}


/*******************************************************************************
                            Calling a Constructor
 A constructor is called automatically when an object is declared, but you must 
 give the arguments for the constructor when you declare the object. A constructor 
 can also be called explicitly in order to create a new object for a class variable.
 
 Syntax (for an object declaration when you have constructors)
 Class_Name Object_Name(Arguments_for_Constructor);
 
 EXAMPLE
 BankAccount account1(100, 2.3);
 
 Syntax (for an explicit constructor call)
 Object = Constructor_Name(Arguments_For_Constructor);
 
 EXAMPLE
 account1 = BankAccount(200, 3.5);
 
 A constructor must have the same name as the class of which it is a member. 
 Thus, in the above syntax descriptions, Class_Name and Constructor_Name are 
 the same identifier.
 ******************************************************************************/
#if 0
BankAccount::BankAccount(int dollars, int cents, double rate) : balance(dollars + 0.01*cents), interest_rate(rate)
{
    if ((dollars < 0) || (cents < 0) || (rate < 0))
    {
        cout <<"Illegal values for money or interest rate.\n";
        exit(1);
    }
}
#else
BankAccount::BankAccount(int dollars, int cents, double rate)
{
    if ((dollars < 0) || (cents < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        exit(1);
    }
	
    balance = dollars + 0.01*cents;
    interest_rate = rate;
}
#endif

/*******************************************************************************
 A constructor is called automatically whenever you declare an object of the class 
 type,but it can also be called again after the object has been declared.This allows 
 you to conveniently set all the members of an object. The technical details are 
 as follows. Calling the constructor creates an anonymous object with new values. 
 An anonymous object is an object that is not named (as yet) by any variable. 
 The anonymous object can be assigned to the named object(that is, to the class 
 variable). For example, the following line of code is a call to the constructor 
 BankAccount that creates an anonymous object with a balance of $999.99 and 
 interest rate of 5.5%. This anonymous object is assigned to object account1 so 
 that it too represents an account with a balance of $999.99 and an interest rate 
 of 5.5%:
            account1 = BankAccount(999, 99, 5.5);
 As you might guess from the notation, a constructor behaves like a function 
 that returns an object of its class type.
 ******************************************************************************/
BankAccount::BankAccount(int dollars, double rate)
{
    if ((dollars < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        exit(1);
    }
	
    balance = dollars;
    interest_rate = rate;
}
/*******************************************************************************
                       Constructors with No Arguments
 When you declare an object and want the constructor with zero arguments to be 
 called, you do not include any parentheses. For example, to declare an object 
 and pass two arguments to the constructor, you might do the following:
                BankAccount account1(100, 2.3);
 However, if you want the constructor with zero arguments to be used, declare the 
 object as follows:
                BankAccount account1;
 You do not declare the object as follows:
                BankAccount account1( ); //INCORRECT DECLARATION 
                                         //it may not produce an error message
 The problem is that this syntax declares a function named account1 that returns 
 a BankAccount object and has no parameters. 
*******************************************************************************
                   Constructor Initialization Section
 Some or all of the member variables in a class can (optionally) be initialized in
 the constructor initialization section of a constructor definition. The constructor 
 initialization section goes after the parentheses that ends the parameter list 
 and before the opening brace of the function body. The initialization section 
 consists of a colon followed by a list of some or all the member variables 
 separated by commas. Each member variable is followed by its initializing value 
 in parentheses.
 ******************************************************************************/
BankAccount::BankAccount( ) : balance(0), interest_rate(0.0)
{
    //Body intentionally empty
}

void BankAccount::set(int dollars, int cents, double rate)
{
    if ((dollars < 0) || (cents < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        exit(1);
    }
    balance = dollars + 0.01*cents;
    interest_rate = rate;
}

/*******************************************************************************
 mutator functions:Member functions, such as @set that allow you to change the 
 values of the private member variables are called mutator functions.
 ******************************************************************************/
void BankAccount::set(int dollars, double rate)
{
    if ((dollars < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        exit(1);
    }
	
    balance = dollars;
    interest_rate = rate;
}


/*******************************************************************************
 Member Function Definition
 A member function is defined the same way as any other function except that the 
 Class_Name and the scope resolution operator ::  are given in the function heading.
 
 SYNTAX
 
 Returned_Type Class_Name::Function_Name(Parameter_List)
 {
     Function_Body_Statements
 }

 type qualifier:The class name that precedes the scope resolution operator is
 often called a type qualifier, because it specializes (¡°qualifies¡±) the function
 name to one particular type.
 ******************************************************************************/ 
void BankAccount::update( )
{
    balance = balance + fraction(interest_rate) *balance;
}

double BankAccount::fraction(double percent_value)
{
    return (percent_value/100.0);
}

/*******************************************************************************
 accessor functions:Member functions, such as get_month and get_day, that allow 
 you to find out the values of the private member variables are called accessor 
 functions.
 ******************************************************************************/
double BankAccount::get_balance( )
{
    return balance;
}

double BankAccount::get_rate( )
{
    return interest_rate;
}

//Uses iostream:
void BankAccount::output(ostream& outs)
{
    outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(2);
    outs << "Account balance $" << balance << endl;
    outs << "Interest rate " << interest_rate << "%" << endl;
}
/*
Start of Test:
account1 initial statement:
Account balance $123.99
Interest rate 3.00%
account1 with new setup:
Account balance $100.00
Interest rate 5.00%
account1 after update:
Account balance $105.00
Interest rate 5.00%
account2:
Account balance $105.00
Interest rate 5.00%
*/

/*******************************************************************************
 ¡ö Classes have both member variables and member functions.
 ¡ö A member (either a member variable or a member function) may be either public or private.
 ¡ö Normally, all the member variables of a class are labeled as private members.
 ¡ö A private member of a class cannot be used except within the definition of
    another member function of the same class.
 ¡ö The name of a member function for a class may be overloaded just like the name 
    of an ordinary function.
 ¡ö A class may use another class as the type for a member variable.
 ¡ö A function may have formal parameters whose types are classes. 
 ¡ö A function may return an object; that is, a class may be the type for the
    value returned by a function.  
 ******************************************************************************/




