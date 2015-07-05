/*-----------------------------------------------------------------------------------
----> Introduction to Object-Oriented Programming
A class is the template or blueprint from which objects are made . When you construct
an object from a class,you are said to have created an instance of the class.The bits 
of data in an object are called its instance fields , and the procedures that operate 
on the data are called its methods. 

When you start writing your own classes in Java , another tenet of OOP will make this
easier: Classes can be built by extending other classes . Java, in fact, comes with a 
"cosmic superclass" called Object. All other classes extend this class. When you ext-
end an existing class , the new class has all the properties and methods of the class 
that you extend. You then supply new methods and data fields that apply to your new -
class only. The concept of extending a class to obtain another class is called inher-
itance.

The most common relationships between classes are:
Dependence ("uses¨Ca")
Aggregation ("has¨Ca")
Inheritance ("is¨Ca")

----> Objects and Object Variables
The standard Java library contains a Data class. Its objects describe points in time, 
such as "December 31, 1999, 23:59:59 GMT" . Constructors always have the same name a-
s the class name. Thus, the constructor for the @Date class is called @Date. To cons-
truct a Date object, you combine the constructor with the new operator, as follows:
    new Date()
This expression constructs a new object. The object is initialized to the current da-
te and time.
---->
    Date birthday = new Date();
    Date deadline; // deadline doesn't refer to any object
deadline, that can refer to objects of type Date. It is important to realize that the 
variable deadline is not an object and,in fact, does not even refer to an object yet. 
You cannot use any Date methods on this variable at this time. The statement
    s = deadline.toString(); // not yet
would cause a compile-time error. You must first initialize the deadline variable. Y-
ou have two choices. Of course, you can initialize the variable with a newly constru-
cted object:
    deadline = new Date();
Or you can set the variable to refer to an existing object:
    deadline = birthday;
Now both variables refer to the same object.

                    +------+
    deadline ---->  | data |  <---- birthday
                    |------|
                    |      |
                    +------+

It is important to realize that an object variable doesn't actually contain an object. 
It only refers to an object. In Java, the value of any object variable is a reference 
to an object that is stored elsewhere. The return value of the new operator is also a 
reference. A statement such as
    Date deadline = new Date();
has two parts. The expression new Date() makes an object of type Date , and its value
is a reference to that newly created object. That reference is then stored in the de-
adline variable.You can explicitly set an object variable to null to indicate that it 
currently refers to no object.
    deadline = null;
    . . .
    if (deadline != null)
        System.out.println(deadline);
If you apply a method to a variable that holds null, a runtime error occurs.
    birthday = null;
    String s = birthday.toString(); // runtime error!
Local variables are not automatically initialized to null . You must initialize them,
either by calling new or by setting them to null.

----> Object: The Cosmic Superclass
The Object class is the ultimate ancestor, every class in Java extends Object. Howe-
ver, you never have to write
	class Employee extends Object
The ultimate superclass Object is taken for granted if no superclass is explicitly -
mentioned. You can use a variable of type Object to refer to objects of any type:
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
-----------------------------------------------------------------------------------*/
