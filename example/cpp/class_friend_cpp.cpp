#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

/*******************************************************************************
                          Friend Functions
 *******************************************************************************
 A friend function of a class is an ordinary function except that it has access
 to the private members of objects of that class. To make a function a friend
 of a class, you must list the function declaration for the friend function in
 the class definition. The function declaration is preceded by the keyword friend. 
 The function declaration may be placed in either the private section or the public 
 section, but it will be a public function in either case, so it is clearer to list 
 it in the public section.
 
 Syntax (of a class definition with friend functions)
			class Class_Name
			{
			public:
			    friend Declaration_for_Friend_Function_1
			    friend Declaration_for_Friend_Function_2
			           .
			           .
			           .
			    Member_Function_Declarations
			private:
			    Private_Member_Declarations
			};
 A friend function is not a member function. A friend function is defined and 
 called the same way as an ordinary function. You do not use the dot operator 
 in a call to a friend function and you do not use a type qualifier in the 
 definition of a friend function.
 ******************************************************************************
                        const Parameter Modifier
 ******************************************************************************
 If you place the modifier const before the type for a call-by-reference parameter, 
 the parameter is called a constant parameter. (The heading of the function 
 definition should also have a const, so that it matches the function declaration.) 
 When you add the const, you are telling the compiler that this parameter should 
 not be changed. If you make a mistake in your definition of the function so that 
 it does change the constant parameter,then the computer will give an error message. 
 Parameters of a class type that are not changed by the function ordinarily should 
 be constant call-by-reference parameters, rather than call-by-value parameters.
 If a member function does not change the value of its calling object,then you 
 can mark the function by adding the const modifier to the function declaration. 
 If you make a mistake in your definition of the function so that it does change 
 the calling object and the function is marked with const, then the computer will 
 give an error message. The const is placed at the end of the function declaration, 
 just before the final semicolon. The heading of the function definition should also 
 have a const, so that it matches the function declaration.
 EXAMPLE
			class Sample
			{
			public:
			    Sample( );
			    friend int compare(const Sample& s1, const Sample& s2);
			    void input( );
			    void output( ) const;
			private:
			    int stuff;
			    double more_stuff;
			};

             int compare(const Sample& s1, const Sample& s2)
             {
             }
			
             void output( ) const
             {
                 
             }
			
 Use of the const modifier is an all-or-nothing proposition. You should use the 
 const modifier whenever it is appropriate for a class parameter and whenever it 
 is appropriate for a member function of the class. If you do not use const every 
 time that it is appropriate for a class, then you should never use it for that class.
 ******************************************************************************
                      Inconsistent Use of const
 ******************************************************************************
 Use of the const modifier is an all-or-nothing proposition. If you use const
 for one parameter of a particular type, then you should use it for every other
 parameter that has that type and that is not changed by the function call;
 moreover, if the type is a class type, then you should also use the const
 modifier for every member function that does not change the value of its
 calling object. The reason has to do with function calls within function calls.
 For example, consider the following definition of the function guarantee:
 void guarantee(const Money& price)
 {
  cout << "If not satisfied, we will pay you\n"
  << "double your money back.\n"
  << "That's a refund of $"
  << (2*price.get_value( )) << endl;
 }
 If you do not add the const modifier to the function declaration for the
 member function get_value, then the function guarantee will give an error
 message on most compilers. The member function get_value does not change
 the calling object price. However, when the compiler processes the function
 definition for guarantee, it will think that get_value does (or at least might)
 change the value of price. This is because when it is translating the function
 definition for guarantee, all that the compiler knows about the member
 function get_value is the function declaration for get_value; if the function
 declaration does not contain a const, which tells the compiler that the calling
 object will not be changed, then the compiler assumes that the calling object
 will be changed. Thus, if you use the modifier const with parameters of type
 Money, then you should also use const with all Money member functions that
 do not change the value of their calling object. In particular, the function
 declaration for the member function get_value should include a const.
 In Display 11.4 we have rewritten the definition of the class Money given in
 Display 11.3, but this time we have used the const modifier where appropriate. The
 definitions of the member and friend functions would be the same as they are in
 Display 11.3, except that the modifier const must be used in function headings so
 that the headings match the function declarations shown in Display 11.4.

 1 if you use the modifier const with parameters of type Money, then you should 
 also use const with all Money member functions that do not change the value of 
 their calling object. 
 ******************************************************************************/

class Money
{
public:
    friend Money add(const Money& amount1, const Money& amount2);
    friend bool equal(const Money& amount1, const Money& amount2);
	Money(long dollars, int cents);
    Money(long dollars);
    Money( );
    double get_value( ) const;
    void input(istream& ins);
    void output(ostream& outs) const;

private:
    long all_cents;
};


int digit_to_int(char c);

int main( )
{
    Money your_amount, my_amount(10, 9), our_amount;
    cout << "Enter an amount of money: ";
    your_amount.input(cin);
    cout << "Your amount is ";
    your_amount.output(cout);
    cout << endl;
    cout << "My amount is ";
    my_amount.output(cout);
    cout << endl;
	
    if (equal(your_amount, my_amount) )
        cout << "We have the same amounts.\n";
    else
        cout << "One of us is richer.\n";
	
    our_amount = add(your_amount, my_amount);
    your_amount.output(cout);
    cout << " + ";
    my_amount.output(cout);
    cout << " equals ";
    our_amount.output(cout);
    cout << endl;
    return 0;
}

Money add(const Money& amount1, const Money& amount2)
{
    Money temp;

    temp.all_cents = amount1.all_cents + amount2.all_cents;
    return temp;
}

bool equal(const Money& amount1, const Money& amount2)
{
    return (amount1.all_cents == amount2.all_cents);
}

Money::Money(long dollars, int cents)
{
    if(dollars*cents < 0) //If one is negative and one is positive
    {
        cout << "Illegal values for dollars and cents.\n";
        exit(1);
    }
    all_cents = dollars*100 + cents;
}

Money::Money(long dollars) : all_cents(dollars*100)
{
    //Body intentionally blank.
}

Money::Money( ) : all_cents(0)
{
    //Body intentionally blank.
}

double Money::get_value( ) const
{
    return (all_cents * 0.01);
}

void Money::input(istream& ins)
{
    char one_char, decimal_point,digit1, digit2; //digits for the amount of cents
    long dollars;
    int cents;
    bool negative;//set to true if input is negative.

    ins >> one_char;
    if (one_char == '-')
    {
        negative = true;
        ins >> one_char; //read '$'
    }
    else
        negative = false;

    ins >> dollars >> decimal_point >> digit1 >> digit2;
    if ( one_char != '$' || decimal_point != '.'|| !isdigit(digit1) || !isdigit(digit2) )
    {
        cout << "Error illegal form for money input\n";
        exit(1);
    }
    cents = digit_to_int(digit1)*10 + digit_to_int(digit2);
    all_cents = dollars*100 + cents;
    if (negative)
    all_cents = -all_cents;
}

//Uses cstdlib and iostream:
void Money::output(ostream& outs) const
{
    long positive_cents, dollars, cents;
    positive_cents = labs(all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if (all_cents < 0)
        outs << "-$" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;
}

int digit_to_int(char c)
{
    return (static_cast<int>(c) - static_cast<int>('0') );
}



/*
Enter an amount of money: $123.45
Your amount is $123.45
My amount is $10.09
One of us is richer.
$123.45 + $10.09 equals $133.54
*/
