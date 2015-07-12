
/* Scanner in = new Scanner(System.in); */
public class Scanner { /* java.util.Scanner 5.0 */
/* constructs a Scanner object from the given input stream. */
Scanner(InputStream in);

/* reads the next line of input. */
String nextLine();

/* reads the next word of input (delimited by whitespace). */
String next();

/* reads and converts the next character sequence that represents an integer or floating-point number. */
int nextInt();
double nextDouble();

/* tests whether there is another word in the input. */
boolean hasNext();

/* tests whether the next character sequence represents an integer or floating-point number. */
boolean hasNextInt();
boolean hasNextDouble();
}

