/*-----------------------------------------------------------------------------------
 ----> The @Class Class
 While your program is running, the Java runtime system always maintains what is cal-
 led runtime type identification on all objects. This information keeps track of  the 
 class to which each object belongs. Runtime type information is used by the  virtual 
 machine to select the correct methods to execute. However, you can also access  this 
 information by working with a special Java class. The class that holds this informa-
 tion is called, somewhat confusingly, @Class.

 getClass()
 The getClass() method in the @Object class returns an instance of @Class type.
     Employee e;
     . . .
     Class cl = e.getClass();
 Just like an Employee object describes the properties of a particular employee, a  -
 @Class object describes the properties of a particular class. 

 @getName
 This returns the name of the class. For example, the statement
     System.out.println(e.getClass().getName() + " " + e.getName());
 prints
     Employee Harry Hacker
 if e is an employee, or
     Manager Harry Hacker
 if e is a manager.
 If the class is in a package, the package name is part of the class name:
     Date d = new Date();
     Class cl = d.getClass();
     String name = cl.getName(); // name is set to "java.util.Date"

 If T is any Java type, then T.class is the matching class object. For example:
     Class cl1 = Date.class; // if you import java.util.*;
     Class cl2 = int.class;
     Class cl3 = Double[].class;
 Note that a @Class object really describes a type, which may or may not be a  class. 
 For example, int is not a class, but int.class is nevertheless an object of type   -
 @Class. For historical reasons, the @getName method returns somewhat strange names -
 for array types:
     Double[].class.getName() //returns "[Ljava.lang.Double"; 
     int[].class.getName()    //returns "[I"
 ------------------------------------------------------------------------------------
 java.lang.Class 1.0

 ----> static Class forName(String className)
 returns the Class object representing the class with name className. You can  obtain 
 a @Class object corresponding to a class name by using the static @forName method.
     String className = "java.util.Date";
     Class cl = Class.forName(className);
 The virtual machine manages a unique @Class object for each type. Therefore, you can 
 use the == operator to compare class objects. For example:
     if (e.getClass() == Employee.class) . . .
 ----> Object newInstance()
 returns a new instance of this class.
     e.getClass().newInstance();
 creates a new instance of the same class type as e. The newInstance method calls the 
 no-argument constructor to initialize the newly created object. An exception is thr-
 own if the class does not have a noargument constructor. 
 ----> Field[] getFields() 1.1
       Field[] getDeclaredFields() 1.1
 @getFields returns an array containing Field objects for the public fields of this c-
 lass or its superclasses; @getDeclaredField returns an array of Field objects for all 
 fields of this class. The methods return an array of length 0 if there are no such f-
 ields or if the Class object represents a primitive or array type.
 ----> Method[] getMethods() 1.1
       Method[] getDeclaredMethods() 1.1
 returns an array containing Method objects: getMethods returns public methods and i-
 ncludes inherited methods; getDeclaredMethods returns all methods of this class or -
 interface but does not include inherited methods.
 ----> Constructor[] getConstructors() 1.1
       Constructor[] getDeclaredConstructors() 1.1
 returns an array containing Constructor objects that give you all the public constr-
 uctors (for getConstructors) or all constructors (for getDeclaredConstructors) of t-
 he class represented by this Class object.
 ----------------------------------------------------------------------------------*/
