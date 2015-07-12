//package textFile;

import java.io.*;
import java.util.*;

/*-----------------------------------------------------------------------------------
 ----> How to Write Text Output
 For text output, use a PrintWriter. That class has methods to print strings and num-
 bers in text format. There is even a convenience constructor to link a PrintWriter -
 to a FileWriter. The statement
     PrintWriter out = new PrintWriter("employee.txt");
 is equivalent to
     PrintWriter out = new PrintWriter(new FileWriter("employee.txt"));

     String name = "Harry Hacker";
     double salary = 75000;
     out.print(name);
     out.print(' ');
     out.println(salary);
 This writes the characters
     Harry Hacker 75000.0

 ----> How to Read Text Input    
 ----------------------------------------------------------------------------------*/
public class TextFileTest
{
   public static void main(String[] args) throws IOException
   {
      Employee[] staff = new Employee[3];

      staff[0] = new Employee("Carl Cracker", 75000, 1987, 12, 15);
      staff[1] = new Employee("Harry Hacker", 50000, 1989, 10, 1);
      staff[2] = new Employee("Tony Tester", 40000, 1990, 3, 15);

      // save all employee records to the file employee.dat
      try (PrintWriter out = new PrintWriter("employee.dat", "UTF-8"))
      {         
         writeData(staff, out);
      }
      
      // retrieve all records into a new array
      try (Scanner in = new Scanner(
            new FileInputStream("employee.dat"), "UTF-8"))
      {
         Employee[] newStaff = readData(in);

         // print the newly read employee records
         for (Employee e : newStaff)
            System.out.println(e);
      }
   }

   /**
    * Writes all employees in an array to a print writer
    * @param employees an array of employees
    * @param out a print writer
    */
   private static void writeData(Employee[] employees, PrintWriter out) throws IOException
   {
      // write number of employees
      out.println(employees.length);

      for (Employee e : employees)
         writeEmployee(out, e);
   }

   /**
    * Reads an array of employees from a scanner
    * @param in the scanner
    * @return the array of employees
    */
   private static Employee[] readData(Scanner in)
   {
      // retrieve the array size
      int n = in.nextInt();
      in.nextLine(); // consume newline

      Employee[] employees = new Employee[n];
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
   public static void writeEmployee(PrintWriter out, Employee e)
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
   public static Employee readEmployee(Scanner in)
   {
      String line = in.nextLine();
      String[] tokens = line.split("\\|");
      String name = tokens[0];
      double salary = Double.parseDouble(tokens[1]);
      int year = Integer.parseInt(tokens[2]);
      int month = Integer.parseInt(tokens[3]);
      int day = Integer.parseInt(tokens[4]);
      return new Employee(name, salary, year, month, day);
   }   
}

/*-----------------------------------------------------------------------------------
 When saving data, you have the choice between binary and text formats. For  example, 
 if the integer 1234 is saved in binary, it is written as the sequence of bytes     -
 00 00 04 D2 (in hexadecimal notation). In text format, it is saved as the string   -
 "1234". Although binary I/O is fast and efficient, it is not easily readable by hum-
 ans. 

 When saving text strings, you need to consider the character encoding. In the UTF-16 
 encoding, the string "1234" is encoded as 00 31 00 32 00 33 00 34 (in hex).

 The OutputStreamWriter class turns a stream of Unicode code units into a stream of -
 bytes, using a chosen character encoding. Conversely,
the InputStreamReader class turns an input stream that contains bytes (specifying characters in some character encoding) into a reader that
emits Unicode code units.
For example, here is how you make an input reader that reads keystrokes from the console and converts them to Unicode:
InputStreamReader in = new InputStreamReader(System.in);
This input stream reader assumes the default character encoding used by the host system, such as the ISO 8859-1 encoding in Western Europe.
You can choose a different encoding by specifying it in the constructor for the InputStreamReader, for example:
InputStreamReader in = new InputStreamReader(new FileInputStream("kremlin.dat"), "ISO8859_5");
 ----------------------------------------------------------------------------------*/
