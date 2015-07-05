/*-----------------------------------------------------------------------------------
----> Object: The Cosmic Superclass
The Object class is the ultimate ancestor, every class in Java extends Object. Howe-
ver, you never have to write
	class Employee extends Object
The ultimate superclass Object is taken for granted if no superclass is explicitly -
mentioned. 

 You can use a variable of type Object to refer to objects of any type:
	Object obj = new Employee("Harry Hacker", 35000);
Of course, a variable of type  Object is only useful as a generic holder for arbitr-
ary values. To do anything specific with the value , you need to have some knowledge 
about the original type and apply a cast:
	Employee e = (Employee) obj;
	
In Java, only the primitive types ( numbers, characters, and boolean values) are not 
objects.

All array types, no matter whether they are arrays of objects or arrays of primitive 
types, are class types that extend the Object class.
	Employee[] staff = new Employee[10];
	obj = staff; // OK
	obj = new int[10]; // OK

 ----> The equals Method

 ----------------------------------------------------------------------------------*/

