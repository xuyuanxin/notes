//Program to demonstrate a function template.

#include <iostream>
using namespace std;


/*******************************************************************************
                            Function Template
 *******************************************************************************
 The function definition and the function declaration for a function template are 
 each prefaced with the following:
             template<class Type_Parameter>
 The function declaration (if used) and definition are the same as any  ordinary 
 function declaration and definition, except that the  Type_Parameter can be used 
 in place of a type.
 For example, the following is a function declaration for a function template:
             template<classT>
             void show_stuff(int stuff1, T stuff2, T stuff3);
 The definition for this function template might be as follows:
             template<classT>
             void show_stuff(int stuff1, T stuff2, T stuff3)
             {
                 cout << stuff1 << endl
                 << stuff2 << endl
                 << stuff3 << endl;
             }
 The function template given in this example is equivalent to having one function 
 declaration and one function definition for each possible  type name. The type 
 name is substituted for the type parameter (which is T in the example above). 
 For instance, consider the following function call:
             show_stuff(2, 3.3, 4.4);
 When this function call is executed, the compiler uses the function  definition 
 obtained by replacing T with the type name double. A separate definition will 
 be produced for each different type for which you use the template, but not for 
 any types you do not use. Only one definition  is generated for a specific type 
 regardless of the number of times you use the template.
 ******************************************************************************/




/*******************************************************************************
 This is often called the template prefix,and it tells the compiler that the
 definition or function declaration that follows is a template and that T is a 
 type parameter.In this context the word class actually means type.
 ******************************************************************************/
template<class T> /* template prefix */


/*******************************************************************************
 The function template definition is, in effect, a large collection of function
 definitions. Another definition for swap_valuesis obtained by replacing the type
 parameter T in the function template with the type name int. Yet another definition 
 is obtained by replacing the type parameter Twith char. 
 The compiler will not literally produce definitions for every possible type for 
 the function name swap_values, but it will behave exactly as if it had produced 
 all those function definitions. A separate definition will be produced for each 
 different type for which you use the template, but not for any types you do not 
 use. Only one definition is generated for a single type regardless of the number 
 of times you use the template for that type.

 1 You cannot have unused template parameters; that is, each template parameter 
 must be used in your template function.
 ******************************************************************************/
void swap_values(T& variable1, T& variable2)
{
    T temp;

    temp = variable1;
    variable1 = variable2;
    variable2 = temp;
}


/*******************************************************************************
 we place the function template definition before the main part of the program, 
 and we used no template function declaration. A function template may have a 
 function declaration, just like an ordinary function. 
 Many compilers do not allow separate compilation of templates, so you may need 
 to include your template definition with your code that uses it. As usual, at 
 least the function declaration must precede any use of the template function.
 Your safest strategy is not to use template function declarations, and to be
 sure the function template definition appears in the same file in which it is
 used and appears before the function template is called. However, the function 
 template definition can appear via a #includedirective. You can give the function 
 template definition in one file and then #includethat file in a file that uses the 
 template function.
 ****************************************************/
int main( )
{
    int integer1 = 1, integer2 = 2;
	
    cout << "Original integer values are " << integer1 << " " << integer2 << endl;
	
/*******************************************************************************
 When the C++ compiler gets to this function call, it notices the types of the 
 arguments—in this case int—and then it uses the template to produce a function 
 definition with the type parameter T replaced with the type name int. 
 ******************************************************************************/
    swap_values(integer1, integer2);

    cout << "Swapped integer values are " << integer1 << " " << integer2 << endl;
	
    char symbol1 = 'A', symbol2 = 'B';
	
    cout << "Original character values are " << symbol1 << " " << symbol2 << endl;
    swap_values(symbol1, symbol2);
    cout << "Swapped character values are "<< symbol1 << " " << symbol2 << endl;
	
    return 0;
}
