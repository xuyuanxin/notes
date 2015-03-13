package abstractClasses;

/**
 * This program demonstrates abstract classes.
 * @version 1.01 2004-02-21
 * @author Cay Horstmann
 */
public class PersonTest
{
   public static void main(String[] args)
   {
      Person[] people = new Person[2];

      // fill the people array with Student and Employee objects
      people[0] = new Employee("Harry Hacker", 50000, 1989, 10, 1);
      people[1] = new Student("Maria Morris", "computer science");

/*-----------------------------------------------------------------------------------
 Keep in mind that the variable p never refers to a Person object because it is impo-
 ssible to construct an object of the abstract Person class. The variable p always r-
 efers to an object of a concrete subclass such as Employee or Student. For these ob-
 jects, the getDescription method is defined. Could you have omitted the abstract me-
 thod altogether from the Person superclass, simply defining the getDescription meth-
 ods in the Employee and Student subclasses ? If you did that, then you wouldn't have 
 been able to invoke the getDescription method on the variable p. The compiler ensur-
 es that you invoke only methods that are declared in the class.
-----------------------------------------------------------------------------------*/
      // print out names and descriptions of all Person objects
      for (Person p : people)
         System.out.println(p.getName() + ", " + p.getDescription());
   }
}





/*
              +--------+
              | Person |
              +--------+
                  /|\
                   |
          +-----------------+
          |                 |
     +----------+       +---------+
     | Employee |       | Student |
     +----------+       +---------+


----> Protected Access
 Any features declared private won't be visible to other classes. this is also true -
 for subclasses: A subclass cannot access the private fields of its superclass. There 
 are times, however, when you want to restrict a method to subclasses only or, less -
 commonly, to allow subclass methods to access a superclass field. In that case , you 
 declare a class feature as protected.
 
 In practice, use protected fields with caution. Suppose your class is used  by other
 programmers and you designed it with protected fields. Unknown to you, other progra-
 mmers may inherit classes from your class and start accessing your protected fields. 
 In this case, you can no longer change the implementation of your class without ups-
 etting the other programmers. That is against the spirit of OOP, which encourages d-
 ata encapsulation.

----> Object: The Cosmic Superclass
 The Object class is the ultimate ancestor, every class in Java extends Object. Howe-
 ver, you never have to write
     class Employee extends Object
 The ultimate superclass Object is taken for granted if no superclass is explicitly -
 mentioned. You can use a variable of type Object to refer to objects of any type:
     Object obj = new Employee("Harry Hacker", 35000);
 Of course, a variable of type  Object is only useful as a generic holder for arbitr-
 ary values. To do anything specific with the value , you need to have some knowledge 
 about the original type and apply a cast:
     Employee e = (Employee) obj;
     
 In Java, only the primitive types ( numbers, characters, and boolean values) are not 
 objects.
 
 All array types, no matter whether they are arrays of objects or arrays of primitive 
 types, are class types that extend the Object class.
     Employee[] staff = new Employee[10];
     obj = staff; // OK
     obj = new int[10]; // OK
 
*/
