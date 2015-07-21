//package textFile;

import java.io.*;
import java.util.*;

public class TextFileTest
{
   public static void main(String[] args) throws IOException
   {
      EmployeeRa[] staff = new EmployeeRa[3];

      staff[0] = new EmployeeRa("Carl Cracker", 75000, 1987, 12, 15);
      staff[1] = new EmployeeRa("Harry Hacker", 50000, 1989, 10, 1);
      staff[2] = new EmployeeRa("Tony Tester", 40000, 1990, 3, 15);

      // save all employee records to the file employee.dat
      try (PrintWriter out = new PrintWriter("employee.dat", "UTF-8"))
      {         
         writeData(staff, out);
      }
      
      // retrieve all records into a new array
      try (Scanner in = new Scanner(new FileInputStream("employee.dat"), "UTF-8"))
      {
         EmployeeRa[] newStaff = readData(in);

         // print the newly read employee records
         for (EmployeeRa e : newStaff)
            System.out.println(e);
      }
   }

   /**
    * Writes all employees in an array to a print writer
    * @param employees an array of employees
    * @param out a print writer
    */
   private static void writeData(EmployeeRa[] employees, PrintWriter out) throws IOException
   {
      // write number of employees
      out.println(employees.length);

      for (EmployeeRa e : employees)
         writeEmployee(out, e);
   }

   /**
    * Reads an array of employees from a scanner
    * @param in the scanner
    * @return the array of employees
    */
   private static EmployeeRa[] readData(Scanner in)
   {
      // retrieve the array size
      int n = in.nextInt();
      in.nextLine(); // consume newline

      EmployeeRa[] employees = new EmployeeRa[n];
      for (int i = 0; i < n; i++)
      {
         employees[i] = readEmployee(in);
      }
      return employees;
   }
   
   /**
    * Writes employee data to a print writer
    * @param out the print writer
    */
   public static void writeEmployee(PrintWriter out, EmployeeRa e)
   {
      GregorianCalendar calendar = new GregorianCalendar();
      calendar.setTime(e.getHireDay());
      out.println(e.getName() + "|" + e.getSalary() + "|" + calendar.get(Calendar.YEAR) + "|"
            + (calendar.get(Calendar.MONTH) + 1) + "|" + calendar.get(Calendar.DAY_OF_MONTH));
   }

   /**
    * Reads employee data from a buffered reader
    * @param in the scanner
    */
   public static EmployeeRa readEmployee(Scanner in)
   {
      String line = in.nextLine();
      String[] tokens = line.split("\\|");
      String name = tokens[0];
      double salary = Double.parseDouble(tokens[1]);
      int year = Integer.parseInt(tokens[2]);
      int month = Integer.parseInt(tokens[3]);
      int day = Integer.parseInt(tokens[4]);
      return new EmployeeRa(name, salary, year, month, day);
   }   
}

