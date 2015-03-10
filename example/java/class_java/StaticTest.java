/**
 * This program demonstrates static methods.
 * @version 1.01 2004-02-19
 * @author Cay Horstmann
 */
public class StaticTest
{
   public static void main(String[] args)
   {
      // fill the staff array with three Employee objects
      Employee[] staff = new Employee[3];

      staff[0] = new Employee("Tom", 40000);
      staff[1] = new Employee("Dick", 60000);
      staff[2] = new Employee("Harry", 65000);

      // print out information about all Employee objects
      for (Employee e : staff)
      {
         e.setId();
         System.out.println("name=" + e.getName() + ",id=" + e.getId() + ",salary="
               + e.getSalary());
      }

      int n = Employee.getNextId(); // calls static method
      System.out.println("Next available id=" + n);
   }
}


/*-----------------------------------------------------------------------------------
Static Fields
    If you define a field as static, then there is only one such field per class . In 
    contrast, each object has its own copy of all instance fields. Every employee ob-
    ject now has its own @id field, but there is only one @nextId field that is shar-
    ed mong all instances of the class.
Static Constants 

Static Methods
    Static methods are methods that do not operate on objects.However, static methods  
    can access the static fields in their class.
Use static methods in two situations:
    * When a method doesn't need to access the object state because all needed paramet-
      ers are supplied as explicit parameters (example: Math.pow).
    * When a method only needs to access static fields of the class (example:
      Employee.getNextId).
-----------------------------------------------------------------------------------*/
class Employee
{
   private static int nextId = 1; /* Static Fields */

   private String name;
   private double salary;
   private int id;

   public Employee(String n, double s)
   {
      name = n;
      salary = s;
      id = 0;
   }

   public String getName()
   {
      return name;
   }

   public double getSalary()
   {
      return salary;
   }

   public int getId()
   {
      return id;
   }

   public void setId()
   {
      id = nextId; // set id to next available id
      nextId++;
   }

   public static int getNextId() /* Static Methods */
   {
      return nextId; // returns static field
   }

/*-----------------------------------------------------------------------------------
The main Method
    Note that you can call static methods without having any objects. For example, y-
    ou never construct any objects of the Math class to call Math.pow. For the same -
    reason, the main method is a static method. The main method does not operate on -
    any objects. In fact, when a program starts, there aren't any objects yet. The s-
    tatic main method executes, and constructs the objects that the program needs.

    Every class can have a main method. That is a handy trick for unit-testing of cl-
    asses. If you want to test the Employee class in isolation, simply execute
            java Employee
-----------------------------------------------------------------------------------*/
   public static void main(String[] args) // unit test
   {
      Employee e = new Employee("Harry", 50000);
      System.out.println(e.getName() + " " + e.getSalary());
   }
}
