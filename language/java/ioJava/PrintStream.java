
/*-----------------------------------------------------------------------------------
 java.lang.Object
   java.io.OutputStream
     java.io.FilterOutputStream
       java.io.PrintStream


 ----------------------------------------------------------------------------------*/
public class PrintStream extends FilterOutputStream implements Appendable, Closeable
{

/* System.out.printf("%,.2f", 10000.0 / 3.0); */
public PrintStream printf(Locale l, String format, Object... args);

}
