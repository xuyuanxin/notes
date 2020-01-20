# Java介绍及安装

```java
version  year
1.0      1996
1.1      1997
1.2      1998
1.3      2000
1.4      2002
5.0      2004
6        2006
7        2011
8        2014

You will still see occasional references to versions 1.5 and 1.6, these are just synonyms for versions 5.0 and 6.
```

```java
Java Development Kit(JDK)
    The software for programmers who want to write Java programs

Java Runtime Environment(JRE)
    The software for consumers who want to run Java programs
	
Standard Edition(SE)
    The Java platform for use on desktops and simple server applications
	
Enterprise Edition(EE)
    The Java platform for complex server applications
	
Micro Edition(ME)
    The Java platform for use on cell phones and other small devices
	
Java 2(J2)
    An outdated term that described Java versions from 1998 until 2006
	
Software Development Kit(SDK)
    An outdated term that described the JDK from 1998 until 2006
	
Updata(u)
    Oracle's term for a bug fix release
	
NetBeans
    Oracle's integrated development environment
```

--> install
With Windows or Linux, you need to choose between the x86 (32-bit) and x64 (64-bit) -
versions.

1 You want the JDK (Java SE Development Kit), not the JRE.
2 Windows or Linux: Choose x86 for 32 bit, x64 for 64 bit.
3 Linux: Pick the .tar.gz version.

http://docs.oracle.com/javase/8
http://www.oracle.com/technetwork/java/javase/downloads/index.html  
http://docs.oracle.com/javase/8/docs/technotes/guides/install/install_overview.html  安装

--> linux
 a) chmod 755 jdk-7u4-linux-xxx.rpm
 b) rpm   -i  jdk-7u4-linux-xxx.rpm
 c) vi /etc/profile 

 #set java environment
 JAVA_HOME=/usr/java/jdkxxx # xxx is version(jdk1.6.0_43), 使用rpm, 默认安装在/usr/java
 CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
 PATH=$JAVA_HOME/bin:$PATH
 export JAVA_HOME,PATH,CLASSPATH 
    
--> linux JDK 8 Installation Instructions
 -->--> Installation Instructions Notation and Files
  For instructions containing the notation version, substitute the appropriate JDK u-
  pdate version number. For example, if you are installing update JDK 8 update relea-
  se 2, the following string representing the name of the bundle:
  jdk-8uversion-linux-i586.tar.gz becomes jdk-8u2-linux-i586.tar.gz

  Note that, as in the preceding example, the version number is sometimes preceded w-
  ith the letter u, for example, 8u2, and sometimes it is preceded with an  underbar, 
  for example, jdk1.8.0_02.

  Download File and Instructions    Architecture              Who Can Install
  jdk-8uversion-linux-x64.tar.gz    64-bit                    anyone
  jdk-8uversion-linux-i586.tar.gz   32-bit                    anyone
  jdk-8uversion-linux-x64.rpm       64-bit RPM-based Linux    root
  jdk-8uversion-linux-i586.rpm      32-bit RPM-based Linux    root

  Installation can be performed using either of the following:
  1 Installation of Oracle Linux JDK using archive binaries (.tar.gz) allows you to in-
  stall a private version of the JDK for the current user into any location,  without 
  affecting other JDK installations. However, it may involve manual steps to get some 
  of the features to work (for example, the -version:release option of the java comm-
  and, which allows you to specify the release to be used to run the specified class, 
  requires the correct path to the JDK release under /usr/jdk).
  2 Installation of Oracle Linux JDK using RPM packages allows you to perform a system-
  wide installation of the JDK for all users, and requires root access. RPM-based Li-
  nux platforms are based on Red Hat and SuSE.

  Note:
    When you download and install the Java Development Kit (JDK), the associated Jav-
	a Runtime Environment (JRE) is also installed.

 --> Installation of the 64-bit JDK on Linux Platforms
  This procedure installs the Java Development Kit (JDK) for 64-bit Linux, using an -
  archive binary file (.tar.gz). These instructions use the following file:
  jdk-8uversion-linux-x64.tar.gz

  1 Download the file.
  Before the file can be downloaded, you must accept the license agreement. The arch-
  ive binary can be installed by anyone (not only root users), in any location that -
  you can write to. However, only the root user can install the JDK into the system -
  location.

  2 Change directory to the location where you would like the JDK to be installed, t-
  hen move the .tar.gz archive binary to the current directory.

  3 Unpack the tarball and install the JDK.
  % tar zxvf jdk-8uversion-linux-x64.tar.gz
  The Java Development Kit files are installed in a directory called jdk1.8.0_version 
  in the current directory.

  4 Delete the .tar.gz file if you want to save disk space.

 --> Installation of the 64-bit JDK on RPM-based Linux Platforms
  This procedure installs the Java Development Kit (JDK) for 64-bit RPM-based Linux -
  platforms, such as Red Hat and SuSE, using an RPM binary file (.rpm) in the  system 
  location. You must be root to perform this installation. These instructions use the 
  following file:
  jdk-8uversion-linux-x64.rpm
  1 Download the file. 
  Before the file can be downloaded, you must accept the license agreement.
  2 Become root by running su and entering the super-user password.
  3 Uninstall any earlier installations of the JDK packages.

