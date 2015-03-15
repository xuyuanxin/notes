/*-----------------------------------------------------------------------------------
at the beginning of the program. The Scanner class is defined in the java.util packa-
ge. Whenever you use a class that is not defined in the basic java.lang package , you 
need to use an import directive. 
-----------------------------------------------------------------------------------*/
import java.util.*;

/*-----------------------------------------------------------------------------------
 To read console input, you first construct a Scanner that is attached to System.in :
     Scanner in = new Scanner(System.in);
 Now you can use the various methods of the Scanner class to read input. For example, 
 the nextLine method reads a line of input.
     System.out.print("What is your name? ");
     String name = in.nextLine();
 Here, we use the nextLine method because the input might contain spaces. To read a -
 single word (delimited by whitespace), call
     String firstName = in.next();
 To read an integer, use the nextInt method.
     System.out.print("How old are you? ");
     int age = in.nextInt();
 Similarly, the nextDouble method reads the next floating-point number.
-----------------------------------------------------------------------------------*/
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
