

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
 ----> Static Fields
 If you define a field as static, then there is only one such field per class. For e-
 xample, We add an instance field id and a static field nextId to the Employee class:
     class Employee
     {
         private static int nextId = 1;
         private int id;
         . . .
     }
 Every employee object now has its own id field, but there is only one nextId field -
 that is shared among all instances of the class . Let's put it another way. If there 
 are 1,000 objects of the Employee class, then there are 1,000 instance fields id, o-
 ne for each object. But there is a single static field nextId . Even if there are no 
 employee objects, the static field nextId is present. It belongs to the class, not -
 to any individual object.
 
 ----> Static Constants 
 Static variables are quite rare. However, static constants are more common. For exa-
 mple, the Math class defines a static constant:
     public class Math
     {
         . . .
         public static final double PI = 3.14159265358979323846;
         . . .
     }
 You can access this constant in your programs as Math.PI .

 ----> Static Methods
	Static methods are methods that do not operate on objects. For example, the pow -
	method of the Math class is a static method. The expression
	    Math.pow(x, a)
	computes the power x^a. It does not use any Math object to carry out its task. I-
	n other words, it has no implicit parameter.

 It is legal to use an object to call a static method. For example, if harry is an  -
 Employee object,then you can call harry.getNextId() instead of Employee.getnextId(). 
 However, we find that notation confusing. The getNextId method doesn't look at harry 
 at all to compute the result. We recommend that you use class names, not objects, to 
 invoke static methods.


 ----> Use static methods in two situations:
 * When a method doesn't need to access the object state because all needed paramete-
   rs are supplied as explicit parameters (example: Math.pow).
 * When a method only needs to access static fields of the class.
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
 ----> The main Method
 Note that you can call static methods without having any objects. For example, you -
 never construct any objects of the Math class to call Math.pow. For the same reason, 
 the main method is a static method. The main method does not operate on any objects. 
 In fact, when a program starts, there aren't any objects yet. The static main metho-
 d executes, and constructs the objects that the program needs.

 Every class can have a main method. That is a handy trick for unit-testing of class-
 es. For example, you can add a main method to the Employee class. If you want to te-
 st the Employee class in isolation, simply execute
     java Employee
 If the employee class is a part of a larger application, then you start the applica-
 tion with
     java Application
 and the main method of the Employee class is never executed.

 Note that the Employee class also has a static main method for unit testing. Try ru-
 nning both
     java Employee
 and
     java StaticTest
 to execute both main methods.
-----------------------------------------------------------------------------------*/
   public static void main(String[] args) // unit test
   {
      Employee e = new Employee("Harry", 50000);
      System.out.println(e.getName() + " " + e.getSalary());
   }
}

/*-----------------------------------------------------------------------------------
 ----> Factory Methods
 Here is another common use for static methods. The NumberFormat class uses factory -
 methods that yield formatter objects for various styles.
     NumberFormat currencyFormatter = NumberFormat.getCurrencyInstance();
     NumberFormat percentFormatter = NumberFormat.getPercentInstance();
     double x = 0.1;
     System.out.println(currencyFormatter.format(x)); // prints $0.10
     System.out.println(percentFormatter.format(x)); // prints 10%
 Why doesn't the NumberFormat class use a constructor instead? There are two reasons:
 * You can't give names to constructors. The constructor name is always the same as -
 the class name. But we want two different names to get the currency instance and the 
 percent instance.
 * When you use a constructor, you can't vary the type of the constructed object. But 
 the factory methods actually return objects of the class DecimalFormat, a subclass -
 that inherits from NumberFormat. 

 ----------------------------------------------------------------------------------*/
