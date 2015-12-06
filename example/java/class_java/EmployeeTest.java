import java.util.*;

/*-----------------------------------------------------------------------------------
 Now the time has come to show you how to write the kind of "workhorse classes"  that 
 are needed for more sophisticated applications. These classes typically do not  have 
 a main method. Instead, they have their own instance fields and methods. To build  a 
 complete program, you combine several classes, one of which has a main method.

 The simplest form for a class definition in Java is
 class ClassName
 {
     field1
     field2
     . . .
     constructor1
     constructor2
     . . .
     method1
     method2
     . . .
 }

 Note that the example program consists of two classes: the Employee class and a cla-
 ss EmployeeTest with the public access specifier. The main method with the instruct-
 ions that we just described is contained in the EmployeeTest class. The name of  the 
 source file is EmployeeTest.java because the name of the file must match the name of 
 the public class. You can only have one public class in a source file, but you can -
 have any number of nonpublic classes.

 when you compile this source code, the compiler creates two class files in the dire-
 ctory: EmployeeTest.class and Employee.class. You then start the program by giving -
 the bytecode interpreter the name of the class that contains the main method of your 
 program:
     java EmployeeTest
 The bytecode interpreter starts running the code in the main method in the         -
 EmployeeTest class.

 ----> Use of Multiple Source Files
 The program has two classes in a single source file . Many programmers prefer to put 
 each class into its own source file. For example, you can place the Employee class -
 into a file Employee.java and the EmployeeTest class into EmployeeTest.java.
 If you like this arrangement, then you have two choices for compiling the program. -
 You can invoke the Java compiler with a wildcard:
     javac Employee*.java
 Then, all source files matching the wildcard will be compiled into class files . Or, 
 you can simply type
     javac EmployeeTest.java
 You may find it surprising that the second choice works even though the Employee.java 
 file is never explicitly compiled. However, when the Java compiler sees the Employee 
 class being used inside EmployeeTest.java, it will look for a file named Employee.class. 
 If it does not find that file, it automatically searches for Employee.java and comp-
 iles it. Moreover, if the timestamp of the version of Employee.java that it finds i-
 s newer than that of the existing Employee.class file, the Java compiler will autom-
 atically recompile the file.
 If you are familiar with the make facility of UNIX (or one of its Windows cousins, -
 such as nmake), then you can think of the Java compiler as having the make function-
 ality already built in.
 ----------------------------------------------------------------------------------*/
public class EmployeeTest
{
/*-----------------------------------------------------------------------------------
 ----> Factory Methods
 Here is another common use for static methods. The NumberFormat class uses factory -
 methods that yield formatter objects for various styles.
     NumberFormat currencyFormatter = NumberFormat.getCurrencyInstance();
     NumberFormat percentFormatter = NumberFormat.getPercentInstance();
     double x = 0.1;
     System.out.println(currencyFormatter.format(x)); // prints $0.10
     System.out.println(percentFormatter.format(x));  // prints 10%
 Why doesn't the NumberFormat class use a constructor instead? There are two reasons:
 * You can't give names to constructors. The constructor name is always the same as -
 the class name. But we want two different names to get the currency instance and the 
 percent instance.
 * When you use a constructor, you can't vary the type of the constructed object. But 
 the factory methods actually return objects of the class DecimalFormat, a subclass -
 that inherits from NumberFormat. 

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
   public static void main(String[] args)
   {
      // fill the staff array with three Employee objects
      Employee[] staff = new Employee[3];

      staff[0] = new Employee("Carl Cracker", 75000, 1987, 12, 15);
      staff[1] = new Employee("Harry Hacker", 50000, 1989, 10, 1);
      staff[2] = new Employee("Tony Tester", 40000, 1990, 3, 15);

      // raise everyone's salary by 5%
      for (Employee e : staff)
         e.raiseSalary(5);

      // print out information about all Employee objects
      for (Employee e : staff)
         System.out.println("name=" + e.getName() + ",salary=" + e.getSalary() + ",hireDay="
               + e.getHireDay());

        int n = Employee.getNextId(); // calls static method
        System.out.println("Next available id=" + n);
   }
}

/*-----------------------------------------------------------------------------------
 ----> public private
 The keyword public means that any method in any class can call the method. The priv-
 ate keyword makes sure that the only methods that can access these instance fields -
 are the methods of the Employee class itself. No outside method can read or write t-
 o these fields. The @name and @hireDay fields are references to @String and @Date o-
 bjects. This is quite usual: Classes will often contain instance fields of class ty-
 pe.
-----------------------------------------------------------------------------------*/
class Employee
{
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
 Static methods are methods that do not operate on objects. For example, the pow met-
 hod of the Math class is a static method. The expression
	 Math.pow(x, a)
 computes the power x^a. It does not use any Math object to carry out its task. In o-
 ther words, it has no implicit parameter.

 It is legal to use an object to call a static method. For example, if harry is an	-
 Employee object,then you can call harry.getNextId() instead of Employee.getnextId(). 
 However, we find that notation confusing. The getNextId method doesn't look at harry 
 at all to compute the result. We recommend that you use class names, not objects, to 
 invoke static methods.

