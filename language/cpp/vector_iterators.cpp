/*******************************************************************************
 Vectors,are one of the container template classes in the STL. Iterators are a 
 generalization of pointers. This section shows you how to use iterators with 
 vectors. Other container template classes,use iterators in the same way. So, all 
 you learn about iterators in this section will apply across a wide range of 
 containers and does not apply solely to vectors.

 Each container class has its own iterator types, just like each data type has 
 its own pointer type. But just as all pointer types behave essentially the same 
 for dynamic variables of their particular data type, so too does each iterator 
 type behave the same, but each iterator is used only with its own container class.
 Like a pointer variable, an iterator variable is located at (“points to”) one 
 data entry in the container.
 
             using std::vector<int>::iterator;
             iterator p;
 This declares pto be of the type iterator. What is the type iterator? The type
 iteratoris defined in the definition of the class vector<int>. Which class
 vector<int>? The one defined in the namespace std.

 You manipulate iterators using the following overloaded operators that apply to 
 iterator objects: 
 ■Prefix and postfix increment operators ++ for advancing the iterator to the 
   next data item. 
 ■Prefix and postfix decrement operators -- for moving the iterator to the previous 
   data item. 
 ■Equal and unequal operators, ==and !=, to test whether two iterators point to the 
   same data location. 
 ■A dereferencing operator *, so that if p is an iterator variable, then *p gives
  access to the data located at (“pointed to by”) p. This access may be readonly, 
  write-only, or allow both reading and changing of the data, depending on the 
  particular container class. 
 *******************************************************************************
                              Constant Iterator
 *******************************************************************************
 A constant iterator is an iterator that does not allow you to change the  element 
 at its location.
             std::vector<char>::const_iterator p = container.begin();
 or equivalently
             usingstd::vector<char>::const_iterator;
             const_iterator p = container.begin();
 With pdeclared in this way, the following would produce an error message:
             *p = 'Z'; error
 ******************************************************************************/

//Program to demonstrate STL iterators.
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


int main2()
{
    vector<char> container;
    container.push_back('A');
    container.push_back('B');
    container.push_back('C');
    container.push_back('D'); 
	
    for(int i = 0; i < 4; i++)
        cout << "container[" << i << "] == " << container[i] << endl;
	
    vector<char>::iterator p = container.begin();

	/*container[2] This notation is specialized  to vectors and arrays*/
    cout << "The third entry is " << container[2]<< endl;

	/*These two work for any random access iterator.*/
    cout << "The third entry is " << p[2]<< endl;
    cout << "The third entry is " << *(p + 2)<< endl;
	
    cout << "Back to container[0].\n";
	
    p = container.begin();
	
    cout << "which has value " << *p << endl;

    cout << "Two steps forward and one step back:\n";
    p++;
    cout << *p << endl;
    p++;
    cout << *p << endl;
    p--;/*This is the decrement operator. It works for any bidirectional iterator*/
    cout << *p << endl;
    return 0;
}

int main()
{
    vector<int> container;
	
    for(int i = 1; i <= 4; i++)
        container.push_back(i);
	
    cout << "Here is what is in the container:\n";
    vector<int>::iterator p;

/*******************************************************************************
 c.begin()returns an iterator for the container cthat points to the “first” data 
 item in the container c. 
 c.end() returns something that can be used to test when an iterator has passed 
 beyond the last data item in a container c. The iterator c.end()is completely 
 analogous to NULL used to test when a pointer has passed the last node in a linked 
 list. The iterator c.end()is thus an iterator that is located at no data item but 
 that is a kind of end marker or sentinel.
 ********************************************************************************/
    for(p = container.begin(); p != container.end(); p++)
        cout << *p << " ";
    cout << endl;

    cout << "Reverse:\n";
    vector<int>::reverse_iterator rp;

/*******************************************************************************
 Reverse Iterators
 A reverse iterator can be used to cycle through all elements of a container, 
 provided that the container has bidirectional iterators. The general scheme is 
 as follows:
             STL_Container<type>::reverse_iterator rp;
             for(rp = c.rbegin(); rp != c.rend(); rp++)
                          Process_At_Locationp;
 The object c is a container class with bidirectional iterators.

 rbegin() returns an iterator located at the last element.
 rend() returns a sentinel that marks the “end” of the elements in the reverse 
 order. Note that for an iterator of type reverse_iterator, the increment operator 
 ++ moves backward through the elements. In other words, the meanings of -- and ++ 
 are interchanged. 
 ******************************************************************************/	
    for(rp = container.rbegin(); rp != container.rend(); rp++)
    cout << *rp << " ";
    cout << endl;
	
	cout << "Setting entries to 0:\n";
	
    for(p = container.begin(); p != container.end(); p++)
        *p = 0;

    cout << "Container now contains:\n";
	
    for(p = container.begin(); p != container.end(); p++)
        cout << *p << " ";
	
    cout << endl;
	
	main2();
	
    return 0;
}


