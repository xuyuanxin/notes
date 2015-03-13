package abstractClasses;

/*
 you could implement Person.getDescription() to return an empty string . But there is 
 a better way. If you use the abstract keyword, you do not need to implement the met-
 hod at all. For added clarity, a class with one or more abstract methods must itself 
 be declared abstract. In addition to abstract methods, abstract classes can have fi-
 elds and concrete methods. For example, the Person class stores the name of the per-
 son and has a concrete method that returns it.

 When you extend an abstract class, you have two choices. You can leave some or all -
 of the abstract methods undefined; then you must tag the subclass as abstract as we-
 ll. Or you can define all methods, and the subclass is no longer abstract. For exam-
 ple, we will define a Student class that extends the abstract Person class and impl-
 ements the getDescription method. None of the methods of the Student class are abst-
 ract, so it does not need to be declared as an abstract class.

 A class can even be declared as abstract even though it has no abstract methods. Ab-
 stract classes cannot be instantiated. That is , if a class is declared as abstract,
 no objects of that class can be created. For example, the expression
     new Person("Vince Vu") //error
 Note that you can still create object variables of an abstract class, but such a va-
 riable must refer to an object of a nonabstract subclass. For example:
     Person p = new Student("Vince Vu", "Economics");
 Here p is a variable of the abstract type Person that refers to an instance of the -
 nonabstract subclass Student.


*/

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