rpm -e package_name

  4 Install the package.

rpm -ivh jdk-8uversion-linux-x64.rpm

  To upgrade a package:

rpm -Uvh jdk-8uversion-linux-x64.rpm

  5 Delete the .rpm file if you want to save disk space.
  6 Exit the root shell. No need to reboot.
	
--> windows
 1 下载安装jdk
 2 我的电脑->属性->高级->环境变量->系统变量中添加以下环境变量：
 JAVA_HOME值为： D:\Program Files\Java\jdk1.6.0_18（你安装JDK的目录）
 CLASSPATH值为：.;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\bin;
 Path: 追加 %JAVA_HOME%\bin;
 3 cmd下查看javac -version  java -verison，输出版本信息说明安装成功。

-------------------------------------------------------------------------------------
----> compile and run
1 xxx.java
2 javac xxx.java 
  编译Java源文件，也就是将Java源文件编译（Compile）成Java类文件（扩展名为.class），如
  ：使用“javac.exe”命令将X.java文件编译成“X.class”类文件。
  Java类文件由字节码构成，所以也可以称为字节码文件，所谓的字节码文件是与平台无关的二
  进制码，执行时由解释器（java.exe）解释成本地计算机码。一边解释一边执行，解释一句，执
  行一句。
3 java xxx
  运行Java程序。Java程序可以分为Java  Application（Java应用程序）和Java  Applet（Java小
  应用程序）。其中，Java  Application必须通过Java解释器来解释执行其字节码文件，Java Applet
  必须使用支持它的浏览器（IE浏览器）运行。

CLASSPATH是编译或运行Java程序时用来告诉Java编译器或虚拟机到哪里查找Java类文件的
PATH变量用来告诉操作系统到哪里去查找一个命令。

# java基础

## first sample

  public class FirstSample
 {
    public static void main(String[] args)
    {
       System.out.println("Hello, World!");
    }
 }

 1 First and foremost, Java is case sensitive. 
 2 The keyword public is called an access modifier;
 3 Everything in a Java program must be inside a class. Following the keyword class -
   is the name of the class. 
 4 You need to make the file name for the source code the same as the name of the pu-
   blic class, with the extension .java appended. 
 5 compile this source code:
      javac ClassName.java
  you end up with a file containing the bytecodes for this class. The Java compiler -
  automatically names the bytecode file ClassName.class and stores it in the same di-
  rectory as the source file. 
 5 launch the program by issuing the following command: 
          java ClassName // Remember to leave off the .class extension.
  the Java virtual machine always starts execution with the code in the main method -
  in the class you indicate. (The term "method" is Java-speak for a function. ) Thus, 
  you must have a main method in the source file for your class for your code to exe-
  cute. The point to remember for now is that every Java application must have a main 
  method that is declared in the following way:
          public class ClassName    
          {
              public static void main(String[] args)
              {
                  program statements
              }
          }
 6 we are using the System.out object and calling its println method(The method displ-
  ays the string parameter on the console. It then terminates the output line, so th-
  at each call to println displays its output on a new line. ). Notice the periods u-
  sed to invoke a method. Java uses the general syntax
          object.method(parameters)
  as its equivalent of a function call. Even if a method takes no parameters, you mu-
  st still use empty parentheses. For example,a variant of the println method with no
  parameters just prints a blank line. You invoke it with the call
          System.out.println();

