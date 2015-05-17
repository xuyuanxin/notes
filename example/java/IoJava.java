import java.util.*;

/*-----------------------------------------------------------------------------------
 The Scanner class is defined in the java.util package. Whenever you use a class that 
 is not defined in the basic java.lang package, you need to use an import directive. 

 To read console input, you first construct a Scanner that is attached to System.in:
     Scanner in = new Scanner(System.in);
 Now you can use the various methods of the Scanner class to read input. For example, 
 the @nextLine method reads a line of input. To read an integer, use the @nextInt me-
 thod. Similarly, the @nextDouble method reads the next floating-point number.

 To read from a file, construct a Scanner object like this:
     Scanner in = new Scanner(Paths.get("myfile.txt"));
 If the file name contains backslashes, remember to escape each of them with an addi-
 tional backslash: "c:\\mydirectory\\myfile.txt". Now you can read from the file, us-
 ing any of the Scanner methods that we already described.

 To write to a file, construct a PrintWriter object. In the constructor, simply supp-
 ly the file name:
    PrintWriter out = new PrintWriter("myfile.txt");
 If the file does not exist, it is created. You can use the print, println, and prin-
 tf commands as you did when printing to System.out.

 ----------------------------------------------------------------------------------*/
public class InputTest
{
   public static void main(String[] args)
   {
      Scanner in = new Scanner(System.in);

      // get first input
      System.out.print("What is your name? ");
      String name = in.nextLine();

      // get second input
      System.out.print("How old are you? ");
      int age = in.nextInt();

      // display output on console
      System.out.println("Hello, " + name + ". Next year, you'll be " + (age + 1));
   }
}

