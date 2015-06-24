/*-----------------------------------------------------------------------------------
 The Scanner class is defined in the java.util package. Whenever you use a class that 
 is not defined in the basic java.lang package , you need to use an import directive. 
 ----------------------------------------------------------------------------------*/
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
public class ScannerJava
{
   public static void main(String[] args)
   {
      Scanner in = new Scanner(System.in);
      
      System.out.print("What is your name? ");
      String name = in.nextLine(); // get first input

      System.out.print("How old are you? ");
      int age = in.nextInt();     // get second input

      System.out.println("Hello, " + name + ". Next year, you'll be " + (age + 1));
   }
}

/*-----------------------------------------------------------------------------------
 ----> File Input and Output
 To read from a file, construct a Scanner object like this:
     Scanner in = new Scanner(Paths.get("myfile.txt"));
 If the file name contains backslashes, remember to escape each of them with an addi-
 tional backslash: "c:\\mydirectory\\myfile.txt".

 Now you can read from the file, using any of the Scanner methods that we already de-
 scribed.

 To write to a file, construct a PrintWriter object. In the constructor, simply supp-
 ly the file name:
     PrintWriter out = new PrintWriter("myfile.txt");
 If the file does not exist, it is created. You can use the print, println,and printf
 commands as you did when printing to System.out.

 Caution
 You can construct a Scanner with a string parameter, but the scanner interprets  the
 string as data, not a file name. For example, if you call
     Scanner in = new Scanner("myfile.txt"); // ERROR?
 then the scanner will see ten characters of data: 'm', 'y', 'f', and so on. That  is
 probably not what was intended in this case.

 Note
 When you specify a relative file name,such as "myfile.txt","mydirectory/myfile.txt", 
 or "../myfile.txt", the file is located relative to the directory in which the  Java 
 virtual machine was started. If you launched your program from a command shell, by -
 executing
     java MyProg
 then the starting directory is the current directory of the command shell.  However, 
 if you use an integrated development environment, the starting directory is control-
 led by the IDE. You can find the directory location with this call:
     String dir = System.getProperty("user.dir");
 If you run into grief with locating files, consider using absolute path names such -
 as "c:\\mydirectory\\myfile.txt" or "/home/me/mydirectory/myfile.txt". 
 ----------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------
 java.util.Scanner 5.0
 
 ----> Scanner(InputStream in)
 constructs a Scanner object from the given input stream.
 ----> Scanner(Path p)
 constructs a Scanner that reads data from the given path.
 ----> Scanner(String data)
 constructs a Scanner that reads data from the given string.
 
 ----> String nextLine()
 reads the next line of input.
 
 ----> String next()
 reads the next word of input (delimited by whitespace).
 
 ----> int nextInt()
 ----> double nextDouble()
 reads and converts the next character sequence that represents an integer or floati-
 ng-point number.
 
 ----> boolean hasNext()
 tests whether there is another word in the input.
 
 ----> boolean hasNextInt()
 ----> boolean hasNextDouble()
 tests whether the next character sequence represents an integer or floating-point n-
 umber.



 java.lang.System 1.0
? static Console console() 6
returns a Console object for interacting with the user through a console window if
such an interaction is possible, null otherwise. A Console object is available for any
program that is launched in a console window. Otherwise, the availability is systemdependent.
java.io.Console 6
? static char[] readPassword(String prompt, Object... args)
? static String readLine(String prompt, Object... args)
 displays the prompt and reads the user input until the end of the input line. The args
 parameters can be used to supply formatting arguments, as described in the next
 section.

 java.io.PrintWriter 1.1
 ? PrintWriter(String fileName)
 constructs a PrintWriter that writes data to the file with the given file name.


 java.nio.file.Paths 7
 ? static Path get(String pathname)
 constructs a Path from the given path name.

 ----------------------------------------------------------------------------------*/
