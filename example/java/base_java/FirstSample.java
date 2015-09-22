
public class FirstSample
{
   public static void main(String[] args)
   {
      System.out.println("Hello, World!");
   }
}

/*-----------------------------------------------------------------------------------
1 First and foremost, Java is case sensitive. 
2 The keyword class reminds you that everything in a Java program lives inside a cla-
  ss. Following the keyword class is the name of the class. 
3 You need to make the file name for the source code the same as the name of the pub-
  lic class, with the extension .java appended. 
4 compile this source code:
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




class name
    Names must begin with a letter, and after that , they can have any combination of 
    letters and digits. The length is essentially unlimited. You cannot use a Java r-
    eserved word (such as public or class) for a class name. If a name consists of m-
    ultiple words, use an initial uppercase letter in each of the words. (This use of 
    uppercase letters in the middle of a word is sometimes called "camel case".)
-----------------------------------------------------------------------------------*/
