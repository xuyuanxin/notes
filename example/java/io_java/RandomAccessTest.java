//package randomAccess;

import java.io.*;
import java.util.*;

/*-----------------------------------------------------------------------------------
 Let us compute the size of each record. We will use 54 characters for the name stri-
 ngs. Therefore, each record contains 100 bytes:
     54 characters = 108 bytes for the name  16*6 + 12
     1 double = 8 bytes for the salary
     3 int = 12 bytes for the date
 ----------------------------------------------------------------------------------*/
public class RandomAccessTest
{  
   public static void main(String[] args) throws IOException
   {
      EmployeeRa[] staff = new EmployeeRa[3];

      staff[0] = new EmployeeRa("Carl Cracker", 75000, 1987, 12, 15); /* 0x7C3=1987  0xC=12 0xF=15*/
      staff[1] = new EmployeeRa("Harry Hacker", 50000, 1989, 10, 1);
      staff[2] = new EmployeeRa("Tony Tester", 40000, 1990, 3, 15);

      try (DataOutputStream out = new DataOutputStream(new FileOutputStream("employee.dat")))
      {  
         // save all employee records to the file employee.dat
         for (EmployeeRa e : staff)
            writeData(out, e);
      }
         
      try (RandomAccessFile in = new RandomAccessFile("employee.dat", "r"))
      {
         // retrieve all records into a new array
            
         // compute the array size
         int n = (int)(in.length() / EmployeeRa.RECORD_SIZE);
         EmployeeRa[] newStaff = new EmployeeRa[n];

         // read employees in reverse order
         for (int i = n - 1; i >= 0; i--)
         {  
            newStaff[i] = new EmployeeRa();
            in.seek(i * EmployeeRa.RECORD_SIZE);
            newStaff[i] = readData(in);
         }
         
         // print the newly read employee records
         for (EmployeeRa e : newStaff) 
            System.out.println(e);
      }
   }
   

   /**
      Writes employee data to a data output
      @param out the data output
      @param e the employee

 The @writeFixedString writes the specified number of code units, starting at the be-
 ginning of the string. If there are too few code units, the method pads the  string, 
 using zero values.      
   */
   public static void writeData(DataOutput out, EmployeeRa e) throws IOException
   {
      DataIO.writeFixedString(e.getName(), EmployeeRa.NAME_SIZE, out);
      out.writeDouble(e.getSalary());

      GregorianCalendar calendar = new GregorianCalendar();
      calendar.setTime(e.getHireDay());
      out.writeInt(calendar.get(Calendar.YEAR));
      out.writeInt(calendar.get(Calendar.MONTH) + 1);
      out.writeInt(calendar.get(Calendar.DAY_OF_MONTH));
   }

   /**
      Reads employee data from a data input
      @param in the data input
      @return the employee
   */
   public static EmployeeRa readData(DataInput in) throws IOException
   {      
      String name = DataIO.readFixedString(EmployeeRa.NAME_SIZE, in);
      double salary = in.readDouble();
      int y = in.readInt();
      int m = in.readInt();
      int d = in.readInt();
      return new EmployeeRa(name, salary, y, m - 1, d);
   }  
}