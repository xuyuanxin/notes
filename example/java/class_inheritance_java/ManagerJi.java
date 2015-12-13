//package inheritance;

public class ManagerJi extends EmployeeJi
{
   private double bonus;

   public ManagerJi(String n, double s, int year, int month, int day)
   {
      super(n, s, year, month, day);
      bonus = 0;
   }
 
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

 ----> Polymorphism


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