--> comment
 /**/
 //


class name
    Names must begin with a letter, and after that , they can have any combination of 
    letters and digits. The length is essentially unlimited. You cannot use a Java r-
    eserved word (such as public or class) for a class name. If a name consists of m-
    ultiple words, use an initial uppercase letter in each of the words. (This use of 
    uppercase letters in the middle of a word is sometimes called "camel case".)
-----------------------------------------------------------------------------------*/





arrays  java.util.Arrays  language/java/utiljava/Arrays.java

# 类

## Defining Your Own Classes

The simplest form for a class definition in Java is

```java
class ClassName
{
    field1
    field2
    . . .
    constructor1
    constructor2
    . . .
    method1
    method2
    . . .
}
```

```java
import java.util.*;

/**
* This program tests the Employee class.
* @version 1.11 2004-02-19
* @author Cay Horstmann
*/
public class EmployeeTest
{
    public static void main(String[] args)
    {
        Employee[] staff = new Employee[3]; // fill the staff array with three Employee objects

        staff[0] = new Employee("Carl Cracker", 75000, 1987, 12, 15);
        staff[1] = new Employee("Harry Hacker", 50000, 1989, 10, 1);
        staff[2] = new Employee("Tony Tester", 40000, 1990, 3, 15);

        for (Employee e : staff)
            e.raiseSalary(5); // raise everyone's salary by 5%

        // print out information about all Employee objects
        for (Employee e : staff)
            System.out.println("name=" + e.getName() + ",salary=" + e.getSalary() + ",hireDay="
                + e.getHireDay());
    }
}

class Employee
{
    private String name;
    private double salary;
    private Date hireDay;

    public Employee(String n, double s, int year, int month, int day)
    {
        name = n;
        salary = s;
        GregorianCalendar calendar = new GregorianCalendar(year, month - 1, day);
        hireDay = calendar.getTime(); // GregorianCalendar uses 0 for January
    }

    public String getName()
    {
        return name;
    }

    public double getSalary()
    {
        return salary;
    }

    public Date getHireDay()
    {
        return hireDay;
    }

    public void raiseSalary(double byPercent)
    {
        double raise = salary * byPercent / 100;
        salary += raise;
    }
} 
```

Note that the example program consists of two classes: the Employee class and a class EmployeeTest with the public access specifier. The main method with the instructions that we just described is contained in the EmployeeTest class. The name of  the source file is EmployeeTest.java because the name of the file must match the name of the public class. You can only have one public class in a source file, but you can have any number of nonpublic classes.

when you compile this source code, the compiler creates two class files in the directory: EmployeeTest.class and Employee.class. You then start the program by giving the bytecode interpreter the name of the class that contains the main method of your program:

```
java EmployeeTesT
```

The bytecode interpreter starts running the code in the main method in the EmployeeTest class.

### Use of Multiple Source Files

The program has two classes in a single source file . Many programmers prefer to put each class into its own source file. For example, you can place the Employee class into a file Employee.java and the EmployeeTest class into EmployeeTest.java. If you like this arrangement, then you have two choices for compiling the program. You can invoke the Java compiler with a wildcard:

```shell
javac Employee*.java
```

Then, all source files matching the wildcard will be compiled into class files. Or, you can simply type

```
javac EmployeeTest.java
```

You may find it surprising that the second choice works even though the Employee.java file is never explicitly compiled. However, when the Java compiler sees the Employee class being used inside EmployeeTest.java, it will look for a file named Employee.class. If it does not find that file, it automatically searches for Employee.java and compiles it. Moreover, if the timestamp of the version of  Employee.java that it finds is newer than that of the existing Employee.class  file, the Java compiler will automatically recompile the file.

> NOTE: If you are familiar with the make facility of UNIX (or one of its Windows cousins, such as nmake), then you can think of the Java compiler as having the make functionality already built in.

--> public private
 public void raiseSalary(double byPercent)
 The keyword @public means that any method in any class can call the method. 

 private String name;
 private double salary;
 private Date hireDay;
 The @private keyword makes sure that the only methods that can access these instanc-
 e fields are the methods of the Employee class itself. No outside method can read or 
 write to these fields. 
 The @name and @hireDay fields are references to @String and @Date objects. This is -
 quite usual: Classes will often contain instance fields of class type.

