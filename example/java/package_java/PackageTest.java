/*-----------------------------------------------------------------------------------
 To place classes inside a package,you must put the name of the package at the top of 
 your source file, before the code that defines the classes in the package. If you d-
 on't put a package statement in the source file,then the classes in that source file 
 belong to the default package. The default package has no package name. 

 Place source files into a subdirectory that matches the full package name. For exam-
 ple, all source files in the package com.horstmann.corejava package should be in a -
 subdirectory com/horstmann/corejava (com\horstmann\corejava on Windows).The compiler 
 places the class files into the same directory structure.

 To compile this program, simply change to the base directory and run the command
         javac PackageTest.java
 The compiler automatically finds the file com/horstmann/corejava/Employee.java and -
 compiles it.


 The compiler does not check the directory structure when it compiles source files. -
 For example, suppose you have a source file that starts with the directive package -
 com.mycompany; You can compile the file even if it is not contained in a subdirecto-
 ry com/mycompany. The source file will compile without errors if it doesn't depend -
 on other packages. However, the resulting program will not run . The virtual machine 
 won't find the resulting classes when you try to run the program.

 classes are stored in subdirectories of the file system. The path to  the class must 
 match the package name.
-----------------------------------------------------------------------------------*/
import com.horstmann.corejava.*; // the Employee class is defined in that package
import static java.lang.System.*;

/**
 * This program demonstrates the use of packages.
 * @version 1.11 2004-02-19
 * @author Cay Horstmann
 */
public class PackageTest
{
   public static void main(String[] args)
   {
      // because of the import statement, we don't have to use com.horstmann.corejava.Employee here
      Employee harry = new Employee("Harry Hacker", 50000, 1989, 10, 1);

      harry.raiseSalary(5);

      // because of the static import statement, we don't have to use System.out here
      out.println("name=" + harry.getName() + ",salary=" + harry.getSalary());
   }
}


