/*-----------------------------------------------------------------------------------
at the beginning of the program. The Scanner class is defined in the java.util packa-
ge. Whenever you use a class that is not defined in the basic java.lang package , you 
need to use an import directive. 
-----------------------------------------------------------------------------------*/
import java.util.*;

/**
 * This program demonstrates console input.
 * @version 1.10 2004-02-10
 * @author Cay Horstmann
 */
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
