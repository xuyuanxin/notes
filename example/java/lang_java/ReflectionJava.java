//package reflection;

import java.util.*;
import java.lang.reflect.*;

/*-----------------------------------------------------------------------------------
 F:\mygit\notes\example\java\lang_java>javac ReflectionJava.java
 F:\mygit\notes\example\java\lang_java>java ReflectionJava
 Enter class name (e.g. java.util.Date):
 java.util.Date

 public class java.util.Date
 {
   public java.util.Date(java.lang.String);
   public java.util.Date(int, int, int, int, int, int);
   public java.util.Date(int, int, int, int, int);
   public java.util.Date();
   public java.util.Date(long);
   public java.util.Date(int, int, int);

   public boolean equals(java.lang.Object);
   public java.lang.String toString();
   public int hashCode();
   public java.lang.Object clone();
   public int compareTo(java.util.Date);
   public volatile int compareTo(java.lang.Object);
   private void readObject(java.io.ObjectInputStream);
   private void writeObject(java.io.ObjectOutputStream);
   private final sun.util.calendar.BaseCalendar$Date normalize(sun.util.calendar.BaseCalendar$Date);
   private final sun.util.calendar.BaseCalendar$Date normalize();
   public static long parse(java.lang.String);
   public boolean after(java.util.Date);
   public boolean before(java.util.Date);
   public int getDate();
   public long getTime();
   public static java.util.Date from(java.time.Instant);
   public void setTime(long);
   public int getHours();
   public int getMinutes();
   public int getMonth();
   public int getSeconds();
   public int getYear();
   public static long UTC(int, int, int, int, int, int);
   private static final java.lang.StringBuilder convertToAbbr(java.lang.StringBuilder, java.lang.String);
   private final sun.util.calendar.BaseCalendar$Date getCalendarDate();
   private static final sun.util.calendar.BaseCalendar getCalendarSystem(long);
   private static final sun.util.calendar.BaseCalendar getCalendarSystem(int);
   private static final sun.util.calendar.BaseCalendar getCalendarSystem(sun.util.calendar.BaseCalendar$Date);
   public int getDay();
   private static final synchronized sun.util.calendar.BaseCalendar getJulianCalendar();
   static final long getMillisOf(java.util.Date);
   private final long getTimeImpl();
   public int getTimezoneOffset();
   public void setDate(int);
   public void setHours(int);
   public void setMinutes(int);
   public void setMonth(int);
   public void setSeconds(int);
   public void setYear(int);
   public java.lang.String toGMTString();
   public java.time.Instant toInstant();
   public java.lang.String toLocaleString();

   private static final sun.util.calendar.BaseCalendar gcal;
   private static sun.util.calendar.BaseCalendar jcal;
   private transient long fastTime;
   private transient sun.util.calendar.BaseCalendar$Date cdate;
   private static int defaultCenturyStart;
   private static final long serialVersionUID;
   private static final [Ljava.lang.String; wtb;
   private static final [I ttb;
 }
 
 ----> Using Reflection to Analyze the Capabilities of Classes 
 Here is a brief overview of the most important parts of the reflection mechanism for 
 letting you examine the structure of a class.
 The three classes @Field, @Method, and @Constructor in the java.lang.reflect package 
 describe the fields, methods, and constructors of a class, respectively. All three -
 classes have a method called @getName that returns the name of the item. The  @Field 
 class has a method @getType that returns an object, again of type @Class, that desc-
 ribes the field type. The @Method and @Constructor classes have methods to report t-
 he types of the parameters, and the @Method class also reports the return type.  All 
 three of these classes also have a method called @getModifiers that returns an inte-
 ger, with various bits turned on and off, that describes the modifiers used, such as 
 public and static. You can then use the static methods in the @Modifier class in the 
 java.lang.reflect package to analyze the integer that @getModifiers returns. Use me-
 thods like @isPublic, @isPrivate, or @isFinal in the @Modifier class to tell whether 
 a method or constructor was public, private, or final. All you have to do is have t-
 he appropriate method in the @Modifier class work on the integer that  @getModifiers 
 returns. You can also use the Modifier.toString method to print the modifiers.
 ----------------------------------------------------------------------------------*/
public class ReflectionJava
{
   public static void main(String[] args)
   {
      // read class name from command line args or user input
      String name;
      if (args.length > 0) name = args[0];
      else
      {
         Scanner in = new Scanner(System.in);
         System.out.println("Enter class name (e.g. java.util.Date): ");
         name = in.next();
      }

      try
      {
         // print class name and superclass name (if != Object)
         Class cl = Class.forName(name);
         Class supercl = cl.getSuperclass();
         String modifiers = Modifier.toString(cl.getModifiers());
		 
         if (modifiers.length() > 0) 
		 	System.out.print(modifiers + " ");
		 
         System.out.print("class " + name);
		 
         if (supercl != null && supercl != Object.class) 
		 	System.out.print(" extends " + supercl.getName());

         System.out.print("\n{\n");
         printConstructors(cl);
         System.out.println();
		 
         printMethods(cl);
         System.out.println();
		 
         printFields(cl);
         System.out.println("}");
      }
      catch (ClassNotFoundException e)
      {
         e.printStackTrace();
      }
      System.exit(0);
   }

