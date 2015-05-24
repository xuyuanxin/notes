//package abstractClasses;

/*-----------------------------------------------------------------------------------
 The program defines the abstract superclass Person and two concrete subclasses, Emp-
 loyee and Student. We fill an array of Person references with employee and student -
 objects:
     Person[] people = new Person[2];
     people[0] = new Employee(. . .);
     people[1] = new Student(. . .);
 We then print the names and descriptions of these objects:
     for (Person p : people)
         System.out.println(p.getName() + ", " + p.getDescription());
 Some people are baffled by the call
     p.getDescription()
 Isn't this a call to an undefined method? Keep in mind that the variable p never re-
 fers to a Person object because it is impossible to construct an object of the abst-
 ract Person class. The variable p always refers to an object of a concrete  subclass 
 such as Employee or Student. For these objects,the getDescription method is defined.

 Could you have omitted the abstract method altogether from the Person superclass, s-
 imply defining the getDescription methods in the Employee and Student subclasses? I-
 f you did that, then you wouldn't have been able to invoke the getDescription method 
 on the variable p. The compiler ensures that you invoke only methods that are decla-
 red in the class.
 ----------------------------------------------------------------------------------*/
public class PersonTest
{
   public static void main(String[] args)
   {
      Person[] people = new Person[2];

      // fill the people array with Student and Employee objects
      people[0] = new Employee("Harry Hacker", 50000, 1989, 10, 1);
      people[1] = new Student("Maria Morris", "computer science");

      // print out names and descriptions of all Person objects
      for (Person p : people)
         System.out.println(p.getName() + ", " + p.getDescription());
   }
}






