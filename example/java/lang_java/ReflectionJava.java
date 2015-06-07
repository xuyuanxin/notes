//package reflection;

import java.util.*;
import java.lang.reflect.*;

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
         if (modifiers.length() > 0) System.out.print(modifiers + " ");
         System.out.print("class " + name);
         if (supercl != null && supercl != Object.class) System.out.print(" extends "
               + supercl.getName());

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

   /**
    * Prints all constructors of a class
    * @param cl a class
    */
   public static void printConstructors(Class cl)
   {
      Constructor[] constructors = cl.getDeclaredConstructors();

      for (Constructor c : constructors)
      {
         String name = c.getName();
         System.out.print("   ");
         String modifiers = Modifier.toString(c.getModifiers());
         if (modifiers.length() > 0) System.out.print(modifiers + " ");         
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

   /**
    * Prints all methods of a class
    * @param cl a class
    */
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
         if (modifiers.length() > 0) System.out.print(modifiers + " ");         
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

   /**
    * Prints all fields of a class
    * @param cl a class
    */
   public static void printFields(Class cl)
   {
      Field[] fields = cl.getDeclaredFields();

      for (Field f : fields)
      {
         Class type = f.getType();
         String name = f.getName();
         System.out.print("   ");
         String modifiers = Modifier.toString(f.getModifiers());
         if (modifiers.length() > 0) System.out.print(modifiers + " ");         
         System.out.println(type.getName() + " " + name + ";");
      }
   }
}

/*-----------------------------------------------------------------------------------
 ----> reflection
 The reflection library gives you a very rich and elaborate toolset to write programs 
 that manipulate Java code dynamically. A program that can analyze the capabilities -
 of classes is called reflective. The reflection mechanism is extremely powerful.  As 
 the next sections show, you can use it to
 > Analyze the capabilities of classes at runtime;
 > Inspect objects at runtime, for example, to write a single toString method that w-
   orks for all classes;
 > Implement generic array manipulation code; and
 > Take advantage of Method objects that work just like function pointers in languag-
   es such as C++.
 Reflection is a powerful and complex mechanism; however, it is of interest mainly t-
 o tool builders, not application programmers. 


 java.lang.reflect.Field 1.1
 java.lang.reflect.Method 1.1
 java.lang.reflect.Constructor 1.1
 ? Class getDeclaringClass()
 returns the Class object for the class that defines this constructor, method, or field.
 ? Class[] getExceptionTypes() (in Constructor and Method classes)
 returns an array of Class objects that represent the types of the exceptions thrown by the
 method.
 ? int getModifiers()
 returns an integer that describes the modifiers of this constructor, method, or field. Use the
 methods in the Modifier class to analyze the return value.
 ? String getName()
 returns a string that is the name of the constructor, method, or field.
 ? Class[] getParameterTypes() (in Constructor and Method classes)
 returns an array of Class objects that represent the types of the parameters.
 ? Class getReturnType() (in Method classes)
 returns a Class object that represents the return type.
 java.lang.reflect.Modifier 1.1
 ? static String toString(int modifiers)
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
