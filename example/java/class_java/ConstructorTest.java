import java.util.*;

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



/*-----------------------------------------------------------------------------------
 ----> Overloading
 Overloading occurs if several methods have the same name but different parameters. -
 The compiler must sort out which method to call. It picks the correct method by mat-
 ching the parameter types in the headers of the various methods with the types of t-
 he values used in the specific method call. A compile-time error occurs if the comp-
 iler cannot match the parameters or if more than one match is possible. (This proce-
 ss is called overloading resolution.)
 
 signature of the method
 Thus, to completely describe a method, you need to specify its name together with i-
 ts parameter types. This is called the signature of the method. For example, the St-
 ring class has four public methods called indexOf. They have signatures
     indexOf(int)
     indexOf(int, int)
     indexOf(String)
     indexOf(String, int)
 The return type is not part of the method signature. That is, you cannot have two m-
 ethods with the same names and parameter types but different return types.

 ----> Object Construction
 1 Default Field Initialization
 If you don't set a field explicitly in a constructor, it is automatically set to a -
 default value:numbers to 0,boolean values to false,and object references to null.

 2 The Constructor with No Arguments
 If you write a class with no constructors whatsoever, then a no-argument constructor 
 is provided for you . This constructor sets all the instance fields to their default 
 values. Please keep in mind that you get a free no-argument constructor only when y-
 our class has no other constructors. If a class supplies at least one constructor b-
 ut does not supply a no-argument constructor, it is illegal to construct objects wi-
 thout supplying arguments.

 3 Explicit Field Initialization
 It is always a good idea to make sure that, regardless of the constructor call, eve-
 ry instance field is set to something meaningful. You can simply assign a value to -
 any field in the class definition. For example:
     class Employee
     {
         private String name = "";
         . . .
     }
 This assignment is carried out before the constructor executes. This syntax is part-
 icularly useful if all constructors of a class need to set a particular instance fi-
 eld to the same value. The initialization value doesn't have to be a constant value. 
 Here is an example in which a field is initialized with a method call. Consider an -
 Employee class where each employee has an id field.You can initialize it as follows:
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

 4 Calling Another Constructor
 The keyword @this refers to the implicit parameter of a method. However, this keywo-
 rd has a second meaning. If the first statement of a constructor has the form      -
 this(. . .), then the constructor calls another constructor of the same class . Here 
 is a typical example:
	public Employee(double s)
	{
	   this("Employee #" + nextId, s); // calls Employee(String, double)
	   nextId++;
	}
 When you call new Employee(60000), the Employee(double) constructor calls the 
 Employee(String, double) constructor. Using the this keyword in this manner is usef-
 ul, you only need to write common construction code once.

 5 initialization block
 By assigning a value in the declaration There is a third mechanism in Java, called -
 an initialization block. Class declarations can contain arbitrary blocks of code. T-
 hese blocks are executed whenever an object of that class is constructed. The initi-
 alization block runs first, and then the body of the constructor is executed.

 If the static fields of your class require complex initialization code, use a static 
 initialization block. Place the code inside a block and tag it with the keyword sta-
 tic. Static initialization occurs when the class is first loaded. Like instance fie-
 lds, static fields are 0, false, or null unless you explicitly set them to another -
 value. All static field initializers and static initialization blocks are executed -
 in the order in which they occur in the class declaration. 

 Here is a Java trivia fact to amaze your fellow Java coders: You can write a "Hello, 
 World" program in Java without ever writing a main method.
	public class Hello
	{
	   static
	   {
	      System.out.println("Hello, World");
	   }
	}
 When you invoke the class with 
     java Hello
 the class is loaded, the static initialization block prints "Hello, World", and onl-
 y then do you get an ugly error message that main is not defined. You can avoid that 
 blemish by calling System.exit(0) at the end of the static initialization block.

 With so many ways of initializing data fields, it can be quite confusing to give all
 possible pathways for the construction process . Here is what happens in detail when 
 a constructor is called:
 1. All data fields are initialized to their default values (0, false, or null).
 2. All field initializers and initialization blocks are executed, in the order in w-
    hich they occur in the class declaration.
 3. If the first line of the constructor calls a second constructor, then the body of
    the second constructor is executed.
 4. The body of the constructor is executed.

 ----> Parameter Names
 When you write very trivial constructors (and you'll write a lot of them), it can be
 somewhat frustrating to come up with parameter names. We have generally opted for  -
 single-letter parameter names:
 public Employee(String n, double s)
     {
         name = n;
         salary = s;
     }
 However, the drawback is that you need to read the code to tell what the n and s pa-
 rameters mean. Some programmers prefix each parameter with an "a":
 public Employee(String aName, double aSalary)
     {
         name = aName;
         salary = aSalary;
     }
 That is quite neat. Any reader can immediately figure out the meaning of the parame-
 ters.
 Another commonly used trick relies on the fact that parameter variables shadow inst-
 ance fields with the same name. For example, if you call a parameter salary, then  -
 salary refers to the parameter, not the instance field. But you can still access the
 instance field as this.salary. Recall that this denotes the implicit parameter, that 
 is, the object that is being constructed. Here is an example:
 public Employee(String name, double salary)
 {
     this.name = name;
     this.salary = salary;
 }

 ----> Object Destruction and the finalize Method
 Since Java does automatic garbage collection, manual memory reclamation is not need-
 ed, so Java does not support destructors. Of course, some objects utilize a resource 
 other than memory, such as a file or a handle to another object that uses system re-
 sources. In this case, it is important that the resource be reclaimed and recycled -
 when it is no longer needed. You can add a finalize method to any class. The finali-
 ze method will be called before the garbage collector sweeps away the object. In pr-
 actice, do not rely on the finalize method for recycling any resources that are in -
 short supply you simply cannot know when this method will be called.
     protected void finalize( )
     {
         // finalization code here
     }
 ----------------------------------------------------------------------------------*/
