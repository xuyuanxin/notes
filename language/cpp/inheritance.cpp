/*******************************************************************************
class D is derived from another class B means that class D has all the features 
of class B and some extra, added features as well.This is usually expressed by 
saying that the derived class inheritsthe member variables and member functions.
B is the base class and D is the derived class. We also say that D is the child 
class and B is the parent class.
********************************************************************************
                            Inherited Members
********************************************************************************
A derived class automatically has all the member variables and all the ordinary 
member functions of the base class. These members from the base class are said to 
be inherited. These inherited member functions and inherited member variables are, 
with one exception, not mentioned in the definition of the derived class, but they 
are automatically members of the derived class. As explained in the text, you do 
mention an inherited member function in the definition of the derived class if you 
want to change the definition of the inherited member function.
********************************************************************************
                An Object of a Derived Class Has More Than One Type
********************************************************************************
an object of a class type can be used anywhere that an object of any of its ancestor 
classes can be used. 
********************************************************************************
                     Constructors in Derived Classes
********************************************************************************
A derived class does not inherit the constructors of its base class. However, when 
defining a constructor for the derived class, you can and should include a call to 
a constructor of the base class (within the initialization section of the constructor 
definition).If you do not include a call to a constructor of the base class, then the
default (zero-argument) constructor of the base class will automatically be called 
when the derived class constructor is called.
********************************************************************************
			          order of constructor calls
********************************************************************************
The call to the base class constructor is the first action taken by a derived
class constructor. Thus, if class B is derived from class A and class C is derived
from class B, then when an object of the class C is created, first a constructor
for the class A is called, then a constructor for B is called, and finally the
remaining actions of the C constructor are taken.
********************************************************************************
                            Protected Members
********************************************************************************
If you use the qualifier protected, rather than private or public, before a member 
variable of a class, then for any class or function other than a derived class 
(or a derived class of a derived class, etc.), the situation is the same as if 
the member variable were labeled private. However, in the definition of a member 
function of a derived class, the variable can be accessed by name. Similarly, if 
you use the qualifier protected before a member function of a class, then for any 
class or function other than a derived class (or a derived class of a derived 
class, etc.), that is the same as if the member function were labeled private. 
However,in the definition of a member function of a derived class the protected 
function can be used.Inherited protected members are inherited in the derived 
class as if they were marked protected in the derived class. In other words, if 
a member is marked as protected in a base class, then it can be accessed by name 
in the definitions of all descendant classes, not just in those classes directly 
derived from the base class.
********************************************************************************
                    functions that are not inherited
********************************************************************************
We have already seen that, as a practical matter, constructors are not inherited 
and that private member functions are not inherited. Destructors are also effectively 
not inherited.
The assignment operator = is also not inherited. 

********************************************************************************/
