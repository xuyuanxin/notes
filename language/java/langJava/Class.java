//  http://docs.oracle.com/javase/8/docs/api/java/lang/Class.html

/* java.lang.String */
public final class Class<T>
extends Object
implements Serializable, GenericDeclaration, Type, AnnotatedElement
{

/*-----------------------------------------------------------------------------------
 Returns the @Class object associated with the class or interface with the given str-
 ing name

 For example, the following code fragment returns the runtime @Class descriptor for -
 the class named java.lang.Thread:
 
 Class t = Class.forName("java.lang.Thread")
 
 A call to forName("X") causes the class named X to be initialized.
 ----------------------------------------------------------------------------------*/
public static Class<?> forName(String className) throws ClassNotFoundException;


/*-----------------------------------------------------------------------------------
 Returns the name of the entity (class, interface, array class, primitive type, or v-
 oid) represented by this @Class object, as a String.

 Examples:

 String.class.getName()
     returns "java.lang.String"
 byte.class.getName()
     returns "byte"
 (new Object[3]).getClass().getName()
     returns "[Ljava.lang.Object;"
 (new int[3][4][5][6][7][8][9]).getClass().getName()
     returns "[[[[[[[I"
 ----------------------------------------------------------------------------------*/
public String getName();



}

