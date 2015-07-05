import java.text.DateFormatSymbols;
import java.util.*;

/*-----------------------------------------------------------------------------------
 If you want to see the program output in a different locale, add a line such as  the 
 following as the first line of the main method:
     Locale.setDefault(Locale.ITALY);
 ----------------------------------------------------------------------------------*/
public class CalendarTest
{
   public static void main(String[] args)
   {
      GregorianCalendar d = new GregorianCalendar(); // construct d as current date
 
      int today = d.get(Calendar.DAY_OF_MONTH);
      int month = d.get(Calendar.MONTH);

      d.set(Calendar.DAY_OF_MONTH, 1); // set d to start date of the month

      int weekday = d.get(Calendar.DAY_OF_WEEK);
      int firstDayOfWeek = d.getFirstDayOfWeek(); // get first day of week (Sunday in the U.S.)

      // determine the required indentation for the first line
      int indent = 0;
      while (weekday != firstDayOfWeek)
      {
         indent++;
         d.add(Calendar.DAY_OF_MONTH, -1);
         weekday = d.get(Calendar.DAY_OF_WEEK);
      }

      // print weekday names
      String[] weekdayNames = new DateFormatSymbols().getShortWeekdays();
      do
      {
         System.out.printf("%4s", weekdayNames[weekday]);
         d.add(Calendar.DAY_OF_MONTH, 1);
         weekday = d.get(Calendar.DAY_OF_WEEK);
      }
      while (weekday != firstDayOfWeek);
      System.out.println();

      for (int i = 1; i <= indent; i++)
         System.out.print("    ");

      d.set(Calendar.DAY_OF_MONTH, 1);
      do
      {
         // print day
         int day = d.get(Calendar.DAY_OF_MONTH);
         System.out.printf("%3d", day);

         // mark current day with *
         if (day == today) System.out.print("*");
         else System.out.print(" ");

         // advance d to the next day
         d.add(Calendar.DAY_OF_MONTH, 1);
         weekday = d.get(Calendar.DAY_OF_WEEK);

         // start a new line at the start of the week
         if (weekday == firstDayOfWeek) System.out.println();
      }
      while (d.get(Calendar.MONTH) == month);
      // the loop exits when d is day 1 of the next month

      // print final end of line if necessary
      if (weekday != firstDayOfWeek) System.out.println();
   }
}

/*-----------------------------------------------------------------------------------
 The library designers decided to separate the concerns of keeping time and attaching
 names to points in time. Therefore, the standard Java library contains two  separate
 classes: the Date class, which represents a point in time, and the GregorianCalendar
 class, which expresses dates in the familiar calendar notation. In fact, the       -
 GregorianCalendar class extends a more generic Calendar class that describes the pr-
 operties of calendars in general. 

 java.util.GregorianCalendar 1.1

 ----> GregorianCalendar()
 constructs a calendar object that represents the current time in the default time z-
 one with the default locale.
 
 GregorianCalendar(int year, int month, int day)
 GregorianCalendar(int year, int month, int day, int hour, int minutes,int seconds)
 constructs a Gregorian calendar with the given date and time.

 @month: the month of the data, 0-based(for example, 0 is january)
 
 ----> int get(int field)
 gets the value of a particular field.

 @field: one of Calendar.ERA, Calendar.YEAR, Calendar.MONTH, Calendar.WEEK_OF_YEAR,
 Calendar.WEEK_OF_MONTH, Calendar.DAY_OF_MONTH, Calendar.DAY_OF_YEAR, 
 Calendar.DAY_OF_WEEK, Calendar.DAY_OF_WEEK_IN_MONTH, Calendar.AM_PM, Calendar.HOUR,
 Calendar.HOUR_OF_DAY, Calendar.MINUTE, Calendar.SECOND, Calendar.MILLISECOND,
 Calendar.ZONE_OFFSET, Calendar.DST_OFFSET

 ----> void set(int field, int value)
 sets the value of a particular field.
 
 ----> void set(int year, int month, int day)
 ----> void set(int year, int month, int day, int hour, int minutes, int seconds)
 sets the fields to new values.
 
 ----> void add(int field, int amount)
 is a date arithmetic method. Adds the specified amount of time to the given time fi-
 eld. For example, to add 7 days to the current calendar date, call
     c.add(Calendar.DAY_OF_MONTH, 7).

 ----> int getFirstDayOfWeek()
 gets the first day of the week in the locale of the current user, for example
     Calendar.SUNDAY 
 in the United States.
 
 ----> void setTime(Date time)
 sets this calendar to the given point in time.
 
 ----> Date getTime()
 gets the point in time that is represented by the current value of this calendar ob-
 ject.


 java.text.DateFormatSymbols 1.1
 
 String[] getShortWeekdays()
 String[] getShortMonths()
 String[] getWeekdays()
 String[] getMonths()
 gets the names of the weekdays or months in the current locale. Uses Calendar weekd-
 ay and month constants as array index values. 
 ----------------------------------------------------------------------------------*/
