//Program to demonstrate use of the stack template class from the STL.
#include <iostream>
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::stack;

/*******************************************************************************
                          StackTemplate Class
 *******************************************************************************
 Stack Adapter Template Class Details
 Type name stack<T> or stack<T, Underlying_Container> for a stack of elements of 
 type T.
 Library header: <stack>which places the definition in the stdnamespace.
 Defined types: value_type, size_type.
 There are no iterators.
 *******************************************************************************
 Member Function (s is a Stack Object.)
 s.size()  Returns the number of elements in the stack.
 s.empty() Returns trueif the stack is empty; otherwise returns false.
 s.top()   Returns a mutable reference to the top member of the stack.
 s.push(Element) Insert a copy of Elementat the top of the stack.
 s.pop()   Removes the top element of the stack. Note that popis a voidfunction. 
           It does not return the element removed.
 s1 == s2  True if s1.size() == s2.size() and each element of s1 is equal to the 
           corresponding element of s2; otherwise returns false.
           
 The stack template class also has a default constructor, a copy constructor, as 
 well as a constructor that takes an object of any sequential container class and 
 initializes the stack to the elements in the sequence. It also has a destructor 
 that returns all storage for recycling and a well-behaved assignment operator.
 ******************************************************************************/


int main()
{
    stack<char> s;

    cout << "Enter a line of text:\n";
    char next;
    cin.get(next);
	
    while(next != '\n')
    {
        s.push(next);
        cin.get(next);
    }

    cout << "Written backward that is:\n";
	
    while( ! s.empty() )
    {
        cout << s.top();
        s.pop();
    }
	
    cout << endl;

    return 0;
}

