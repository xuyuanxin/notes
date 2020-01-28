# Inheritance

In this chapter, you will learn about inheritance, another fundamental concept of  object-oriented programming. The idea behind inheritance is that you can create new classes that are built on existing classes. When you inherit from an existing class, you reuse (or inherit) its methods, and you can add new methods and fields to  adapt your new class to new situations. This technique is essential in Java programming.

## Superclasses and Subclasses

### Defning Subclasses

Here is how you defne a Manager class that inherits from the Employee class. Use the Java keyword extends to denote inheritance.

```java
public class Manager extends Employee
{
    added methods and fields
}  
```

The keyword extends indicates that you are making a new class that derives from an existing class. The existing class is called the superclass, base class, or parent class. The new class is called the subclass, derived class, or child class. The terms superclass and subclass are those most commonly used by Java programmers.

However, you can use methods such as getName and getHireDay with Manager objects. Even though these methods are not explicitly defned in the Manager class, they are automatically inherited from the Employee superclass.

Similarly, the felds name, salary, and hireDay are taken from the superclass. Every Manager object has four felds: name, salary, hireDay, and bonus.  

 All inheritance in Java is public inheritance; a subclass can add fields, and it can add methods or override the methods of the superclass. However, inheritance can never take away any fields or methods.

### Overriding Methods

However, some of the superclass methods are not appropriate for the Manager subclass. In particular, the getSalary method should return the sum of the base salary and the bonus. You need to supply a new method to override the superclass method:

```java
public double getSalary()
{
    return salary + bonus; // V1: won't work, 
}
```

The getSalary method of the Manager class has no direct access to the private fields of the superclass. If the Manager methods want to access those private fields, they have to do what every other method does, use the public interface, in this case, the public getSalary method of the Employee class. So, let's try this again. You need to call getSalary instead of simply accessing the salary field.

```java
public double getSalary()
{
    double baseSalary = getSalary(); // V2: still won't work
    return baseSalary + bonus;
}
```

The problem is that the call to getSalary simply calls itself, because the Manager class has a getSalary method (namely, the method we are trying to implement). The consequence is an infinite chain of calls to the same method, leading to a program crash. We need to indicate that we  want to call the getSalary method of the Employee super class, not the current class. You use the special keyword super for this purpose. The call super.getSalary() calls the getSalary method of the Employee class. Here is the correct version of the getSalary method for the Manager class:

```java
public double getSalary()
{
    double baseSalary = super.getSalary(); // V3 ok
    return baseSalary + bonus;
}
```

Note: Some people think of super as being analogous to the this reference. However, that analogy is not quite accurate: super is not a reference to an object. For example, you cannot assign the value super to another object variable. Instead, super is a special keyword that directs the compiler to invoke the superclass method. 

Note: Recall that the @this keyword has two meanings: to denote a reference to the implicit parameter and to call another constructor of the same class. Likewise, the @super keyword has two meanings: to invoke a superclass method and to invoke a superclass constructor. When used to invoke constructors, the @this and @super keywords are closely related. The constructor calls can only occur as the first statement in another constructor. The constructor parameters are either passed  to another constructor of the same class (this) or a constructor of the superclass (super). 

### Subclass Constructor

```java
 public Manager(String n, double s, int year, int month, int day)
 {
     super(n, s, year, month, day);
     bonus = 0;
 }
```

The instruction

```java
super(n, s, year, month, day);
```

is shorthand for "call the constructor of the Employee superclass with n, s, year, month, and day as parameters." Since the Manager constructor cannot access the private fields of the Employee class, it must initialize them through a constructor. The constructor is invoked with the special super syntax. The call using super must be the first statement in the constructor for the subclass.

If the subclass constructor does not call a superclass constructor explicitly, the no-argument constructor of the superclass is invoked. If the superclass does not have a no-argument constructor and the subclass constructor does not call another superclass constructor explicitly, the Java compiler reports an error. 

### Inheritance Hierarchies /todo

### polymorphism

A simple rule can help you decide whether or not inheritance is the right design for your data. The “is–a” rule states that every object of the subclass is an object of the superclass. For example, every manager is an employee. Thus, it makes sense for the Manager class to be a subclass of the Employee class. Naturally, the opposite is not true—not every employee is a manager.

Another way of formulating the “is–a” rule is the substitution principle. That principle states that you can use a subclass object whenever the program expects a superclass object. For example, you can assign a subclass object to a superclass variable.

```java
Employee e;
e = new Employee(. . .); // Employee object expected
e = new Manager(. . .); // OK, Manager can be used as well    
```

In the Java programming language, object variables are polymorphic. A variable of type Employee can refer to an object of type Employee or to an object of any subclass of the Employee class (such as Manager, Executive, Secretary, and so on). 

```java
Manager boss = new Manager(. . .);
Employee[] staff = new Employee[3];
staff[0] = boss;
```

In this case, the variables staff[0] and boss refer to the same object. However,  staff[0] is considered to be only an Employee object by the compiler. 

```java
boss.setBonus(5000); // OK  
staff[0].setBonus(5000); // ERROR 
```

The declared type of staff[0] is Employee, and the setBonus method is not a method of the Employee class. However, you cannot assign a superclass reference to a subclass variable. For example, it is not legal to make the assignment

```java
Manager m = staff[i]; // ERROR
```

