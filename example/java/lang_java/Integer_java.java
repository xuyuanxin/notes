/*-----------------------------------------------------------------------------------
 java.lang.Integer 1.0

 int intValue()
 returns the value of this Integer object as an int (overrides the intValue method in 
 the Number class).

 static String toString(int i)
 returns a new String object representing the number i in base 10.

 static String toString(int i, int radix)
 lets you return a representation of the number i in the base specified by the  radix 
 parameter.

 static int parseInt(String s)
 static int parseInt(String s, int radix)
 returns the integer whose digits are contained in the string s. The string must rep-
 resent an integer in base 10 (for the first method) or in the base given by the rad-
 ix parameter (for the second method).

 static Integer valueOf(String s)
 static Integer valueOf(String s, int radix)
 returns a new Integer object initialized to the integer whose digits are contained -
 in the string s. The string must represent an integer in base 10 (for the first met-
 hod) or in the base given by the radix parameter (for the second method).
 ----------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------
 ----> wrapper
 All primitive types have class counterparts. For example, a class Integer correspon-
 ds to the primitive type int. These kinds of classes are usually called wrappers. T-
 he wrapper classes have obvious names: Integer, Long, Float, Double, Short, Byte, C-
 haracter, Void, and Boolean. (The first six inherit from the common superclass Numb-
 er.) The wrapper classes are immutable, you cannot change a wrapped value after  the 
 wrapper has been constructed. They are also final, so you cannot subclass them.

 Suppose we want an array list of integers. Unfortunately, the type parameter  inside 
 the angle brackets cannot be a primitive type. It is not possible to form an ArrayL-
 ist<int>. Here, the Integer wrapper class comes in. It is OK to declare an array li-
 st of Integer objects.
     ArrayList<Integer> list = new ArrayList<>();

 ----> autoboxing unboxed
 The call
     list.add(3);
 is automatically translated to
     list.add(Integer.valueOf(3));
 This conversion is called autoboxing.

 Conversely, when you assign an Integer object to an int value, it is automatically -
 unboxed. That is, the compiler translates
     int n = list.get(i);
 into
     int n = list.get(i).intValue();
 you can apply the increment operator to a wrapper reference:
     Integer n = 3;
     n++;


 As you know, the == operator, applied to wrapper objects, only tests whether the ob-
 jects have identical memory locations. The following comparison would therefore pro-
 bably fail:
     Integer a = 1000;
     Integer b = 1000;
     if (a == b) . . .
 However, a Java implementation may, if it chooses, wrap commonly occurring values i-
 nto identical objects, and thus the comparison might succeed. This ambiguity is  not 
 what you want. The remedy is to call the equals method when comparing wrapper objec-
 ts.

 ----> Caution
 it is impossible to write a Java method that increments an integer parameter because 
 parameters to Java methods are always passed by value.
     public static void triple(int x) // won't work
     {
         x = 3 * x; // modifies local variable
     }
 Could we overcome this by using an Integer instead of an int?
     public static void triple(Integer x) // won't work
     {
        . . .
     }
 The problem is that Integer objects are immutable: The information contained  inside 
 the wrapper can't change. You cannot use these wrapper classes to create a method t-
 hat modifies numeric parameters.
 If you do want to write a method to change numeric parameters, you can use one of t-
 he holder types defined in the org.omg.CORBA package: IntHolder, BooleanHolder,  and 
 so on. Each holder type has a public (!) field value through which you can access t-
 he stored value.
     public static void triple(IntHolder x)
     {
         x.value = 3 * x.value;
     }
 ----------------------------------------------------------------------------------*/ 
