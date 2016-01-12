/*-----------------------------------------------------------------------------------
 java.util
 Class Arrays

 java.lang.Object
   java.util.Arrays

 An array is a data structure that stores a collection of values of the same type. Y-
 ou access each individual value through an integer index. For example, if a is an  -
 array of integers, then a[i] is the ith integer in the array.

 Declare an array variable by specifying the array type -- which is the element  type 
 followed by [] -- and the array variable name. For example, here is the  declaration 
 of an array a of integers:
 > int[] a;
 However, this statement only declares the variable a. It does not yet initialize a -
 with an actual array. Use the new operator to create the array.
 > int[] a = new int[100];
 This statement declares and initializes an array of 100 integers. The array length -
 need not be a constant: 
 > new int[n]  # creates an array of length n.

 When you create an array of numbers, all elements are initialized with zero.  Arrays 
 of boolean are initialized with false. Arrays of objects are initialized with the s-
 pecial value null, which indicates that they do not (yet) hold any objects. 

 If you construct an array with 100 elements and then try to access the element     -
 a[100] (or any other index outside the range 0 . . . 99), your program will termina-
 te with an "array index out of bounds" exception.

 Once you create an array, you cannot change its size (although you can, of course, -
 change an individual array element). If you frequently need to expand the size of an 
 array while your program is running, you should use a different data structure call-
 ed an array list. 

 To find the number of elements of an array, use array .length. For example:
     for (int i = 0; i < a.length; i++)
        System.out.println(a[i]);

 ----------------------------------------------------------------------------------*/
public class Arrays extends Object /* java.util.Arrays */
{

/*-----------------------------------------------------------------------------------
 Parameters:
 a - the array whose string representation to return
 Returns:
 a string representation of a

 Returns a string representation of the contents of the specified array. The string -
 representation consists of a list of the array's elements, enclosed in square brack-
 ets ("[]"). Adjacent elements are separated by the characters ", " (a comma followed 
 by a space). Elements are converted to strings as by String.valueOf(byte). Returns -
 "null" if a is null.

 Since:
 1.5
 ----------------------------------------------------------------------------------*/
public static String toString(byte[] a);

}

