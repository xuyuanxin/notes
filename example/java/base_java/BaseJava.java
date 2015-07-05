/*-----------------------------------------------------------------------------------
 ----> Methods with a Variable Number of Parameters
 The printf method is defined like this:
     public class PrintStream
     {
         public PrintStream printf(String fmt, Object... args) 
         { 
             return format(fmt, args); 
         }
     }
 Here, the ellipsis ... is part of the Java code. It denotes that the method can rec-
 eive an arbitrary number of objects (in addition to the fmt parameter).
 The printf method actually receives two parameters:the format string and an Object[] 
 array that holds all other parameters. (If the caller supplies integers or other pr-
 imitive type values, autoboxing turns them into objects.) The compiler needs to tra-
 nsform each call to printf, bundling the parameters into an array and autoboxing  as 
 necessary:
     System.out.printf("%d %s", new Object[] { new Integer(n), "widgets" } );
 You can define your own methods with variable parameters, and you can specify any t-
 ype for the parameters, even a primitive type. Here is a simple example: a  function 
 that computes the maximum of a variable number of values.
     public static double max(double... values)
     {
         double largest = Double.MIN_VALUE;
         for (double v : values) if (v > largest) largest = v;
         return largest;
     }
 Simply call the function like this:
     double m = max(3.1, 40.4, -5);
 The compiler passes a "new double[] { 3.1, 40.4, -5 }" to the max function.

 It is legal to pass an array as the last parameter of a method with variable parame-
 ters. For example:
     System.out.printf("%d %s", new Object[] { new Integer(1), "widgets" } );
 Therefore, you can redefine an existing function whose last parameter is an array to 
 a method with variable parameters, without breaking any existing code. For  example,
 MessageFormat.format was enhanced in this way in Java SE 5.0. If you like, you can -
 even declare the main method as
     public static void main(String... args)
 ----------------------------------------------------------------------------------*/
