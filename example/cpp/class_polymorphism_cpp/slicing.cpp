//Program to illustrate use of a virtual function
//to defeat the slicing problem.
#include <string>
#include <iostream>
using namespace std;

class Pet
{
public:
    virtual void print();
    string name;
};

class Dog : public Pet
{
public:
    virtual void print(); //Keyword virtual not needed, but put here for clarity. (It is also good style!)
    string breed;
};

int main()
{
    Dog vdog;
    Pet vpet;

    vdog.name = "Tiny";
    vdog.breed = "Great Dane";
    vpet = vdog;

    //vpet.breed; is illegal since class Pet has no member named breed

    Dog *pdog;
    pdog = new Dog;
    pdog->name = "Tiny";
    pdog->breed = "Great Dane";

    Pet *ppet;
    ppet = pdog;
/*******************************************************************************
print() was declared virtual by the base class, Pet. So, when the compiler sees 
the call
        ppet->print();
it checks the virtual table for classes Pet and Dog and sees that ppet points to
an object of type Dog. It therefore uses the code generated for
        Dog::print(),
rather than the code for
        Pet::print()

1. If the domain type of the pointer p_ancestor is a base class for the domain type 
of the pointer p_descendant, then the following assignment of pointers is allowed:
        p_ancestor = p_descendant;
Moreover, none of the data members or member functions of the dynamic variable 
being pointed to by p_descendant will be lost.
2. Although all the extra fields of the dynamic variable are there, you will need 
virtual member functions to access them.        
********************************************************************************/
	
    ppet->print();  // These two print the same output:
    pdog->print();  // name: Tiny breed: Great Dane

/*******************************************************************************
//The following, which accesses member variables directly
//rather than via virtual functions, would produce an error:
//cout << "name: " << ppet->name << " breed: "
// << ppet->breed << endl;
//generates an error message: 'class Pet' has no member
//named 'breed' .
//See Pitfall section "Not Using Virtual Member Functions"
//for more discussion on this.
*******************************************************************************/
return 0;
}

void Dog::print()
{
    cout << "name: " << name << endl;
    cout << "breed: " << breed << endl;
}

void Pet::print()
{
    cout << "name: " << endl;//Note no breed mentioned
}

/*
output:

name: Tiny
breed: Great Dane
name: Tiny
breed: Great Dane

*/

