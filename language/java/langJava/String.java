
/* java.lang.String */
public final class String extends Object implements Serializable, Comparable<String>, CharSequence
{

/* Constructs a new String by decoding the specified subarray of bytes using the platform's default charset. */
String(byte[] bytes, int offset, int length);

/*-----------------------------------------------------------------------------------
 Parameters:
 bytes - The bytes to be decoded into characters
 offset - The index of the first byte to decode
 length - The number of bytes to decode
 charset - The charset to be used to decode the bytes

 Constructs a new String by decoding the specified subarray of bytes using the speci-
 fied charset. The length of the new String is a function of the charset, and hence -
 may not be equal to the length of the subarray.
 This method always replaces malformed-input and unmappable-character sequences  with 
 this charset's default replacement string. The CharsetDecoder class should be used -
 when more control over the decoding process is required.

 String str = new String(response.getData(), 0, response.getLength(),  "US-ASCII");
 ----------------------------------------------------------------------------------*/
public String(byte[] bytes, int offset, int length, Charset charset);

/*----------------------------------------------------------------------------------- 
 Encodes this String into a sequence of bytes using the platform's default charset, -
 storing the result into a new byte array. 
 ----------------------------------------------------------------------------------*/
byte[]	getBytes();

/*-----------------------------------------------------------------------------------
 Parameters:
 charsetName - The name of a supported charset
 Returns:
 The resultant byte array

 Encodes this String into a sequence of bytes using the named charset, storing the r-
 esult into a new byte array.
 The behavior of this method when this string cannot be encoded in the given  charset 
 is unspecified. The CharsetEncoder class should be used when more control over the -
 encoding process is required.
 
 byte[] data = daytime.getBytes("US-ASCII");
 ----------------------------------------------------------------------------------*/
public byte[] getBytes(String charsetName) throws UnsupportedEncodingException;


/*----------------------------------------------------------------------------------- 
 Returns the length of this string. The length is equal to the number of Unicode code 
 units in the string. 
 -----------------------------------------------------------------------------------*/
public int length();


}

