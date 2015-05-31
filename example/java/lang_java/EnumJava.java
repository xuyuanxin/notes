//package enums;

import java.util.*;

public class EnumJava
{  
   public static void main(String[] args)
   {  
      Scanner in = new Scanner(System.in);
      System.out.print("Enter a size: (SMALL, MEDIUM, LARGE, EXTRA_LARGE) ");
      String input = in.next().toUpperCase();
      Size size = Enum.valueOf(Size.class, input);
      System.out.println("size=" + size);
      System.out.println("abbreviation=" + size.getAbbreviation());
      if (size == Size.EXTRA_LARGE)
         System.out.println("Good job--you paid attention to the _.");      
   }
}

enum Size
{
   SMALL("S"), MEDIUM("M"), LARGE("L"), EXTRA_LARGE("XL");

   private Size(String abbreviation) { this.abbreviation = abbreviation; }
   public String getAbbreviation() { return abbreviation; }

   private String abbreviation;
}

/*-----------------------------------------------------------------------------------
 ----> Enumeration Classes
 Here is a typical example:
     public enum Size { SMALL, MEDIUM, LARGE, EXTRA_LARGE };
 You can, if you like, add constructors, methods, and fields to an enumerated type. 
     public enum Size
     {
         SMALL("S"), MEDIUM("M"), LARGE("L"), EXTRA_LARGE("XL");
         private String abbreviation;
         private Size(String abbreviation) { this.abbreviation = abbreviation; }
         public String getAbbreviation() { return abbreviation; }
     }
     
 All enumerated types are subclasses of the class Enum. They inherit a number of met-
 hods from that class. The most useful one is toString, which returns the name of the 
 enumerated constant. For example, Size.SMALL.toString() returns the string  "SMALL".
 The converse of toString is the static valueOf method. For example, the statement
     Size s = Enum.valueOf(Size.class, "SMALL");
 sets s to Size.SMALL.
 
 Each enumerated type has a static values method that returns an array of all  values 
 of the enumeration. For example, the call
     Size[] values = Size.values();
 returns the array with elements Size.SMALL, Size.MEDIUM, Size.LARGE, and Size.EXTRA_-
 LARGE. The @ordinal method yields the position of an enumerated constant in the  enum 
 declaration, counting from zero. For example, Size.MEDIUM.ordinal() returns 1.


 java.lang.Enum<E> 5.0

 static Enum valueOf(Class enumClass, String name)
 returns the enumerated constant of the given class with the given name.

 String toString()
 returns the name of this enumerated constant.

 int ordinal()
 returns the zero-based position of this enumerated constant in the enum declaration.

 int compareTo(E other)
 returns a negative integer if this enumerated constant comes before other, zero if this ==
 other, and a positive integer otherwise. The ordering of the constants is given by the enum
 declaration.

 ----------------------------------------------------------------------------------*/
