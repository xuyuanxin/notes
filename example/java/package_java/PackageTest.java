/*-----------------------------------------------------------------------------------
 two packages: The PackageTest class belongs to the default package, and the Employee 
 class belongs to the com.horstmann.corejava package. Therefore, the Employee.java f-
 ile must be in a subdirectory com/horstmann/corejava.
     .(base directory)
     |-- PackageTest.java
     |-- PackageTest.class
     |-- com/
         |-- horstmann/
             |-- corejava/
                 |-- Employee.java
                 |-- Employee.class
 To compile this program, simply change to the base directory and run the command
     javac PackageTest.java
 The compiler automatically finds the file com/horstmann/corejava/Employee.java and -
 compiles it.

     Let's look at a more realistic example, in which we don't use the default packa-
 ge but have classes distributed over several packages (com.horstmann.corejava and  -
 com.mycompany)
     .(base directory)
     |-- com/
         |-- horstmann/
         |   |-- corejava/
         |   |   |-- Employee.java
         |   |   |-- Employee.class 
         |-- mycompany/
             |-- PayrollApp.java
             |-- PayrollApp.class
 In this situation, you still must compile and run classes from the base directory, -
 that is, the directory containing the com directory:
     javac com/mycompany/PayrollApp.java
     java com.mycompany.PayrollApp

 ----> Caution 
 The compiler does not check the directory structure when it compiles source files. -
 For example, suppose you have a source file that starts with the directive 
     package com.mycompany; 
 You can compile the file even if it is not contained in a subdirectory com/mycompany. 
 The source file will compile without errors if it doesn't depend on other  packages. 
 However, the resulting program will not run . The virtual machine won't find the re-
 sulting classes when you try to run the program.

 classes are stored in subdirectories of the file system. The path to  the class must 
 match the package name.
 ----------------------------------------------------------------------------------*/
import com.horstmann.corejava.*; // the Employee class is defined in that package
import static java.lang.System.*;

public class PackageTest
{
   public static void main(String[] args)
   {
      // because of the import statement, we don't have to use com.horstmann.corejava.Employee here
      EmployeeP harry = new EmployeeP("Harry Hacker", 50000, 1989, 10, 1);

      harry.raiseSalary(5);

      // because of the static import statement, we don't have to use System.out here
      out.println("name=" + harry.getName() + ",salary=" + harry.getSalary());
   }
}

/*-----------------------------------------------------------------------------------
 From the point of view of the compiler, there is absolutely no relationship  between
 nested packages. For example, the packages java.util and java.util.jar have  nothing
 to do with each other. Each is its own independent collection of classes.

----> class base
 A class is the template or blueprint from which objects are made.Think about classes
 as cookie cutters. Objects are the cookies themselves . When you construct an object
 from a class, you are said to have created an instance of the class.

 The bits of data in an object are called its instance fields,and the procedures that 
 operate on the data are called its  methods. A specific object that is an instance -
 of a class will have specific values of its instance fields. The set of those values 
 is the current state of the object. Whenever you invoke a method on an object, its -
 state may change.

----> Relationships between Classes
 The most common relationships between classes are
 1 Dependence ("uses-a")
 2 Aggregation ("has-a")
 3 Inheritance ("is-a")

----> Objects and Object Variables
 There is an important difference between objects and object variables . For example,
 the statement
         Date deadline; // deadline doesn't refer to any object
         Data birthday;
 defines an object variable, deadline, that can refer to objects of type Date . It is
 important to realize that the variable deadline is not an object and, in fact , does 
 not even refer to an object yet. You cannot use any Date methods on this variable at 
 this time. The statement
         s = deadline.toString(); // not yet
 would cause a compile-time error.
 You must first initialize the deadline variable. You have two choices.Of course, you
 can initialize the variable with a newly constructed object:
         deadline = new Date();
         birthday = new Date();
 Or you can set the variable to refer to an existing object:
         deadline = birthday;

 It is important to realize that an object variable doesn't actually contain an obje-
 ct. It only refers to an object.
 In Java, the value of any object variable is a reference to an object that is stored
 elsewhere. The return value of the new operator is also a reference.A statement such 
 as 
         Date deadline = new Date();
 has two parts. The expression new Date() makes an object of type Date, and its value
 is a reference to that newly created object. That reference is then stored in the
 deadline variable.
 You can explicitly set an object variable to null to indicate that it currently ref-
 ers to no object.
         deadline = null;
         . . .
         if (deadline != null)
             System.out.println(deadline);
 If you apply a method to a variable that holds null, a runtime error occurs.
         birthday = null;
         String s = birthday.toString(); // runtime error!
 Local variables are not automatically initialized to null. You must initialize them,
 either by calling new or by setting them to null.


*/