--> constructor
 A constructor has the same name as the class.
 A class can have more than one constructor.
 A constructor can take zero, one, or more parameters.
 A constructor has no return value.
 A constructor is always called with the @new operator. You can’t apply a constructor 
 to an existing object to reset the instance fields.

 -->--> Default Field Initialization
  If you don’t set a field explicitly in a constructor, it is automatically set to  a 
  default value:numbers to 0, boolean values to false, and object references to null. 

 -->--> The Constructor with No Arguments
  Please keep in mind that you get a free no-argument constructor only when your cla-
  ss has no other constructors. If you write your class with even a single construct-
  or of your own and you want the users of your class to have the ability to create -
  an instance by a call to
  > new ClassName()
  > then you must provide a no-argument constructor. Of course, if you are happy with -
  > the default values for all fields, you can simply supply
  > public ClassName()
  > {
  > }

 -->--> Explicit Field Initialization
  You can simply assign a value to any field in the class definition. For example:

  class Employee
  {
      private String name = "";
      . . .
  }

  This assignment is carried out before the constructor executes.

 -->--> Calling Another Constructor
  The keyword this refers to the implicit parameter of a method. However, this keywo-
  rd has a second meaning. If the first statement of a constructor has the form     -
  this(. . .), then the constructor calls another constructor of the same class. Here 
  is a typical example:

  public Employee(double s)
  {
      // calls Employee(String, double)
      this("Employee #" + nextId, s);
      nextId++;
  }

  When you call new Employee(60000), the Employee(double) constructor calls the     -
  Employee(String,double) constructor. Using the this keyword in this manner is usef-
  ul, you only need to write common construction code once.

 -->--> initialization block
  Class declarations can contain arbitrary blocks of code. These blocks are  executed 
  whenever an object of that class is constructed. For example:

  class Employee
  {
      private static int nextId;
      private int id;
      private String name;
      private double salary;
      // object initialization block
      {
      id = nextId;
      nextId++;
      }
      public Employee(String n, double s)
      {
          name = n;
          salary = s;
      }
      public Employee()
      {
          name = "";
          salary = 0;
      }
      . . .
  }

  In this example, the id field is initialized in the object initialization block, no
  matter which constructor is used to construct an object. The initialization block -
  runs first, and then the body of the constructor is executed.

 With so many ways of initializing data fields, it can be quite confusing to give all
 possible pathways for the construction process. Here is what happens in detail  when 
 a constructor is called:
 1. All data fields are initialized to their default values (0, false, or null).
 2. All field initializers and initialization blocks are executed, in the order in w-
    hich they occur in the class declaration.
 3. If the first line of the constructor calls a second constructor, then the body of
    the second constructor is executed.
 4. The body of the constructor is executed.

 -->--> initialize a static field
  To initialize a static field, either supply an initial value or use a static initi-
  alization block. You have already seen the first mechanism:
  > private static int nextId = 1;
  > If the static fields of your class require complex initialization code, use a stat-
  > ic initialization block.

  Place the code inside a block and tag it with the keyword static. Here is an examp-
  le. We want the employee ID numbers to start at a random integer less than 10,000.

  // static initialization block
  static 
  {
      Random generator = new Random();
      nextId = generator.nextInt(10000);
  }

  Static initialization occurs when the class is first loaded. Like instance  fields,
  static fields are 0, false, or null unless you explicitly set them to another valu-
  e. All static field initializers and static initialization blocks are executed in -
  the order in which they occur in the class declaration.


  Amazingly enough, up to JDK 6, it was possible to write a “Hello, World” program in 
  Java without ever writing a main method.

  public class Hello
  {
      static
      {
          System.out.println("Hello, World");
      }
  }

  When you invoked the class with java Hello, the class was loaded, the static initi-
  alization block printed “Hello, World” , and only then was a message displayed that 
  main is not defined. Since Java SE 7, the java program first checks that there is a 
  main method.

 -->--> Object Destruction and the finalize Method
  Since Java does automatic garbage collection, manual memory reclamation is not nee-
  ded, so Java does not support destructors. You can add a finalize method to any cl-
  ass. The finalize method will be called before the garbage collector sweeps away t-
  he object. 