/*
 Java allows you to group classes in a collection called a package. Packages are con-
 venient for organizing your work and for separating your work from code libraries p-
 rovided by others. The standard Java library is distributed over a number of packag-
 es, including java.lang, java.util, java.net, and so on . The standard Java packages 
 are examples of hierarchical packages. Just as you have nested subdirectories on yo-
 ur hard disk, you can organize packages by using levels of nesting.All standard Java 
 packages are inside the java and javax package hierarchies.

 A class can use all classes from its own package and all public classes from other -
 packages. You can access the public classes in another package in two ways. The fir-
 st is simply to add the full package name in front of every class name. For example:
         java.util. Date today = new java.util. Date();
 The simpler, and more common, approach is to use the import statement . For example, 
 you can import all classes in the java.util package with the statement
         import java.util.*;
 Then you can use
         Date today = new Date();
 without a package prefix. You can also import a specific class inside a package:
         import java.util.Date;
 The java.util.* syntax is less tedious. It has no negative effect on code size. How-
 ever, if you import classes explicitly , the reader of your code knows exactly which
 classes you use. However, note that you can only use the * notation to import a sin-
 gle package. You cannot use import java.* or import java.*.* to import  all packages 
 with the java prefix.

----> The Class Path

 Class files can also be stored in a JAR (Java archive) file. A JAR file contains mu-
 ltiple class files and subdirectories in a compressed format, saving space and impr-
 oving performance. When you use a third-party library in your programs, you will us-
 ually be given one or more JAR files to include. The JDK also supplies a number of -
 JAR files, such as the file jre/lib/rt.jar that contains thousands of library class-
 es. JAR files use the ZIP format to organize files and subdirectories. You can use -
 any ZIP utility to peek inside rt.jar and other JAR files.

 To share classes among programs, you need to do the following:
 1 Place your class files inside a directory, for example, /home/user/classdir . Note
   that this directory is the base directory for the package tree. If you add the cl-
   ass com.horstmann.corejava.Employee, then the  Employee.class file must be located 
   in the subdirectory /home/user/classdir/com/horstmann/corejava.
 2 Place any JAR files inside a directory, for example, /home/user/archives.
 3 Set the class path. The class path is the collection of all locations that can co-
   ntain class files.
   
 In UNIX, the elements on the class path are separated by colons:
     /home/user/classdir:.:/home/user/archives/archive.jar
 In Windows, they are separated by semicolons:
     c:\classdir;.;c:\archives\archive.jar
 In both cases, the period denotes the current directory.
 
 This class path contains
 1 The base directory /home/user/classdir or c:\classdir;
 2 The current directory (.); and
 3 The JAR file /home/user/archives/archive.jar or c:\archives\archive.jar.

 The runtime library files (rt.jar and the other JAR files in the  jre/lib and jre/lib/ext 
 directories) are always searched for classes; don't include them explicitly in the -
 class path.

 Caution
 The javac compiler always looks for files in the current directory, but the java vi-
 rtual machine launcher only looks into the current directory if the "." directory is 
 on the class path. If you have no class path set, this is not a problem, the default 
 class path consists of the "." directory. But if you have set the class path and fo-
 rgot to include the "." directory, your programs will compile without error, but th-
 ey won't run.

 The class path lists all directories and archive files that  are starting points for 
 locating classes. Let's consider our sample class path:
     /home/user/classdir:.:/home/user/archives/archive.jar
 Suppose the virtual machine searches for the class file of the 
     com.horstmann.corejava.Employee
 It first looks in the system class files that are stored in archives in the  jre/lib 
 and jre/lib/ext directories. It won't find the class file there , so it turns to the 
 class path. It then looks for the following files:
 1 /home/user/classdir/com/horstmann/corejava/Employee.class
 2 com/horstmann/corejava/Employee.class starting from the current directory
 3 com/horstmann/corejava/Employee.class inside /home/user/archives/archive.jar
 
 The compiler has a harder time locating files than does the virtual machine . If you
 refer to a class without specifying its package,the compiler first needs to find out 
 the package that contains the class. It consults all import directives as possible -
 sources for the class. For example, suppose the source file contains directives
     import java.util.*;
     import com.horstmann.corejava.*;
 and the source code refers to a class Employee. The compiler then tries to find
 1 java.lang.Employee (because the  java.lang package is always imported by default),
 2 java.util.Employee  com.horstmann.corejava.Employee, 
 3 and Employee in the current package. 
 It searches for each of these classes in all of the locations of the class path . It
 is a compile-time error if more than one class is found. (Classes must be unique, so 
 the order of the import statements doesn't matter.)
 The compiler goes one step further.It looks at the source files to see if the source 
 is newer than the class file. If so, the source file is recompiled automatically. R-
 ecall that you can import only public classes from other packages. A source file can 
 only contain one public class, and the names of the file and the public class must -
 match. Therefore, the compiler can easily locate source files for public classes. H-
 owever, you can import nonpublic classes from the current package. These classes may 
 be defined in source files with different names. If you import a class from the cur-
 rent package, the compiler searches all source files of the current package to see -
 which one defines the class.

----> Setting the Class Path
 It is best to specify the class path with the -classpath (or -cp) option:
     java -classpath /home/user/classdir:.:/home/user/archives/archive.jar MyProg
 or
     java -classpath c:\classdir;.;c:\archives\archive.jar MyProg
 The entire command must be typed onto a single line. It is a good idea to place such
 a long command line into a shell script or a batch file.
 Using the -classpath option is the preferred approach for setting the class path. An
 alternate approach is the CLASSPATH environment variable. The details depend on your
 shell. With the Bourne Again shell (bash), use the command
     export CLASSPATH=/home/user/classdir:.:/home/user/archives/archive.jar
 With the C shell, use the command
     setenv CLASSPATH /home/user/classdir:.:/home/user/archives/archive.jar
 With the Windows shell, use
     set CLASSPATH=c:\classdir;.;c:\archives\archive.jar
 The class path is set until the shell exits.
 


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

----> Use of Multiple Source Files
 Many programmers prefer to put each class into its own source file. For example, you 
 can place the Employee class into a file Employee.java and the EmployeeTest class i-
 nto EmployeeTest.java. If you like this arrangement, then you have two choices for -
 compiling the program. You can invoke the Java compiler with a wildcard:
         javac Employee*.java
 Then, all source files matching the wildcard will be compiled into class files . Or, 
 you can simply type
         javac EmployeeTest.java
 You may find it surprising that the second choice works even though the Employee.java 
 file is never explicitly compiled. However, when the Java compiler sees the Employee 
 class being used inside EmployeeTest.java, it will look for a file named Employee.class. 
 If it does not find that file, it automatically searches for Employee.java and comp-
 iles it. Moreover, if the timestamp of the version of Employee.java that it finds is 
 newer than that of the existing  Employee.class file, the Java compiler will automa-
 tically recompile the file. you can think of the Java compiler as having  the "make" 
 functionality already built in.


*/
