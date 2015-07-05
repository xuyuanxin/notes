//package inheritance;

/*-----------------------------------------------------------------------------------
 ----> Classes, Superclasses, and Subclasses
 ----> keyword extends 
 The keyword extends indicates that you are making a new class that derives from an -
 existing class. The existing class is called the superclass, base class, or parent -
 class. The new class is called the subclass, derived class, or child class. The ter-
 ms superclass and subclass are those most commonly used by Java programmers.
 
 a subclass can add fields, and it can add methods or override the methods of the su-
 perclass. However, inheritance can never take away any fields or methods.

 ----> Manager
 you can use methods such as getName and getHireDay with Manager objects. Even though 
 these methods are not explicitly defined in the Manager class, they are automatical-
 ly inherited from the Employee superclass. Similarly, the fields name, salary, and -
 hireDay are taken from the superclass. Every Manager object has four fields: name, -
 salary, hireDay, and bonus.
-----------------------------------------------------------------------------------*/
public class ManagerJi extends EmployeeJi
{
   private double bonus;

/*-----------------------------------------------------------------------------------
 Here, the keyword super has a different meaning. The instruction
     super(n, s, year, month, day);
 is shorthand for "call the constructor of the Employee superclass with n, s, year, -
 month, and day as parameters." Since the Manager constructor cannot access the priv-
 ate fields of the Employee class, it must initialize them through a constructor. The 
 constructor is invoked with the special super syntax. The call using super must be -
 the first statement in the constructor for the subclass.

 If the subclass constructor does not call a superclass constructor explicitly, the -
 no-argument constructor of the superclass is invoked. If the superclass does not ha-
 ve a no-argument constructor and the subclass constructor does not call another sup-
 erclass constructor explicitly, the Java compiler reports an error.
 ----------------------------------------------------------------------------------*/
   public ManagerJi(String n, double s, int year, int month, int day)
   {
      super(n, s, year, month, day);
      bonus = 0;
   }

/*-----------------------------------------------------------------------------------
 However, some of the superclass methods are not appropriate for the Manager subclass. 
 In particular, the getSalary method should return the sum of the base salary and the 
 bonus. You need to supply a new method to override the superclass method:

 At first glance, it appears to be simple,just return the sum of the salary and bonus 
 fields:
         public double getSalary()
         {
             return salary + bonus; // won't work
         }
 However, that won't work. The getSalary method of the Manager class has no direct a-
 ccess to the private fields of the superclass . This means that the getSalary method 
 of the Manager class cannot directly access the salary field, even though every Man-
 ager object has a field called salary. Only the methods of the Employee class have -
 access to the private fields. If the Manager methods want to access those private f-
 ields, they have to do what every other method does, use the public interface, in t-
 his case, the public getSalary method of the Employee class. So, let's try this aga-
 in. You need to call getSalary instead of simply accessing the salary field.
		 public double getSalary()
		 {
		    double baseSalary = getSalary(); // still won't work
		    return baseSalary + bonus;
		 }
 The problem is that the call to getSalary simply calls itself, because the Manager -
 class has a getSalary method (namely, the method we are trying to implement). The c-
 onsequence is an infinite chain of calls to the same method, leading to a program c-
 rash. We need to indicate that we  want to call the getSalary method of the Employee
 super-class, not the current class. You use the special keyword super for this purp-
 ose. The call
         super.getSalary()
 calls the getSalary method of the Employee class. Here is the correct version of the 
 getSalary method for the Manager class:

 Note
 Some people think of super as being analogous to the this reference. However, that -
 analogy is not quite accurate: super is not a reference to an object. For example, -
 you cannot assign the value super to another object variable. Instead, super is a s-
 pecial keyword that directs the compiler to invoke the superclass method. 

 Note
 Recall that the @this keyword has two meanings: to denote a reference to the implic-
 it parameter and to call another constructor of the same class. Likewise, the @super 
 keyword has two meanings: to invoke a superclass method and to invoke a superclass -
 constructor. When used to invoke constructors, the @this and @super keywords are cl-
 osely related. The constructor calls can only occur as the first statement in anoth-
 er constructor. The constructor parameters are either passed  to another constructor 
 of the same class (this) or a constructor of the superclass (super).
 ----------------------------------------------------------------------------------*/
   public double getSalary()
   {
      double baseSalary = super.getSalary();
      return baseSalary + bonus;
   }

/*-----------------------------------------------------------------------------------
 Our Manager class has a new field to store the bonus, and a new method to set it:
 class Manager extends Employee
 {
     private double bonus;
     . . .
     public void setBonus(double b)
     {
        bonus = b;
     }
 }
 There is nothing special about these methods and fields. If you have a Manager obje-
 ct, you can simply apply the setBonus method.
     Manager boss = . . .;
     boss.setBonus(5000);
 Of course, if you have an Employee object, you cannot apply the setBonus method,  it 
 is not among the methods that are defined in the Employee class. However, you can u-
 se methods such as getName and getHireDay with Manager objects. Even though these m-
 ethods are not explicitly defined in the Manager class, they are automatically inhe-
 rited from the Employee superclass. Similarly, the fields name, salary, and  hireDay 
 are taken from the superclass. Every Manager object has four fields: name, salary, -
 hireDay, and bonus.
 ----------------------------------------------------------------------------------*/
   public void setBonus(double b)
   {
      bonus = b;
   }
}

