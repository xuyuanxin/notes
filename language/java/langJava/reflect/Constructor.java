/*  
 http://docs.oracle.com/javase/8/docs/api/java/lang/reflect/Constructor.html
 java.lang.reflect.Constructor<T>
 eg: ReflectionJava.java
 */

/* java.lang.reflect.Constructor<T> */
public final class Constructor<T> extends Executable
{

/*
 Returns the Java language modifiers for the executable represented by this object.
*/
public int getModifiers();


/*
 Returns the name of this constructor, as a string. This is the binary name of the c-
 onstructor's declaring class.
*/
public String getName();


/*
 @return:
  the parameter types for the executable this object represents.
 */
public Class<?>[] getParameterTypes();


}

