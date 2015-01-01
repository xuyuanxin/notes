#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;


/************************************************************************************
                         Operator Overloading
 ************************************************************************************
 A (binary) operator, such as +, ? , /, %, and so forth, is simply a function that is 
 called using a different syntax for listing its arguments.With an operator,the arguments 
 are listed before and after the operator; with a function, the arguments are listed 
 in parentheses after the function name. An operator definition is written similarly 
 to a function definition, except that the operator definition includes the reserved 
 word operator before the operator name. The predefined operators, such as + and so 
 forth, can be overloaded by giving them a new definition for a class type.
 ************************************************************************************
                       Rules on Overloading Operators
 ************************************************************************************
 1 When overloading an operator, at least one argument of the resulting overloaded 
   operator must be of a class type.
 2 An overloaded operator can be, but does not have to be, a friend of a class; the
   operator function may be a member of the class or an ordinary (nonfriend) function. 
 3 You cannot create a new operator.All you can do is overload existing operators,such 
   as +, -, *, /, %, and so forth.
 4 You cannot change the number of arguments that an operator takes. For example, you 
   cannot change % from a binary to a unary operator when you overload %;you cannot 
   change ++ from a unary to a binary operator when you overload it.
¡ö You cannot change the precedence of an operator. An overloaded operator
   has the same precedence as the ordinary version of the operator. For example,
   x*y + z always means (x*y) + z, even if x, y, and z are objects and the 
   operators + and * have been overloaded for the appropriate classes.
¡ö The following operators cannot be overloaded: the dot operator (. ), the scope
   resolution operator (:: ), and the operators .* and ?: , which are not discussed
   in this book.
¡ö Although the assignment operator = can be overloaded so that the default meaning 
   of = is replaced by a new meaning, this must be done in a different way from
   what is described here. Overloading = is discussed in the section ¡°Overloading 
   the Assignment Operator¡± later in this chapter. Some other operators, including 
   [] and ->, also must be overloaded in a way that is different from what is described
   in this chapter. The operators []  and -> are discussed later in this book.
 ************************************************************************************
               Constructors for Automatic Type Conversion
 ************************************************************************************
            Money base_amount(100, 60), full_amount;
            full_amount = base_amount + 25;

 The constant 25 is an integer and is not of type Money.the system first checks to see 
 if the operator + has been overloaded for the combination of a value of type Money 
 and an integer. Since there is no such overloading, the system next looks to see if 
 there is a constructor that takes a single argument that is an integer.The constructor 
 with one argument of type long tells the system how to convert an integer, such as 
 25,to a value of type Money.Note that this type conversion will not work unless there 
 is a suitable constructor.
           full_amount = base_amount + 25.67; //error
 To make this use of + legal, you could change the definition of the class Money by 
 adding another constructor. The function declaration for the constructor you need to 
 add is the following:
           class Money
           {
           public:
               . . .
               Money(double amount);
               . . .
           }
 ******************************************************************************/
class Money
{
public:
	friend Money operator +(const Money& amount1, const Money& amount2);
	friend Money operator -(const Money& amount1, const Money& amount2);
	friend Money operator -(const Money& amount);
	friend bool operator ==(const Money& amount1, const Money& amount2);
	friend istream& operator >>(istream& ins, Money& amount);
	friend ostream& operator <<(ostream& outs, const Money& amount);
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
    Money cost(1, 50), tax(0, 15), total;
    total = cost + tax;
    cout << "cost = ";
    cost.output(cout);
    cout << endl;
    cout << "tax = ";
    tax.output(cout);
    cout << endl;
    cout << "total bill = ";
    total.output(cout);
    cout << endl;
    if (cost == tax)
    cout << "Move to another state.\n";
    else
    cout << "Things seem normal.\n";

	cout << endl;
	cout << cost;
    return 0;
}

Money operator +(const Money& amount1, const Money& amount2)
{
    Money temp;
    temp.all_cents = amount1.all_cents + amount2.all_cents;
    return temp;
}

Money operator -(const Money& amount)
{
    Money temp;
    temp.all_cents = -amount.all_cents;
    return temp;
}


bool operator ==(const Money& amount1, const Money& amount2)
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

//Uses iostream, cctype, cstdlib:
istream& operator >>(istream& ins, Money& amount)
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
    if ( one_char != '$' || decimal_point != '.' || !isdigit(digit1) || !isdigit(digit2) )
    {
        cout << "Error illegal form for money input\n";
        exit(1);
    }
    cents = digit_to_int(digit1)*10 + digit_to_int(digit2);
    amount.all_cents = dollars*100 + cents;
    if (negative)
    amount.all_cents = -amount.all_cents;

    return ins;
}

//Uses cstdlib and iostream:
/*******************************************************************************
 When you add an & to the name of a returned type, you are saying that the operator 
 (or function) returns a reference, which means that you are returning  the object 
 itself, as opposed to the value of the object
 ******************************************************************************/
ostream& operator <<(ostream& outs, const Money& amount)
{
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if (amount.all_cents < 0)
        outs << "-$" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;

    return outs;
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
cost = $1.50
tax = $0.15
total bill = $1.65
Things seem normal.
*/
