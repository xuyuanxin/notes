/* 
 http://docs.oracle.com/javase/8/docs/api/java/lang/reflect/package-frame.html
*/


/*
 The AccessibleObject class is the base class for Field, Method and Constructor objects. 
*/
public class AccessibleObject extends Object implements AnnotatedElement
{

/*
 Set the accessible flag for this object to the indicated boolean value. A value of -
 true indicates that the reflected object should suppress Java language access check-
 ing when it is used. A value of false indicates that the reflected object should en-
 force Java language access checks.
*/
public void setAccessible(boolean flag) throws SecurityException;

}
