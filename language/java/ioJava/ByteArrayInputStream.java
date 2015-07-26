/*-----------------------------------------------------------------------------------
 java.lang.Object
   java.io.InputStream
     java.io.ByteArrayInputStream

 A ByteArrayInputStream contains an internal buffer that contains bytes that may be -
 read from the stream. An internal counter keeps track of the next byte to be suppli-
 ed by the read method. Closing a ByteArrayInputStream has no effect. The methods  in 
 this class can be called after the stream has been closed without generating an    -
 IOException.
 ----------------------------------------------------------------------------------*/
public class ByteArrayInputStream extends InputStream /* java.io.ByteArrayInputStream */
{

/*-----------------------------------------------------------------------------------
 Parameters:
 buf - the input buffer.

 Creates a ByteArrayInputStream so that it uses @buf as its buffer array. The  buffer 
 array is not copied. The initial value of pos is 0 and the initial value of count is 
 the length of @buf.
 ----------------------------------------------------------------------------------*/
public ByteArrayInputStream(byte[] buf);


/*----------------------------------------------------------------------------------- 
 Parameters:
 buf - the input buffer.
 offset - the offset in the buffer of the first byte to read.
 length - the maximum number of bytes to read from the buffer.

 Creates ByteArrayInputStream that uses @buf as its buffer array. The initial value -
 of pos is @offset and the initial value of count is the minimum of offset+length and 
 buf.length. The buffer array is not copied. The buffer's mark is set to the specifi-
 ed offset.
 ----------------------------------------------------------------------------------*/
ByteArrayInputStream(byte[] buf, int offset, int length);


}

