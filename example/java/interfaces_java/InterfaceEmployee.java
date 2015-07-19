//package interfaces;
import java.util.*;

public class Employee implements Comparable<Employee>
{
   private String name;
   private double salary;

   public Employee(String n, double s)
   {
      name = n;
      salary = s;
   }

   public String getName()
   {
      return name;
   }

   public double getSalary()
   {
      return salary;
   }

   public void raiseSalary(double byPercent)
   {
      double raise = salary * byPercent / 100;
      salary += raise;
   }

/*-----------------------------------------------------------------------------------
 In the interface declaration, the compareTo method was not declared public because -
 all methods in an interface are automatically public. However, when implementing the 
 interface, you must declare the method as public. Otherwise, the compiler assumes t-
 hat the method has package visibility¡ªthe default for a class. The compiler then c-
 omplains that you're trying to supply a weaker access privilege.

 @return a negative value if this employee has a lower salary than otherObject, 0  if 
 the salaries are the same, a positive value otherwise
 ----------------------------------------------------------------------------------*/
   public int compareTo(Employee other)
   {
      return Double.compare(salary, other.salary);
   }
}

public class InterfaceEmployee
{
   public static void main(String[] args)
   {
      Employee[] staff = new Employee[3];

      staff[0] = new Employee("Harry Hacker", 35000);
      staff[1] = new Employee("Carl Cracker", 75000);
      staff[2] = new Employee("Tony Tester", 38000);

      Arrays.sort(staff);

      // print out information about all Employee objects
      for (Employee e : staff)
         System.out.println("name=" + e.getName() + ",salary=" + e.getSalary());
   }
}

/*-----------------------------------------------------------------------------------
 ----> interfaces
 The first technique, called interfaces, is a way of describing what classes should -
 do, without specifying how they should do it. A class can implement one or more int-
 erfaces. You can then use objects of these implementing classes whenever conformance 
 to the interface is required. 

 In the Java programming language, an interface is not a class but a set of requirem-
 ents for the classes that want to conform to the interface.

 Typically, the supplier of some service states: "If your class conforms to a partic-
 ular interface, then I'll perform the service."  Let's look at a concrete example. -
 The @sort method of the @Arrays class promises to sort an array of objects, but und-
 er one condition: The objects must belong to classes that implement the Comparable -
 interface. Here is what the Comparable interface looks like:
     public interface Comparable<T>
	{
	    int compareTo(T other); // parameter has type T
     }
 All methods of an interface are automatically public. For that reason, it is not ne-
 cessary to supply the keyword public when declaring a method in an interface.

 Now suppose we want to use the sort method of the Arrays class to sort an array of -
 Employee objects. Then the Employee class must implement the Comparable interface. -
 To make a class implement an interface, you carry out two steps:
 1 You declare that your class intends to implement the given interface.
 2 You supply definitions for all methods in the interface.

 To declare that a class implements an interface, use the implements keyword:
     public class Employee implements Comparable<Employee>
 Of course, now the Employee class needs to supply the compareTo method.

 ---->
 Although you cannot put instance fields or static methods in an interface, you can -
 supply constants in them . Just as methods in an interface are automatically public, 
 fields are always "public static final".

 ----> Properties of Interfaces
 Interfaces never have instance fields, and the methods are never implemented in  the 
 interface. Supplying instance fields and method implementations is the job of the c-
 lasses that implement the interface. Interfaces are not classes. In particular,  you 
 can never use the @new operator to instantiate an interface:
     x = new Comparable(. . .); // ERROR
 However, even though you can't construct interface objects, you can still declare i-
 nterface variables.    
     Comparable x; // OK you can still declare interface variables.
 An interface variable must refer to an object of a class that implements the interf-
 ace:
     x = new Employee(. . .); // OK provided Employee implements Comparable

 Next, just as you use @instanceof to check whether an object is of a specific class,
 you can use @instanceof to check whether an object implements an interface:
     if (anObject instanceof Comparable) { . . . }
     
 Just as you can build hierarchies of classes, you can extend interfaces. This allows 
 for multiple chains of interfaces that go from a greater degree of generality to a -
 greater degree of specialization. For example, suppose you had an interface called -
 Moveable.
     public interface Moveable
     {
         void move(double x, double y);
     }
 Then, you could imagine an interface called Powered that extends it:
     public interface Powered extends Moveable
     {
         double milesPerGallon();
     }
     
 Although you cannot put instance fields or static methods in an interface, you can -
 supply constants in them. For example:
     public interface Powered extends Moveable
     {
         double milesPerGallon();
         double SPEED_LIMIT = 95; // a public static final constant
     }
 Just as methods in an interface are automatically public, fields are always        -
 "public static final".
 
 While each class can have only one superclass, classes can implement multiple inter-
 faces. Use commas to separate the interfaces that describe the characteristics  that 
 you want to supply.
    class Employee implements Cloneable, Comparable
 ----------------------------------------------------------------------------------*/