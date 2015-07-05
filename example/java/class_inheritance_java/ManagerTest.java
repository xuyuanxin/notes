//package inheritance;

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
 every manager is an employee. not every employee is a manager.
 you can use a subclass object whenever the program expects a superclass object.
 ----------------------------------------------------------------------------------*/

public class ManagerTest
{
   public static void main(String[] args)
   {
      // construct a Manager object
      ManagerJi boss = new ManagerJi("Carl Cracker", 80000, 1987, 12, 15);
      boss.setBonus(5000);

      EmployeeJi[] staff = new EmployeeJi[3];

      // fill the staff array with Manager and Employee objects

      staff[0] = boss;
      staff[1] = new EmployeeJi("Harry Hacker", 50000, 1989, 10, 1);
      staff[2] = new EmployeeJi("Tommy Tester", 40000, 1990, 3, 15);

      // print out information about all Employee objects
      for (EmployeeJi e : staff)
         System.out.println("name=" + e.getName() + ",salary=" + e.getSalary());
   }
}

/*-----------------------------------------------------------------------------------
 ----> Dynamic binding
 Let's look at this process in detail in the call e.getSalary(). The declared type of 
 e is Employee. The Employee class has a single method, called getSalary, with no me-
 thod parameters. Therefore, in this case, we don't worry about overloading resoluti-
 on. The getSalary method is not private, static, or final, so it is dynamically bou-
 nd. The virtual machine produces method tables for the Employee and Manager classes. 
 The Employee table shows that all methods are defined in the Employee class itself:
 Employee:
     getName()            -> Employee.getName()
     getSalary()          -> Employee.getSalary()
     getHireDay()         -> Employee.getHireDay()
     raiseSalary(double)  -> Employee.raiseSalary(double)
 the Employee class has a superclass Object from which it inherits a number of metho-
 ds. We ignore the Object methods for now. The Manager method table is slightly diff-
 erent. Three methods are inherited, one method is redefined, and one method is added.
 Manager:
      getName()           -> Employee.getName()
      getSalary()         -> Manager.getSalary()
      getHireDay()        -> Employee.getHireDay()
      raiseSalary(double) -> Employee.raiseSalary(double)
      setBonus(double)    -> Manager.setBonus(double)
 At runtime, the call e.getSalary() is resolved as follows:
 1 First, the virtual machine fetches the method table for the actual type of e. That 
   may be the table for Employee, Manager, or another subclass of Employee.
 2 Then, the virtual machine looks up the defining class for the getSalary() signatu-
   re. Now it knows which method to call.
 3 Finally, the virtual machine calls the method.
 Dynamic binding has a very important property : It makes programs extensible without 
 the need for modifying existing code. Suppose a new class Executive is added and th-
 ere is the possibility that the variable e refers to an object of that class. The c-
 ode containing the call e.getSalary() need not be recompiled. The Executive.getSalary() 
 method is called automatically if e happens to refer to an object of type Executive.
 ----------------------------------------------------------------------------------*/
