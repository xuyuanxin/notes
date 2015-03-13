import java.util.*;

/**
 * This program demonstrates object construction.
 * @version 1.01 2004-02-19
 * @author Cay Horstmann
 */
public class ConstructorTest
{
   public static void main(String[] args)
   {
      // fill the staff array with three Employee objects
      Employee[] staff = new Employee[3];

      staff[0] = new Employee("Harry", 40000);
      staff[1] = new Employee(60000);
      staff[2] = new Employee();

      // print out information about all Employee objects
      for (Employee e : staff)
         System.out.println("name=" + e.getName() + ",id=" + e.getId() + ",salary="
               + e.getSalary());
   }
}

class Employee
{
   private static int nextId;

   private int id;
   private String name = ""; // instance field initialization
   private double salary;


/*
initialization block
    By assigning a value in the declaration There is a third mechanism in Java,called 
    an initialization block. Class declarations can contain arbitrary blocks of code. 
    These blocks are executed whenever an object of that class is constructed. The i-
    nitialization block runs first, and then the body of the constructor is executed.

    If the static fields of your class require complex initialization code, use a st-
    atic initialization block. Place the code inside a block and tag it with the key-
    word static. Static initialization occurs when the class is first loaded. Like i-
    nstance fields, static fields are 0, false, or null unless you explicitly set th-
    em to another value. All static field initializers and static initialization blo-
    cks are executed in the order in which they occur in the class declaration. 

    Here is a Java trivia fact to amaze your fellow Java coders: You can write a "He-
    llo, World" program in Java without ever writing a main method.
				public class Hello
				{
				   static
				   {
				      System.out.println("Hello, World");
				   }
				}
    When you invoke the class with java Hello, the class is loaded, the static initi-
    alization block prints "Hello, World", and only then do you get an ugly error me-
    ssage that main is not defined. You can avoid that blemish by calling System.exit(0) 
    at the end of the static initialization block.
*/
  
   // static initialization block
   static
   {
      Random generator = new Random();
      // set nextId to a random number between 0 and 9999
      nextId = generator.nextInt(10000);
   }

   // object initialization block
   {
      id = nextId;
      nextId++;
   }

   // three overloaded constructors
   public Employee(String n, double s)
   {
      name = n;
      salary = s;
   }

   public Employee(double s)
   {
      // calls the Employee(String, double) constructor
      this("Employee #" + nextId, s);
   }

   // the default constructor
   public Employee()
   {
      // name initialized to ""--see above
      // salary not explicitly set--initialized to 0
      // id initialized in initialization block
   }

   public String getName()
   {
      return name;
   }

   public double getSalary()
   {
      return salary;
   }

   public int getId()
   {
      return id;
   }
}



/*
Overloading
    Overloading occurs if several methods have the same name but different parameter-
    s. The compiler must sort out which method to call. It picks the correct method -
    by matching the parameter types in the headers of the various methods with the t-
    ypes of the values used in the specific method call . A compile-time error occurs  
    if the compiler cannot match the parameters or if more than one match is possible. 
    (This process is called overloading resolution.)
signature of the method
    Thus, to completely describe a method, you need to specify its name together with  
    its parameter types. This is called the signature of the method. For example, the 
    String class has four public methods called indexOf. They have signatures
				indexOf(int)
				indexOf(int, int)
				indexOf(String)
				indexOf(String, int)
    The return type is not part of the method signature. That is, you cannot have two 
    methods with the same names and parameter types but different return types.

Object Construction
1 Default Field Initialization
    If you don't set a field explicitly in a constructor , it is automatically set to 
    a default value:numbers to 0,boolean values to false,and object references to null.
2 The Constructor with No Arguments
    If you write a class with no constructors whatsoever, then a no-argument constru-
    ctor is provided for you . This constructor sets all the instance fields to their 
    default values. Please keep in mind that you get a free no-argument constructor -
    only when your class has no other constructors . If a class supplies at least one 
    constructor but does not supply a no-argument constructor, it is illegal to cons-
    truct objects without supplying arguments.
3 Explicit Field Initialization
    It is always a good idea to make sure that, regardless of the constructor call, -
    every instance field is set to something meaningful. You can simply assign a val-
    ue to any field in the class definition. For example:
				class Employee
				{
				   private String name = "";
				   . . .
				}
    This assignment is carried out before the constructor executes. This syntax is p-
    articularly useful if all constructors of a class need to set a particular insta-
    nce field to the same value. The initialization value doesn't have to be a const-
    ant value. Here is an example in which a field is initialized with a method call. 
    Consider an Employee class where each employee has an id field. You can initiali-
    ze it as follows:
				class Employee
				{
				   private static int nextId;
				   private int id = assignId();
				   . . .
				   private static int assignId()
				   {
				      int r = nextId;
				      nextId++;
				      return r;
				   }
				   . . .
				}
4  Calling Another Constructor
    The keyword this refers to the implicit parameter of a method. However, this key-
    word  has  a second meaning. If the first statement of a constructor has the form 
    this(. . .), then the constructor calls another constructor of the same class. H-
    ere is a typical example:
				public Employee(double s)
				{
				   // calls Employee(String, double)
				   this("Employee #" + nextId, s);
				   nextId++;
				}
    When you call new Employee(60000), the Employee(double) constructor calls the
    Employee(String, double) constructor. Using the this keyword in this manner is u-
    seful, you only need to write common construction code once.

Object Destruction and the finalize Method
    Since Java does automatic garbage collection, manual memory reclamation is not n-
    eeded, so Java does not support destructors. Of course, some objects utilize a r-
    esource other than memory, such as a file or a handle to another object that uses  
    system  resources. In this case, it is important that the resource be reclaimed -
    and recycled when it is no longer needed. You can add a finalize method to any c-
    lass. The finalize method will be called before the garbage collector sweeps away  
    the object. In practice, do not rely on the finalize method for recycling any re-
    sources that are  in short supply you simply cannot know when this method will be
    called.

Final Instance Fields
    You can define an instance field as final. Such a field must be initialized  when 
    the object is constructed. That is, you must guarantee that the field value has -
    been set after the end of every constructor. Afterwards, the field may not be mo-
    dified again. For example, the name field of the Employee class may be declared -
    as final because it never changes after the object is constructed.
            class Employee
            {
                   private final String name;
                   . . .
            }
    The final modifier is particularly useful for fields whose type is primitive or -
    an immutable class. ( A class is immutable if none of its methods ever mutate its 
    objects. For example, the String class is immutable.) For mutable classes, the f-
    inal modifier is likely to confuse the reader. For example,
            private final Date hiredate;
    merely means that the object reference stored in the hiredate variable doesn't g-
    et changed after the object is constructed . That does not mean that the hiredate 
    object is constant.Any method is free to invoke the setTime mutator on the object 
    to which hiredate refers.


*/
