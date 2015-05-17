import java.util.*;

/*-----------------------------------------------------------------------------------
 Note that the example program consists of two classes: the Employee class and a cla-
 ss EmployeeTest with the public access specifier. The main method is contained in t-
 he EmployeeTest class. The name of the source file is  EmployeeTest.java because the 
 name of the file must match the name of the public class. You can only have one pub-
 lic class in a source file, but you can have any number of nonpublic classes.

 when you compile this source code, the compiler creates two class files in the dire-
 ctory: EmployeeTest.class and Employee.class. You then start the program by giving -
 the bytecode interpreter the name of the class that contains the main method of your 
 program:
     java EmployeeTest
 The bytecode interpreter starts running the code in the main method in the EmployeeTest 
 class. This code in turn constructs three new Employee objects and shows you their -
 state.

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
   }
}

/*-----------------------------------------------------------------------------------
The keyword public means that any method in any class can call the method. The priva-
te keyword makes sure that the only methods that can access these instance fields are 
the methods of the Employee class itself. No outside method can read or write to the-
se fields.
-----------------------------------------------------------------------------------*/
class Employee
{
   private String name;
   private double salary;
   private Date hireDay;

/*-----------------------------------------------------------------------------------
 As you can see, the name of the constructor is the same as the name of the class. T-
 his constructor runs when you construct objects of the Employee class, giving the i-
 nstance fields the initial state you want them to have. A constructor can only be c-
 alled in conjunction with the new operator. You can't apply a constructor to an exi-
 sting object to reset the instance fields. For example,
    james.Employee("James Bond", 250000, 1950, 1, 1) // compile-time error

 A constructor has the same name as the class.
 A class can have more than one constructor.
 A constructor can take zero, one, or more parameters.
 A constructor has no return value.
 A constructor is always called with the new operator.

 all Java objects are constructed on the heap and that a constructor must be combine-
 d with new. 
 
 ----> Caution
 Be careful not to introduce local variables with the same names as the instance fie-
 lds.
-----------------------------------------------------------------------------------*/
   public Employee(String n, double s, int year, int month, int day)
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

   public double getSalary()
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
   public Date getHireDay()
   {
      return hireDay;
   }

/*-----------------------------------------------------------------------------------
 Implicit and Explicit Parameters
 The raiseSalary method has two parameters . The first parameter, called the implicit 
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
}

/*-----------------------------------------------------------------------------------
 You can only have one public class in a source file , but you can have any number of
 nonpublic classes.

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
 immutable class.

----> Use of Multiple Source Files
The program in Listing 4.2 has two classes in a single source file . Many programmers
prefer to put each class into its own source file. For example, you can place the Em-
ployee class into a file Employee.java and the EmployeeTest class into EmployeeTest.java.
If you like this arrangement, then you have two choices for compiling the program. Y-
ou can invoke the Java compiler with a wildcard:
    javac Employee*.java
Then, all source files matching the wildcard will be compiled into class files. Or, -
you can simply type
    javac EmployeeTest.java
You may find it surprising that the second choice works even though the Employee.java 
file is never explicitly compiled. However , when the Java compiler sees the Employee 
class being used inside EmployeeTest.java, it will look for a file named Employee.class. 
If it does not find that file, it automatically searches for Employee.java and compi-
les it. Moreover, if the timestamp of the version of Employee.java that it finds is -
newer than that of the existing Employee.class file, the Java compiler will automati-
cally recompile the file.
-----------------------------------------------------------------------------------*/
