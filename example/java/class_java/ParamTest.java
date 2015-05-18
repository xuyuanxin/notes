
public class ParamTest
{
   public static void main(String[] args)
   {
      /*
       * Test 1: Methods can't modify numeric parameters
       */
      System.out.println("Testing tripleValue:");
      double percent = 10;
      System.out.println("Before: percent=" + percent);
      tripleValue(percent);
      System.out.println("After: percent=" + percent);

      /*
       * Test 2: Methods can change the state of object parameters
       */
      System.out.println("\nTesting tripleSalary:");
      Employee harry = new Employee("Harry", 50000);
      System.out.println("Before: salary=" + harry.getSalary());
      tripleSalary(harry);
      System.out.println("After: salary=" + harry.getSalary());

      /*
       * Test 3: Methods can't attach new objects to object parameters
       */
      System.out.println("\nTesting swap:");
      Employee a = new Employee("Alice", 70000);
      Employee b = new Employee("Bob", 60000);
      System.out.println("Before: a=" + a.getName());
      System.out.println("Before: b=" + b.getName());
      swap(a, b);
      System.out.println("After: a=" + a.getName());
      System.out.println("After: b=" + b.getName());
   }

   public static void tripleValue(double x) // doesn't work
   {
      x = 3 * x;
      System.out.println("End of method: x=" + x);
   }
   public static void tripleSalary(Employee x) // works
   {
      x.raiseSalary(200);
      System.out.println("End of method: salary=" + x.getSalary());
   }

   public static void swap(Employee x, Employee y)
   {
      Employee temp = x;
      x = y;
      y = temp;
      System.out.println("End of method: x=" + x.getName());
      System.out.println("End of method: y=" + y.getName());
   }
}

class Employee // simplified Employee class
{
   private String name;
   private double salary;

   public Employee(String n, double s)
   {
      name = n;
      salary = s;
   }

   public String getName()
   {
      return name;
   }

   public double getSalary()
   {
      return salary;
   }

   public void raiseSalary(double byPercent)
   {
      double raise = salary * byPercent / 100;
      salary += raise;
   }
}



/*-----------------------------------------------------------------------------------
 ----> call by value, call by reference
 Let us review the computer science terms that describe how parameters can be  passed 
 to a method (or a function) in a programming language . The term call by value means 
 that the method gets just the value that the caller provides. In contrast, call by -
 reference means that the method gets the location of the variable that the caller p-
 rovides. Thus,a method can modify the value stored in a variable passed by reference
 but not in one passed by value.
 
 The Java programming language always uses call by value . That means that the method 
 gets a copy of all parameter values. In particular, the method cannot modify the co-
 ntents of any parameter variables passed to it. For example , consider the following 
 call:
     double percent = 10;
     harry.raiseSalary(percent);
 No matter how the method is implemented, we know that after the method call, the va-
 lue of percent is still 10. Let us look a little more closely at this situation. Su-
 ppose a method tried to triple the value of a method parameter:
     public static void tripleValue(double x) // doesn't work
     {
         x = 3 * x;
     }
 Let's call this method:
     double percent = 10;
     tripleValue(percent);
 However, this does not work. After the method call,the value of percent is still 10.
 Here is what happens:
 1. x is initialized with a copy of the value of percent (that is, 10).
 2. x is tripled. it is now 30. But percent is still 10 .
 3. The method ends, and the parameter variable x is no longer in use.

 There are, however, two kinds of method parameters: Primitive types (numbers, boole-
 an values), Object references. You have seen that it is impossible for a method to -
 change a primitive type parameter. The situation is different for object parameters. 
 You can easily implement a method that triples the salary of an employee:
     public static void tripleSalary(Employee x) // works
     {
         x.raiseSalary(200);
     }
 When you call
     harry = new Employee(. . .);
     tripleSalary(harry);
 then the following happens:
 1. x is initialized with a copy of the value of harry, that is, an object reference.
 2. The raiseSalary method is applied to that object reference. The Employee object -
    to which both x and harry refer gets its salary raised by 200 percent.
 3. The method ends, and the parameter variable x is no longer in use. Of course, th-
    e object variable harry continues to refer to the object whose salary was tripled.
 The reason is simple. The method gets a copy of the object reference, and both the -
 original and the copy refer to the same object.

 Let's try to write a method that swaps two employee objects:
     public static void swap(Employee x, Employee y) // doesn't work
     {
         Employee temp = x;
         x = y;
         y = temp;
     }
 If the Java programming language used call by reference for objects, this method wo-
 uld work:
     Employee a = new Employee("Alice", . . .);
     Employee b = new Employee("Bob", . . .);
     swap(a, b);
     // does a now refer to Bob, b to Alice?
 However, the method does not actually change the object references that are stored -
 in the variables a and b . The x and y parameters of the swap method are initialized 
 with copies of these references. The method then proceeds to swap these copies.
     // x refers to Alice, y to Bob
     Employee temp = x;
     x = y;
     y = temp;
     // now x refers to Bob, y to Alice
 But ultimately, this is a wasted effort. When the method ends, the parameter variab-
 les x and y are abandoned. The original variables a and b still refer to the same o-
 bjects as they did before the method call.

 This demonstrates that the Java programming language  does not use call by reference 
 for objects. Instead, object references are passed by value.

 Here is a summary of what you can and cannot do with method parameters in Java:
 1. A method cannot modify a parameter of a primitive type (that is, numbers or bool-
    ean values).
 2. A method can change the state of an object parameter.
 3. A method cannot make an object parameter refer to a new object.
 ----------------------------------------------------------------------------------*/
