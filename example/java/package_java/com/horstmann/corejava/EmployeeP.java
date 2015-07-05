/*-----------------------------------------------------------------------------------
 To place classes inside a package, you must put the name of the package at the top -
 of your source file, before the code that defines the classes in the package. For e-
 xample, the file Employee.java starts out like this:
     package com.horstmann.corejava;
 If you don't put a package statement in the source file, then the classes in that s-
 ource file belong to the default package. The default package has no package name. 

 Place source files into a subdirectory that matches the full package name. For exam-
 ple, all source files in the package com.horstmann.corejava package should be in a -
 subdirectory com/horstmann/corejava (com\horstmann\corejava on Windows).The compiler 
 places the class files into the same directory structure. 
 ----------------------------------------------------------------------------------*/
package com.horstmann.corejava;

// the classes in this file are part of this package

import java.util.*;

// import statements come after the package statement

public class EmployeeP
{
   private String name;
   private double salary;
   private Date hireDay;

   public EmployeeP(String n, double s, int year, int month, int day)
   {
      name = n;
      salary = s;
      GregorianCalendar calendar = new GregorianCalendar(year, month - 1, day);
      // GregorianCalendar uses 0 for January
      hireDay = calendar.getTime();
   }

   public String getName()
   {
      return name;
   }

   public double getSalary()
   {
      return salary;
   }

   public Date getHireDay()
   {
      return hireDay;
   }

   public void raiseSalary(double byPercent)
   {
      double raise = salary * byPercent / 100;
      salary += raise;
   }
}