/*-----------------------------------------------------------------------------------
 ---->
 We make a new manager and set the manager's bonus:
     Manager boss = new Manager("Carl Cracker", 80000, 1987, 12, 15);
     boss.setBonus(5000);
 We make an array of three employees:
     Employee[] staff = new Employee[3];
 We populate the array with a mix of managers and employees:
     staff[0] = boss;
     staff[1] = new Employee("Harry Hacker", 50000, 1989, 10, 1);
     staff[2] = new Employee("Tony Tester", 40000, 1990, 3, 15); 

 We print out everyone's salary:
     for (Employee e : staff)
         System.out.println(e.getName() + " " + e.getSalary());
 This loop prints the following data:
     Carl Cracker 85000.0
     Harry Hacker 50000.0
     Tommy Tester 40000.0
 Now staff[1] and staff[2] each print their base salary because they are Employee ob-
 jects. However, staff[0] is a Manager object whose getSalary method adds the bonus -
 to the base salary. What is remarkable is that the call  e.getSalary() picks out the  
 correct getSalary method. Note that the declared type of e is Employee, but the act-
 ual type of the object to which e refers can be either Employee or Manager. When e -
 refers to an Employee object, then the call e.getSalary() calls the getSalary method 
 of the Employee class. However,when e refers to a Manager object, then the getSalary 
 method of the Manager class is called instead. The virtual machine knows about the -
 actual type of the object to which e refers, and therefore can invoke the correct m-
 ethod. The fact that an object variable (such as the variable e) can refer to multi-
 ple actual types is called polymorphism. Automatically selecting the appropriate me-
 thod at runtime is called dynamic binding. We discuss both topics in more detail  in 
 this chapter.

 Java does not support multiple inheritance.

 ----> Polymorphism
 every object of the subclass is an object of the superclass. For example, every man-
 ager is an employee. Thus, it makes sense for the Manager class to be a subclass  of 
 the Employee class. 

 For example, you can assign a subclass object to a superclass variable. 
     Employee e;
     e = new Employee(. . .);  // Employee object expected
     e = new Manager(. . .); // OK, Manager can be used as well
 In the Java programming language, object variables are polymorphic. A variable of t-
 ype Employee can refer to an object of type Employee or to an object of any subclass 
 of the Employee class (such as Manager, Executive, Secretary, and so on).
     Manager boss = new Manager(. . .);
     Employee[] staff = new Employee[3];
     staff[0] = boss;
 In this case, the variables staff[0] and boss refer to the same object. However, 
 staff[0] is considered to be only an Employee object by the compiler. That means yo-
 u can call
     boss.setBonus(5000); // OK
 but you can't call
     staff[0].setBonus(5000); // ERROR
 The declared type of staff[0] is Employee, and the setBonus method is not a method -
 of the Employee class. However, you cannot assign a superclass reference to a subcl-
 ass variable. For example, it is not legal to make the assignment
     Manager m = staff[i]; // ERROR
 The reason is clear: Not all employees are managers. If this assignment were to suc-
 ceed and m were to refer to an Employee object that is not a manager , then it would 
 later be possible to call m.setBonus(...) and a runtime error would occur. 

 Caution:
 In Java, arrays of subclass references can be converted to arrays of superclass ref-
 erences without a cast. For example, consider this array of managers:
     Manager[] managers = new Manager[10];
 It is legal to convert this array to an Employee[] array:
     Employee[] staff = managers; //no compiler error, but
 The compiler will allow this assignment. But actually, something surprising is goin-
 g on. Keep in mind that managers and staff are references to the same array. Now co-
 nsider the statement
     staff[0] = new Employee("Harry Hacker", ...); 
 staff[0] and managers[0] are the same reference. That would be very bad, calling   -
     managers[0].setBonus(1000) 
 would try to access a nonexistent instance field and would corrupt neighboring memo-
 ry. To make sure no such corruption can occur, all arrays remember the element  type 
 with which they were created, and they monitor that only compatible  references  are 
 stored into them. For example, the array created as new Manager[10] remembers that -
 it is an array of managers. Attempting to store an Employee reference causes an    -
 ArrayStore Exception.

----> override
 Recall that the name and parameter type list for a method is called the method's si-
 gnature. For example, f(int) and f(String) are two methods with the same name but d-
 ifferent signatures. If you define a method in a subclass that has the same signatu-
 re as a superclass method, then you override that method.The return type is not part 
 of the signature. However, when you override a method, you need to keep the return -
 type compatible . A subclass may change the return type to a subtype of the original 
 type. For example, suppose that the Employee class has a method
     public Employee getBuddy() { ... }
 A manager would never want to have a lowly employee as a buddy. To reflect that fact, 
 the Manager subclass can override this method as
     public Manager getBuddy() { ... } // OK to change return type
 We say that the two getBuddy methods have covariant return types.

 When you override a method, the subclass method must be at least as visible as the -
 superclass method. In particular, if the superclass method is public, then the subc-
 lass method must also be declared as public. It is a common error to accidentally o-
 mit the public specifier for the subclass method. The compiler then complains that -
 you try to supply a weaker access privilege.

 ----> Dynamic Binding
 It is important to understand what happens when a method call is applied to an obje-
 ct. Here are the details:
 1 The compiler looks at the declared type of the object and the method name. Let's -
   say we call x.f(param), and the implicit parameter x is declared to be an object -
   of class C. Note that there may be multiple methods, all with the same name, f, b-
   ut with different parameter types. For example, there may be a method f(int) and a 
   method f(String). The compiler enumerates all methods called  f in the class C and 
   all accessible methods called f in the superclasses of C. ( Private methods of the 
   superclass are not accessible.) Now the compiler knows all possible candidates for 
   the method to be called.
 2 Next, the compiler determines the types of the parameters that are supplied in the 
   method call. If among all the methods called f there is a unique method whose par-
   ameter types are a best match for the supplied parameters, then that method is ch-
   osen to be called. This process is called overloading resolution.
   For example, in a call x.f("Hello") , the compiler picks f(String) and not f(int). 
   The situation can get complex because of type conversions ( int to double, Manager 
   to Employee, and so on). If the compiler cannot find any method with matching par-
   ameter types or if multiple methods all match after applying conversions, the com-
   piler reports an error. Now the compiler knows the name and parameter types of the 
   method that needs to be called.
 3 If the method is private, static, final, or a constructor, then the compiler knows 
   exactly which method to call. This is called static binding. Otherwise, the method 
   to be called depends on the actual type of the implicit parameter, and dynamic bi-
   nding must be used at runtime. In our example, the compiler would generate an ins-
   truction to call f(String) with dynamic binding.
 4 When the program runs and uses dynamic binding to call a method , then the virtual 
   machine must call the version of the method that is appropriate for the actual ty-
   pe of the object to which x refers. Let's say the actual type is D,a subclass of C. 
   If the class D defines a method f(String), that method is called. If not, D's sup-
   erclass is searched for a method f(String), and so on.

--------> method table
 It would be time-consuming to carry out this search every time a method is called. -
 Therefore , the virtual machine precomputes for each class a method table that lists 
 all method signatures and the actual methods to be called. When a method is actually 
 called, the virtual machine simply makes a table lookup. In our example, the virtual 
 machine consults the method table for the class D and looks up the method to call f-
 or f(String). That method may be D.f(String) or X.f(String), where X is some superc-
 lass of D. There is one twist to this scenario. If the call is super.f(param) , then 
 the compiler consults the method table of the superclass of the implicit parameter.

 ---->  final modifier
 Classes that cannot be extended are called final classes, and you use the final mod-
 ifier in the definition of the class to indicate this. For example, let us suppose -
 we want to prevent others from subclassing the Executive class. Simply declare the -
 class using the final modifier, as follows:
     final class Executive extends Manager
     {
         . . .
     }
 You can also make a specific method in a class final. If you do this, then no subcl-
 ass can override that method. (All methods in a final class are automatically final.) 
 
 Recall that fields can also be declared as final. A final field cannot be changed a-
 fter the object has been constructed. However, if a class is declared final, only t-
 he methods, not the fields, are automatically final.

 ----> Casting
 1 You can cast only within an inheritance hierarchy.
   If you assign a subclass reference to a superclass variable, you are promising le-
   ss, and the compiler will simply let you do it. If you assign a super-class refer-
   ence to a subclass variable, you are promising more. Then you must use a cast so -
   that your promise can be checked at runtime . What happens if you try to cast down 
   an inheritance chain and you are "lying" about what an object contains?
       Manager boss = (Manager) staff[1]; // ERROR staff[1] is Employee
   When the program runs, the Java runtime system notices the broken promise and gen-
   erates a ClassCastException.
 2 Use instanceof to check before casting from a superclass to a subclass.
       if (staff[1] instanceof Manager)
       {
           boss = (Manager) staff[1];
           . . .
        }
 3 the compiler will not let you make a cast if there is no chance for the cast to s-
   ucceed. For example, the cast
       Date c = (Date) staff[1];
   is a compile-time error because Date is not a subclass of Employee.
 ----------------------------------------------------------------------------------*/