   /* Prints all constructors of a class */
   public static void printConstructors(Class cl)
   {
      Constructor[] constructors = cl.getDeclaredConstructors();

      for (Constructor c : constructors)
      {
         String name = c.getName();
         System.out.print("   ");
		 
         String modifiers = Modifier.toString(c.getModifiers());
		 
         if (modifiers.length() > 0) 
		 	System.out.print(modifiers + " "); 
		 
         System.out.print(name + "(");

         // print parameter types
         Class[] paramTypes = c.getParameterTypes();
         for (int j = 0; j < paramTypes.length; j++)
         {
            if (j > 0) System.out.print(", ");
            System.out.print(paramTypes[j].getName());
         }
		 
         System.out.println(");");
      }
   }

   /* Prints all methods of a class */
   public static void printMethods(Class cl)
   {
      Method[] methods = cl.getDeclaredMethods();

      for (Method m : methods)
      {
         Class retType = m.getReturnType();
         String name = m.getName();

         System.out.print("   ");
         // print modifiers, return type and method name
         String modifiers = Modifier.toString(m.getModifiers());
		 
         if (modifiers.length() > 0) 
		 	System.out.print(modifiers + " "); 
		 
         System.out.print(retType.getName() + " " + name + "(");

         // print parameter types
         Class[] paramTypes = m.getParameterTypes();
         for (int j = 0; j < paramTypes.length; j++)
         {
            if (j > 0) System.out.print(", ");
            System.out.print(paramTypes[j].getName());
         }
         System.out.println(");");
      }
   }

   /* Prints all fields of a class */
   public static void printFields(Class cl)
   {
      Field[] fields = cl.getDeclaredFields();

      for (Field f : fields)
      {
         Class type = f.getType();
         String name = f.getName();
         System.out.print("   ");
         String modifiers = Modifier.toString(f.getModifiers());
         if (modifiers.length() > 0) 
		 	System.out.print(modifiers + " ");
		 
         System.out.println(type.getName() + " " + name + ";");
      }
   }
}

/*-----------------------------------------------------------------------------------
 ----> reflection
 A program that can analyze the capabilities of classes is called reflective. The re-
 flection mechanism is extremely powerful.  As the next sections show, you can use it 
 to
 > Analyze the capabilities of classes at runtime;
 > Inspect objects at runtime, for example, to write a single toString method that w-
   orks for all classes;
 > Implement generic array manipulation code; and
 > Take advantage of Method objects that work just like function pointers in languag-
   es such as C++.
 Reflection is a powerful and complex mechanism; however, it is of interest mainly t-
 o tool builders, not application programmers.
 
 -----------------------------------------------------------------------------------
 java.lang.reflect.Field 1.1
 java.lang.reflect.Method 1.1
 java.lang.reflect.Constructor 1.1
 ----> Class getDeclaringClass()
 returns the @Class object for the class that defines this constructor, method, or f-
 ield.
 ----> Class[] getExceptionTypes() (in Constructor and Method classes)
 returns an array of Class objects that represent the types of the exceptions  thrown 
 by the method.
 ----> int getModifiers()
 returns an integer that describes the modifiers of this constructor, method, or fie-
 ld. Use the methods in the @Modifier class to analyze the return value.
 ----> String getName()
 returns a string that is the name of the constructor, method, or field.
 ----> Class[] getParameterTypes() (in Constructor and Method classes)
 returns an array of Class objects that represent the types of the parameters.
 ----> Class getReturnType() (in Method classes)
 returns a Class object that represents the return type.
 -----------------------------------------------------------------------------------
 java.lang.reflect.Modifier 1.1
 ----> static String toString(int modifiers)
 returns a string with the modifiers that correspond to the bits set in modifiers.
 
 ? static boolean isAbstract(int modifiers)
 ? static boolean isFinal(int modifiers)
 ? static boolean isInterface(int modifiers)
 ? static boolean isNative(int modifiers)
 ? static boolean isPrivate(int modifiers)
 ? static boolean isProtected(int modifiers)
 ? static boolean isPublic(int modifiers)
 ? static boolean isStatic(int modifiers)
 ? static boolean isStrict(int modifiers)
 ? static boolean isSynchronized(int modifiers)
 ? static boolean isVolatile(int modifiers)
 tests the bit in the modifiers value that corresponds to the modifier in the method name.
 ----------------------------------------------------------------------------------*/
