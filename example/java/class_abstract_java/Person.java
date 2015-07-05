//package abstractClasses;

public abstract class Person
{
   public abstract String getDescription();
   private String name;

   public Person(String n)
   {
      name = n;
   }

   public String getName()
   {
      return name;
   }
}



/*-----------------------------------------------------------------------------------
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

 As you move up the inheritance hierarchy, classes become more general and probably -
 more abstract. for example, an extension of our Employee class hierarchy. An employ-
 ee is a person, and so is a student. Let us extend our class hierarchy to include c-
 lasses Person and Student.

 The Person class knows nothing about the person except the name. Of course, you cou-
 ld implement Person.getDescription() to return an empty string. But there is a bett-
 er way. If you use the abstract keyword, you do not need to implement the method  at 
 all.
     public abstract String getDescription(); // no implementation required
 For added clarity, a class with one or more abstract methods must itself be declared 
 abstract.
     abstract class Person
     { 
         . . .
         public abstract String getDescription();
     }
 In addition to abstract methods, abstract classes can have fields and concrete meth-
 ods. For example, the Person class stores the name of the person and has a  concrete 
 method that returns it.

 When you extend an abstract class, you have two choices. You can leave some or all -
 of the abstract methods undefined ; then you must tag the subclass as abstract as w-
 ell. Or you can define all methods, and the subclass is no longer abstract. For exa-
 mple, we will define a Student class that extends the abstract Person class and imp-
 lements the getDescription method. None of the methods of the Student class are abs-
 tract, so it does not need to be declared as an abstract class. 

 A class can even  be declared as abstract even though it has no abstract methods. A-
 bstract classes cannot be instantiated. That is, if a class is declared as abstract,
 no objects of that class can be created. For example, the expression
     new Person("Vince Vu")
 is an error. However, you can create objects of concrete subclasses. Note that you -
 can still create object variables of an abstract class, but such a variable must re-
 fer to an object of a nonabstract subclass. For example:
     Person p = new Student("Vince Vu", "Economics");
 Here p is a variable of the abstract type Person that refers to an instance of the -
 nonabstract subclass Student.

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

 Here is a summary of the four access modifiers in Java that control visibility:
 1. Visible to the class only (private).
 2. Visible to the world (public).
 3. Visible to the package and all subclasses (protected).
 4. Visible to the package¡ªthe (unfortunate) default. No modifiers are needed.


 -----------------------------------------------------------------------------------*/

