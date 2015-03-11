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
*/
