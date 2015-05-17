/*-----------------------------------------------------------------------------------
 An array is a data structure that stores a collection of values of the same type. Y-
 ou access each individual value through an integer index. For example, if a is an a-
 rray of integers, then a[i] is the ith integer in the array.
 Declare an array variable by specifying the array type(which is the element type f-
 ollowed by []), and the array variable name. For example, here is the declaration -
 of an array a of integers:
     int[] a; // or int[] a;
 However, this statement only declares the variable a. It does not yet initialize a -
 with an actual array. Use the new operator to create the array.
     int[] a = new int[100];

 The array elements are numbered from 0 to 99 (and not 1 to 100). Once the array is -
 created, you can fill the elements in an array, for example, by using a loop:
     int[] a = new int[100];
     for (int i = 0; i < 100; i++)
         a[i] = i; // fills the array with numbers 0 to 99
         
 When you create an array of numbers, all elements are initialized with zero . Arrays 
 of boolean are initialized with false. Arrays of objects are initialized with the s-
 pecial value null, which indicates that they do not (yet) hold any objects. For exa-
 mple,
     String[] names = new String[10];
 creates an array of ten strings, all of which are null. If you want the array to ho-
 ld empty strings, you must supply them:
     for (int i = 0; i < 10; i++) names[i] = "";
     
 ----> Caution
 If you construct an array with 100 elements and then try to access the element 
 a[100] (or any other index outside the range 0~99), your program will terminate with 
 an "array index out of bounds" exception. To find the number of elements of an array, 
 use array .length. For example:
     for (int i = 0; i < a.length; i++)
         System.out.println(a[i]);



 ----------------------------------------------------------------------------------*/
