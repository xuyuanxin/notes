public class PrintWriter { /* java.io.PrintWriter 1.1 */

/* creates a new PrintWriter. */
PrintWriter(Writer out);
PrintWriter(Writer out, boolean autoFlush);

/*-----------------------------------------------------------------------------------
 autoflush: If true, the println methods will flush the output buffer(default:false)

 creates a new PrintWriter from an existing OutputStream by creating the necessary  -
 intermediate OutputStreamWriter.
 ----------------------------------------------------------------------------------*/
PrintWriter(OutputStream out);
PrintWriter(OutputStream out, boolean autoflush);

/* constructs a PrintWriter that writes data to the file with the given file name. */
PrintWriter(String filename);

/*-----------------------------------------------------------------------------------
 creates a new PrintWriter that writes to the given file by creating the necessary  -
 intermediate FileWriter.
 ----------------------------------------------------------------------------------*/
PrintWriter(File file);

/* prints an object by printing the string resulting from toString. */
void print(Object obj);

/* prints a string containing Unicode code units. */
void print(String s);

/*-----------------------------------------------------------------------------------
 prints a string followed by a line terminator. Flushes the stream if the stream is -
 in autoflush mode.
 The println method adds the correct end-of-line character for the target system    -
 ("\r\n" on Windows, "\n" on UNIX) to the line. This is the string obtained by the c-
 all System.getProperty("line.separator").
 ----------------------------------------------------------------------------------*/
void println(String s);

/*prints all Unicode code units in the given array.*/
void print(char[] s);

/* prints a Unicode code unit. */
void print(char c);

/* prints the given value in text format. */
void print(int i);
void print(long l);
void print(float f);
void print(double d);
void print(boolean b);

/* prints the given values as specified by the format string. */
void printf(String format, Object... args);

/*-----------------------------------------------------------------------------------
 returns true if a formatting or output error occurred. Once the stream has encounte-
 red an error, it is tainted and all calls to checkError return true. 
 ----------------------------------------------------------------------------------*/
boolean checkError();

}