The reason is clear: Not all employees are managers. If this assignment were to succeed and m were to refer to an Employee object that is not a manager , then it would later be possible to call m.setBonus(...) and a runtime error would occur. 

Caution: In Java, arrays of subclass references can be converted to arrays of superclass references without a cast. For example, consider this array of managers,  It is legal to convert this array to an Employee[] array:

```java
Manager[] managers = new Manager[10];
Employee[] staff = managers; //no compiler error, but
```

The compiler will allow this assignment. But actually, something surprising is going on. Keep in mind that managers and staff are references to the same array. Now consider the statement

```java
staff[0] = new Employee("Harry Hacker", ...); 
managers[0].setBonus(1000) 
```

staff[0] and managers[0] are the same reference. That would be very bad, calling would try to access a nonexistent instance field and would corrupt neighboring memory. 

### Understanding Method Calls /todo

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

 When @e refers to an Employee object,then the call e.getSalary() calls the getSalary 
 method of the Employee class. However, when e refers to a Manager object, then the -
 getSalary method of the Manager class is called instead. The virtual machine knows -
 about the actual type of the object to which e refers, and therefore can invoke  the 
 correct method. The fact that an object variable (such as the variable e) can  refer 
 to multiple actual types is called polymorphism. Automatically selecting the approp-
 riate method at runtime is called dynamic binding.

 1 Java does not support multiple inheritance.
 2 you can use a subclass object whenever the program expects a superclass object. e-
   very manager is an employee. not every employee is a manager. 

 It is important to understand exactly how a method call is applied to an object. Le-
 t’s say we call x.f(args), and the implicit parameter x is declared to be an  object 
 of class C. Here is what happens:

 1 The compiler enumerates all methods called f in the class C and all accessible me-
   thods called f in the superclasses of C. (Private methods of the superclass are n-
   ot accessible.) For example, there may be a method f(int) and a method f(String). 

 2 Next, the compiler determines the types of the arguments that are supplied in  the 
   method call. This process is called "overloading resolution". For example, in a c-
   all x.f("Hello"), the compiler picks f(String) and not f(int). If the compiler ca-
   nnot find any method with matching parameter types or if multiple methods all mat-
   ch after applying conversions, the compiler reports an error.

 3 If the method is private, static, final, or a constructor, then the compiler knows
   exactly which method to call. This is called "static binding". Otherwise, the met-
   hod to be called depends on the actual type of the implicit parameter, and "dynam-
   ic binding" must be used at runtime. 

 4 When the program runs and uses dynamic binding to call a method, the virtual mach-
   ine must call the version of the method that is appropriate for the actual type of 
   the object to which x refers. Let’s say the actual type is D, a subclass of C.  If 
   the class D defines a method f(String), that method is called. If not, D’s superc-
   lass is searched for a method f(String), and so on.

### Preventing Inheritance

Classes that cannot be extended are called final classes, and you use the @final modifier in the definition of the class to indicate this. For example, suppose we want to prevent others from subclassing the Executive class. Simply declare the class using the final modifier, as follows:

```java
public final class Executive extends Manager
{
    . . .
} 
```

You can also make a specific method in a class final. If you do this, then no subclass can override that method. (All methods in a final class are automatically final.)For example:

```java
public class Employee
{
    . . .
    public final String getName()
    {
        return name;
    }
    . . .
}
```

Recall that fields can also be declared as final. A final field cannot be changed after the object has been constructed. However, if a class is declared final, only the methods, not the fields, are automatically final.

### Casting /todo

### Abstract Classes

As you move up the inheritance hierarchy, classes become more general and probably more abstract. At some point, the ancestor class becomes so general that you think of it more as a basis for other classes than as a class with specific instances you want to use. 

If you use the @abstract keyword, you do not need to implement the method at all. a class with one or more abstract methods must itself be declared abstract.

```java
public abstract class Person
{
    . . .
    public abstract String getDescription();
}
```

In addition to abstract methods, abstract classes can have fields and concrete methods. A class can even be declared as abstract though it has no abstract methods.

Abstract methods act as placeholders for methods that are implemented in the subclasses. When you extend an abstract class, you have two choices. You can leave some or all of the abstract methods undefined; then you must tag the subclass as abstract as well. Or you can define all methods, and the subclass is no longer abstract.

Abstract classes cannot be instantiated. Note that you can still create object variables of an abstract class, but such a variable must refer to an object of a nonabstract subclass. For example, the expression

```java
new Person("Vince Vu") // error
```

is an error. However, you can create objects of concrete subclasses.

Note that you can still create object variables of an abstract class, but such a variable must refer to an object of a nonabstract subclass. For example:

```java
Person p = new Student("Vince Vu", "Economics");
```

Here p is a variable of the abstract type Person that refers to an instance of the nonabstract subclass Student.  

### protected

Any features declared private won’t be visible to other classes.  A subclass cannot access the private fields of its superclass. There are times, however, when you want to restrict a method to subclasses only or, less commonly, to allow subclass methods to access a superclass field. In that case, you declare a class feature as protected. 

Here is a summary of the four access modifiers in Java that control visibility:

  1. Visible to the class only (private).
  2. Visible to the world (public).
  3. Visible to the package and all subclasses (protected).
    4. Visible to the package—the (unfortunate) default. No modifiers are needed

## Object: The Cosmic Superclass /todo




















