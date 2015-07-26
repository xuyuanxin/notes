/*-----------------------------------------------------------------------------------
 In Java, all values are written in the big-endian fashion, regardless of the proces-
 sor. That makes Java data files platform-independent.

 The DataInputStream class implements the DataInput interface. To read binary data f-
 rom a file, combine a DataInputStream with a source of bytes such as a             -
 FileInputStream:
     DataInputStream in = new DataInputStream(new FileInputStream("xxx.dat"));
 Similarly, to write binary data, use the DataOutputStream class that implements  the 
 DataOutput interface:
     DataOutputStream out = new DataOutputStream(new FileOutputStream("xxx.dat"));
 ----------------------------------------------------------------------------------*/
public interface DataInput /* java.io */
{ 

/* reads in a value of the given type. */
boolean readBoolean();
byte readByte();
char readChar();
double readDouble();

/* reads bytes into the array b, blocking until all bytes are read. */
void readFully(byte[] b);

/*-----------------------------------------------------------------------------------
 Parameters:
 b - the buffer into which the data is read.
 off - an int specifying the offset into the data.
 len - an int specifying the number of bytes to read.

 reads bytes into the array b, blocking until all bytes are read. 
 ----------------------------------------------------------------------------------*/
void readFully(byte[] b, int off, int len);

float readFloat();

/*-----------------------------------------------------------------------------------
 Reads four input bytes and returns an int value. Let a-d be the first through fourth 
 bytes read. The value returned is:

 (((a & 0xff) << 24) | ((b & 0xff) << 16) | ((c & 0xff) <<  8) | (d & 0xff))
 
 This method is suitable for reading bytes written by the writeInt method of interfa-
 ce DataOutput.

 Returns: the int value read.
 Throws:
 EOFException - if this stream reaches the end before reading all the bytes.
 IOException - if an I/O error occurs.
 ----------------------------------------------------------------------------------*/
int readInt() throws IOException;

long readLong();
short readShort();

/* reads a string of characters in the "modified UTF-8" format. */
String readUTF();

/* skips n bytes, blocking until all bytes are skipped. */
int skipBytes(int n);

}


	
public class DataOutput { /* java.io.DataOutput 1.0 */
	
/* writes a value of the given type. */
void writeBoolean(boolean b);
void writeByte(int b);
void writeChar(int c);
void writeDouble(double d);
void writeFloat(float f);
void writeInt(int i);
void writeLong(long l);
void writeShort(int s);

/* writes all characters in the string. */
void writeChars(String s);

/* writes a string of characters in the "modified UTF-8" format. */
void writeUTF(String s);

}




public class DataOutputStream { /*  */
}