--> Implicit and Explicit Parameters
 Methods operate on objects and access their instance fields. For example, the method 

 public void raiseSalary(double byPercent)
 {
     double raise = salary * byPercent / 100;
     salary += raise;
 }

 sets a new value for the @salary instance field in the object on which this method -
 is invoked. Consider the call

 number007.raiseSalary(5);

 The effect is to increase the value of the number007.salaryfield by 5%. More specif-
 ically, the call executes the following instructions:

 double raise = number007.salary * 5 / 100;
 number007.salary += raise;

 The @raiseSalary method has two parameters. The first parameter, called the implicit
 parameter, is the object of type Employee that appears before the method name. The -
 second parameter, the number inside the parentheses after the method name, is an ex-
 plicit parameter. (Some people call the implicit parameter the target or receiver of 
 the method call.)

 As you can see, the explicit parameters are explicitly listed in the method declara-
 tion, for example, double @byPercent. The implicit parameter does not appear in  the
 method declaration.

 In every method, the keyword @this refers to the implicit parameter. If you like, y-
 ou can write the @raiseSalary method as follows:

 public void raiseSalary(double byPercent)
 {
     double raise = this.salary * byPercent / 100;
     this.salary += raise;
 }

--> accessor method
  accessor methods: they simply return the values of instance fields, they are somet-
  imes called field accessors. 

  Sometimes, it happens that you want to get and set the value of an instance  field.
  Then you need to supply three items:
  1 A private data field;
  2 A public field accessor method; and
  3 A public field mutator method.
  This is a lot more tedious than supplying a single public data field, but there are
  considerable benefits.

--> Final Instance Fields
 You can define an instance field as final. Such a field must be initialized when the
 object is constructed. That is, you must guarantee that the field value has been set
 after the end of every constructor. Afterwards, the field may not be modified again. 
 For example, the name field of the Employee class may be declared as final because -
 it never changes after the object is constructed.
    class Employee
    {
        private final String name;
        . . .
    }
 The final modifier is particularly useful for fields whose type is primitive or an -
 immutable class. (A class is immutable if none of its methods ever mutate its objec-
 ts. For example, the String class is immutable.) For mutable classes, the final mod-
 ifier is likely to confuse the reader. For example,
     private final Date hiredate;
 merely means that the object reference stored in the hiredate variable doesn't get -
 changed after the object is constructed. That does not mean that the hiredate object 
 is constant. Any method is free to invoke the setTime mutator on the object to which
 hiredate refers.

--> Static Fields
 If you define a field as static, then there is only one such field per class. For e-
 xample, We add an instance field id and a static field nextId to the Employee class:
	 class Employee
	 {
		 private static int nextId = 1;
		 private int id;
		 . . .
	 }
 Every employee object now has its own id field, but there is only one nextId field -
 that is shared among all instances of the class . Let's put it another way. If there 
 are 1,000 objects of the Employee class, then there are 1,000 instance fields id, o-
 ne for each object. But there is a single static field nextId . Even if there are no 
 employee objects, the static field nextId is present. It belongs to the class, not -
 to any individual object.

 NOTE: In some object-oriented programming languages, static fields are called  class 
 fields. The term "static" is a meaningless holdover from C++.

 -->--> Static Constants 
  Static variables are quite rare. However, static constants are more common. For ex-
  ample, the Math class defines a static constant:
	 public class Math
	 {
		 . . .
		 public static final double PI = 3.14159265358979323846;
		 . . .
	 }
  You can access this constant in your programs as Math.PI .

 -->--> Static Methods
  Static methods are methods that do not operate on objects. For example, the pow me-
  thod of the Math class is a static method. The expression
	  Math.pow(x, a)
  computes the power x^a. It does not use any Math object to carry out its task. In -
  other words, it has no implicit parameter.

  A static method of the Employee class cannot access the @id instance field  because 
  it does not operate on an object. (@id is not @static )

  It is legal to use an object to call a static method. For example, if harry is  an
  Employee object,then you can call harry.getNextId() instead of Employee.getnextId(). 
  However, we find that notation confusing. The getNextId method doesn't look at har-
  ry at all to compute the result. We recommend that you use class names, not object-
  s, to invoke static methods.

 -->--> Use static methods in two situations:
  * When a method doesn't need to access the object state because all needed paramet-
    ers are supplied as explicit parameters (example: Math.pow).
  * When a method only needs to access static fields of the class.