 ----> Use static methods in two situations:
 * When a method doesn't need to access the object state because all needed paramete-
   rs are supplied as explicit parameters (example: Math.pow).
 * When a method only needs to access static fields of the class.
-----------------------------------------------------------------------------------*/
    private static int nextId = 1; /* Static Fields */
	private int id;
    private String name;   //instance fields
    private double salary;
    private Date hireDay;

/*-----------------------------------------------------------------------------------
 ----> constructor
 As you can see, the name of the constructor is the same as the name of the class. T-
 his constructor runs when you construct objects of the Employee class, giving the i-
 nstance fields the initial state you want them to have. For example, when you create 
 an instance of the Employee class with code like this:
     new Employee("James Bond", 100000, 1950, 1, 1)
 you have set the instance fields as follows:
     name = "James Bond";
     salary = 100000;
     hireDay = January 1, 1950;

 A constructor can only be called in conjunction with the new operator. You can't ap-
 ply a constructor to an existing object to reset the instance fields. For example,
    james.Employee("James Bond", 250000, 1950, 1, 1) // compile-time error

 A constructor has the same name as the class.
 A class can have more than one constructor.
 A constructor can take zero, one, or more parameters.
 A constructor has no return value.
 A constructor is always called with the new operator.

 all Java objects are constructed on the heap and that a constructor must be combine-
 d with @new. 
 
 ----> Caution
 Be careful not to introduce local variables with the same names as the instance fie-
 lds.
-----------------------------------------------------------------------------------*/
   public Employee(String n, double s, int year, int month, int day) /* constructor */
   {
      name = n;
      salary = s;
      GregorianCalendar calendar = new GregorianCalendar(year, month - 1, day);
      // GregorianCalendar uses 0 for January
      hireDay = calendar.getTime();
   }

   public String getName() /* field accessors */
   {
      return name;
   }

   public double getSalary() /* field accessors */
   {
      return salary;
   }

/*-----------------------------------------------------------------------------------
 Be careful not to write accessor methods that return references to mutable  objects. 
 We violated that rule in our Employee class in which the getHireDay method returns -
 an object of class Date. This breaks encapsulation! Consider the following rogue co-
 de:
     Employee harry = . . .;
     Date d = harry.getHireDay();
     double tenYearsInMilliSeconds = 10 * 365.25 * 24 * 60 * 60 * 1000;
     d.setTime(d.getTime() - (long) tenYearsInMilliSeconds);
     // let's give Harry ten years of added seniority
 The reason is subtle. Both d and harry.hireDay refer to the same object. Applying m-
 utator methods to d automatically changes the private state of the employee object !
 If you need to return a reference to a mutable object , you should clone it first. A
 clone is an exact copy of an object stored in a new location . Here is the corrected 
 code:
 class Employee
 {
     . . .
     public Date getHireDay()
     {
         return hireDay.clone();
     }
    . . .
 }
 As a rule of thumb, always use clone whenever you need to return a copy of a mutabl-
 e data field.
 ----------------------------------------------------------------------------------*/
   public Date getHireDay() /* field accessors */
   {
      return hireDay;
   }

/*-----------------------------------------------------------------------------------
 ----> Implicit and Explicit Parameters
 The @raiseSalary method has two parameters . The first parameter, called the implicit 
 parameter, is the object of type Employee that appears before the method name. The -
 second parameter, the number inside the parentheses after the method name, is an ex-
 plicit parameter.

 As you can see, the explicit parameters are explicitly listed in the method declara-
 tion, for example, double byPercent. The implicit parameter does not appear in the -
 method declaration.

 In every method, the keyword this refers to the implicit parameter. If you like, you
 can write the raiseSalary method as follows:
    public void raiseSalary(double byPercent)
    {
        double raise = this.salary * byPercent / 100;
        this.salary += raise;
    }
-----------------------------------------------------------------------------------*/
   public void raiseSalary(double byPercent)
   {
      double raise = salary * byPercent / 100;
      salary += raise;
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
}

/*-----------------------------------------------------------------------------------

----> Final Instance Fields
 You can define an instance field as final. Such a field must be initialized when the
 object is constructed. That is, you must guarantee that the field value has been set
 after the end of every constructor. Afterwards, the field may not be modified again. 
 For example, the name field of the Employee class may be declared as final because -
 it never changes after the object is constructed.
    class Employee
    {
        private final String name;
        . . .
    }
 The final modifier is particularly useful for fields whose type is primitive or an -
 immutable class. (A class is immutable if none of its methods ever mutate its objec-
 ts. For example, the String class is immutable.) For mutable classes, the final mod-
 ifier is likely to confuse the reader. For example,
     private final Date hiredate;
 merely means that the object reference stored in the hiredate variable doesn't get -
 changed after the object is constructed. That does not mean that the hiredate object 
 is constant. Any method is free to invoke the setTime mutator on the object to which
 hiredate refers.
-----------------------------------------------------------------------------------*/
