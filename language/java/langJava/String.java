
/* java.lang.String */
public final class String extends Object implements Serializable, Comparable<String>, CharSequence
{

/* Constructs a new String by decoding the specified subarray of bytes using the platform's default charset. */
String(byte[] bytes, int offset, int length);

/*----------------------------------------------------------------------------------- 
 Encodes this String into a sequence of bytes using the platform's default charset, -
 storing the result into a new byte array. 
 ----------------------------------------------------------------------------------*/
byte[]	getBytes();



}