--> The main Method
 Note that you can call static methods without having any objects. For example, you -
 never construct any objects of the Math class to call Math.pow. For the same reason, 
 the main method is a static method. The main method does not operate on any objects. 
 In fact, when a program starts, there aren’t any objects yet. The static main metho-
 d executes, and constructs the objects that the program needs.

 Every class can have a main method. That is a handy trick for unit testing of class-
 es. For example, you can add a main method to the Employee class:

 class Employee
 {
     public Employee(String n, double s, int year, int month, int day)
     {
         name = n;
         salary = s;
         LocalDate hireDay = LocalDate.now(year, month, day);
     }
     . . .
	 
     public static void main(String[] args) // unit test
     {
         Employee e = new Employee("Romeo", 50000, 2003, 3, 31);
         e.raiseSalary(10);
         System.out.println(e.getName() + " " + e.getSalary());
     }
     . . .
 }

 If you want to test the Employee class in isolation, simply execute
 > java Employee
 >  If the Employee class is a part of a larger application, you start the application -
 >  with
 > java Application
 >  and the main method of the Employee class is never executed.

 

 

 

 

 

public class classBase // EmployeeTest
{
/*-----------------------------------------------------------------------------------
 ----> Factory Methods
 Here is another common use for static methods. The NumberFormat class uses factory -
 methods that yield formatter objects for various styles.
     NumberFormat currencyFormatter = NumberFormat.getCurrencyInstance();
     NumberFormat percentFormatter = NumberFormat.getPercentInstance();
     double x = 0.1;
     System.out.println(currencyFormatter.format(x)); // prints $0.10
     System.out.println(percentFormatter.format(x));  // prints 10%
 Why doesn't the NumberFormat class use a constructor instead? There are two reasons:
 * You can't give names to constructors. The constructor name is always the same as -
 the class name. But we want two different names to get the currency instance and the 
 percent instance.
 * When you use a constructor, you can't vary the type of the constructed object. But 
 the factory methods actually return objects of the class DecimalFormat, a subclass -
 that inherits from NumberFormat. 

 ----> The main Method
 Note that you can call static methods without having any objects. For example, you -
 never construct any objects of the Math class to call Math.pow. For the same reason, 
 the main method is a static method. The main method does not operate on any objects. 
 In fact, when a program starts, there aren't any objects yet. The static main metho-
 d executes, and constructs the objects that the program needs.

 Every class can have a main method. That is a handy trick for unit-testing of class-
 es. For example, you can add a main method to the Employee class. If you want to te-
 st the Employee class in isolation, simply execute
	 java Employee
 If the employee class is a part of a larger application, then you start the applica-
 tion with
	 java Application
 and the main method of the Employee class is never executed.

 Note that the Employee class also has a static main method for unit testing. Try ru-
 nning both
	 java Employee
 and
	 java StaticTest
 to execute both main methods.
-----------------------------------------------------------------------------------*/
   public static void main(String[] args)
   {
      // fill the staff array with three Employee objects
      EmployeeL[] staff = new EmployeeL[3];

      staff[0] = new EmployeeL("Carl Cracker", 75000, 1987, 12, 15);
      staff[1] = new EmployeeL("Harry Hacker", 50000, 1989, 10, 1);
      staff[2] = new EmployeeL("Tony Tester", 40000, 1990, 3, 15);
    
      // raise everyone's salary by 5%
      for (EmployeeL e : staff)
         e.raiseSalary(5);
    
      // print out information about all Employee objects
      for (EmployeeL e : staff)
         System.out.println("name=" + e.getName() + ",salary=" + e.getSalary() + ",hireDay="
               + e.getHireDay());
    
        int n = EmployeeL.getNextId(); // calls static method
        System.out.println("Next available id=" + n);
   }
}




