/*******************************************************************************
                   set Template Class Details
 *******************************************************************************
 Type name set<T> or set<T, Ordering> for a set of elements of type T.
 The Ordering is used to sort elements for storage. If no Ordering is given, the 
 ordering used is the binary operator <.
 Library header: <set>, which places the definition in the stdnamespace.
 Defined types include: value_type, size_type.
 Iterators: iterator, const_iterator, reverse_iterator, and const_reverse_iterator.
 All iterators are bidirectional and those not including const_are mutable.
 begin(), end(), rbegin(), and rend() have the expected behavior.
 Adding or deleting elements does not affect iterators, except for an iterator 
 located at the element removed.
 *******************************************************************************
 Member Function (sis a Set Object)

 s.insert(Element) Insert a copy of Elementin the set. If Elementis already in 
                   the set, this has no effect.
 s.erase(Element)  Removes Element from the set. If Element is not in the set, 
                   this has no effect.
 s.find(Element)   Returns a mutable iterator located at the copy of Elementin 
                   the set. If Elementis not in the set, s.end() is returned. 
 s.erase(Iterator) Erases the element at the location of the Iterator.
 s.size()          Returns the number of elements in the set.
 s.empty()         Returns true if the set is empty; otherwise returns false.
 s1 == s2          Returns trueif the sets contains the same elements; otherwise 
                   returns false.
                   
 The set template class also has a default constructor, a copy constructor, as 
 well as other specialized constructors not mentioned here. It also has a destructor 
 that returns all storage for recycling and a well-behaved assignment operator

 ******************************************************************************/



//Program to demonstrate use of the set template class.
#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;

int main()
{
    set<char> s;

    s.insert('A');
    s.insert('D');
    s.insert('D');
    s.insert('C');
    s.insert('C');
    s.insert('B');

    cout << "The set contains:\n";
    set<char>::const_iterator p;
    for(p = s.begin(); p != s.end(); p++)
        cout << *p << " ";
	
    cout << endl;

    cout << "Removing C.\n";
    s.erase('C');
	
    for(p = s.begin(); p != s.end(); p++)
        cout << *p << " ";
	
    cout << endl;

    return 0;
}