class EmployeeL // employee local
{
/*-----------------------------------------------------------------------------------

 

-----------------------------------------------------------------------------------*/
    private static int nextId = 1; /* Static Fields */
	private int id;
    private String name;   //instance fields
    private double salary;
    private Date hireDay;

/*-----------------------------------------------------------------------------------
 ----> constructor
 As you can see, the name of the constructor is the same as the name of the class. T-
 his constructor runs when you construct objects of the Employee class, giving the i-
 nstance fields the initial state you want them to have. For example, when you create 
 an instance of the Employee class with code like this:
     new Employee("James Bond", 100000, 1950, 1, 1)
 you have set the instance fields as follows:
     name = "James Bond";
     salary = 100000;
     hireDay = January 1, 1950;

 A constructor can only be called in conjunction with the new operator. You can't ap-
 ply a constructor to an existing object to reset the instance fields. For example,
    james.Employee("James Bond", 250000, 1950, 1, 1) // compile-time error



 all Java objects are constructed on the heap and that a constructor must be combine-
 d with @new. 

 ----> Caution
 Be careful not to introduce local variables with the same names as the instance fie-
 lds.
-----------------------------------------------------------------------------------*/
   public EmployeeL(String n, double s, int year, int month, int day) /* constructor */
   {
      name = n;
      salary = s;
      GregorianCalendar calendar = new GregorianCalendar(year, month - 1, day);
      // GregorianCalendar uses 0 for January
      hireDay = calendar.getTime();
   }

   public String getName() /* field accessors */
   {
      return name;
   }

   public double getSalary() /* field accessors */
   {
      return salary;
   }

/*-----------------------------------------------------------------------------------
 As they simply return the values of instance fields, they are sometimes called field 
 accessors.

 Be careful not to write accessor methods that return references to mutable  objects. 
 We violated that rule in our Employee class in which the getHireDay method returns -
 an object of class Date. This breaks encapsulation! Consider the following rogue co-
 de:
     Employee harry = . . .;
     Date d = harry.getHireDay();
     double tenYearsInMilliSeconds = 10 * 365.25 * 24 * 60 * 60 * 1000;
     d.setTime(d.getTime() - (long) tenYearsInMilliSeconds);
     // let's give Harry ten years of added seniority

 The reason is subtle. Both d and harry.hireDay refer to the same object. Applying m-
 utator methods to d automatically changes the private state of the employee  object!
 If you need to return a reference to a mutable object , you should clone it first. A
 clone is an exact copy of an object stored in a new location . Here is the corrected 
 code:
 class Employee
 {
     . . .
     public Date getHireDay()
     {
         return hireDay.clone();
     }
    . . .
 }

 As a rule of thumb, always use clone whenever you need to return a copy of a mutabl-
 e data field.
 ----------------------------------------------------------------------------------*/
   public Date getHireDay() /* field accessors */
   {
      return hireDay;
   }

/*-----------------------------------------------------------------------------------
 ----> Implicit and Explicit Parameters
 Methods operate on objects and access their instance fields. For example, the method
     public void raiseSalary(double byPercent)
     {
         double raise = salary * byPercent / 100;
         salary += raise;
     }
 sets a new value for the salary instance field in the object on which this method is
 invoked. Consider the call 
     number007.raiseSalary(5);
 The effect is to increase the value of the number007.salary field by 5%. More speci-
 fically, the call executes the following instructions:
     double raise = number007.salary * 5 / 100;
     number007.salary += raise;

 The @raiseSalary method has two parameters . The first parameter, called the implicit 
 parameter, is the object of type Employee that appears before the method name. The -
 second parameter, the number inside the parentheses after the method name, is an ex-
 plicit parameter.

 As you can see, the explicit parameters are explicitly listed in the method declara-
 tion, for example, double byPercent. The implicit parameter does not appear in the -
 method declaration.

 In every method, the keyword this refers to the implicit parameter. If you like, you
 can write the raiseSalary method as follows:
    public void raiseSalary(double byPercent)
    {
        double raise = this.salary * byPercent / 100;
        this.salary += raise;
    }
-----------------------------------------------------------------------------------*/
   public void raiseSalary(double byPercent)
   {
      double raise = salary * byPercent / 100;
      salary += raise;
   }

    public int getId()
    {
        return id;
    }
    
    public void setId()
    {
        id = nextId; // set id to next available id
        nextId++;
    }
    
    public static int getNextId() /* Static Methods */
    {
        return nextId; // returns static field
    }
}

/*-----------------------------------------------------------------------------------

-----------------------------------------------------------------------------------*/



# xx

