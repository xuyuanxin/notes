/*-----------------------------------------------------------------------------------
 ----> input stream; output stream; InputStream and OutputStream classes
 In the Java API, an object from which we can read a sequence of bytes is called an -
 input stream. An object to which we can write a sequence of bytes is called an outp-
 ut stream. These sources and destinations of byte sequences can be (and often are) -
 files, but they can also be network connections and even blocks of memory. The abst-
 ract classes InputStream and OutputStream form the basis for a hierarchy of input/o-
 utput (I/O) classes

 ----> Reader and Writer classes
 Byte-oriented streams are inconvenient for processing information stored in  Unicode 
 (recall that Unicode uses multiple bytes per character). Therefore, a separate hier-
 archy provides classes for processing Unicode characters that inherit from the abst-
 ract Reader and Writer classes. These classes have read and write operations that a-
 re based on two-byte Unicode code units rather than on single-byte characters. 
------------------------------------------------------------------------------------


 ------------------------------------------------------------------------------------
 Byte-oriented streams are inconvenient for processing information stored in  Unicode 
 (recall that Unicode uses multiple bytes per character). Therefore, a separate hier-
 archy provides classes for processing Unicode characters that inherit from the abst-
 ract Reader and Writer classes. These classes have read and write operations that a-
 re based on two-byte Unicode code units rather than on single-byte characters.
     abstract int read()
     abstract void write(int c)
 The read method returns either a Unicode code unit (as an integer between 0 and    -
 65535) or -1 when you have reached the end of the file. The write method is called -
 with a Unicode code unit.
 
 ------------------------------------------------------------------------------------
 There are four additional interfaces: Closeable, Flushable, Readable,and Appendable.
 The first two interfaces are very simple, with methods
     void close() throws IOException
 and
     void flush()
 respectively. The classes InputStream, OutputStream, Reader, and Writer all impleme-
 nt the Closeable interface. 

 Note
     The java.io.Closeable interface extends the java.lang.AutoCloseable interface. -
     Therefore, you can use the try-with-resources statement with any Closeable.  Why 
     have two interfaces? The close method of the Closeable interface only throws an
     IOException, whereas the AutoCloseable.close method may throw any exception.

 OutputStream and Writer implement the Flushable interface. The Readable interface h-
 as a single method
     int read(CharBuffer cb)
 The CharBuffer class has methods for sequential and random read/write access. It re-
 presents an in-memory buffer or a memory-mapped file.  

 The @Appendable interface has two methods for appending single characters and chara-
 cter sequences:
     Appendable append(char c)
     Appendable append(CharSequence s)
 The CharSequence interface describes basic properties of a sequence of char  values. 
 It is implemented by String, CharBuffer, StringBuilder, and StringBuffer. Of the st-
 ream zoo classes, only @Writer implements @Appendable.

 ------------------------------------------------------------------------------------
 java.io.Closeable 5.0
? void close()
closes this Closeable. This method may throw an IOException.
java.io.Flushable 5.0
? void flush()
flushes this Flushable.
java.lang.Readable 5.0
? int read(CharBuffer cb)
attempts to read as many char values into cb as it can hold. Returns the number of values read, or -1 if no further values are available
from this Readable.
java.lang.Appendable 5.0
? Appendable append(char c)
? Appendable append(CharSequence cs)
appends the given code unit, or all code units in the given sequence, to this Appendable; returns this.
java.lang.CharSequence 1.4
? char charAt(int index)
returns the code unit at the given index.
? int length()
returns the number of code units in this sequence.
? CharSequence subSequence(int startIndex, int endIndex)
returns a CharSequence consisting of the code units stored at index startIndex to endIndex - 1.
? String toString()
returns a string consisting of the code units of this sequence.

 ------------------------------------------------------------------------------------
 FileInputStream and FileOutputStream
 
 ------------------------------------------------------------------------------------
 When saving data, you have the choice between binary and text formats. For  example, 
 if the integer 1234 is saved in binary, it is written as the sequence of bytes 00 00 
 04 D2 (in hexadecimal notation). In text format, it is saved as the string "1234". 

 ----------------------------------------------------------------------------------*/


public class InputStream { /* java.io.InputStream 1.0 */
/*-----------------------------------------------------------------------------------
 This method reads one byte and returns the byte that was read, or -1 if it encounte-
 rs the end of the input source. The designer of a concrete input stream class overr-
 ides this method to provide useful functionality.For example, in the FileInputStream 
 class, this method reads one byte from a file. System.in is a predefined object of a 
 subclass of InputStream that allows you to read information from the keyboard.

 Similarly, the OutputStream class defines the abstract method
     abstract void write(int b)
 which writes one byte to an output location.

 Both the read and write methods block until the byte is actually read or written. T-
 his means that if the stream cannot immediately be accessed (usually because of a b-
 usy network connection), the current thread blocks. 
 ----------------------------------------------------------------------------------*/
abstract int read();

/*-----------------------------------------------------------------------------------
 reads into an array of bytes and returns the actual number of bytes read, or -1 at -
 the end of the stream; this method reads at most b.length bytes.
 ----------------------------------------------------------------------------------*/
int read(byte[] b);

/*-----------------------------------------------------------------------------------
 @b: The array into which the data is read
 @off: The offset into @b where the first bytes should be placed
 @len: The maximum number of bytes to read
 
 reads into an array of bytes and returns the actual number of bytes read, or -1 at -
 the end of the stream.
 ----------------------------------------------------------------------------------*/
int read(byte[] b, int off, int len);

/*-----------------------------------------------------------------------------------
 skips n bytes in the input stream, returns the actual number of bytes skipped (which 
 may be less than n if the end of the stream was encountered).
 ----------------------------------------------------------------------------------*/
long skip(long n);

/*----------------------------------------------------------------------------------- 
 The available method lets you check the number of bytes that are currently available 
 for reading. This means a fragment like the following is unlikely to block:
     int bytesAvailable = in.available();
     if (bytesAvailable > 0)
     {
         byte[] data = new byte[bytesAvailable];
         in.read(data);
     }
 ----------------------------------------------------------------------------------*/
int available();

/*----------------------------------------------------------------------------------- 
 When you have finished reading or writing to a stream,close it by calling the @close 
 method.This call frees up the operating system resources that are in limited supply. 
 Closing an output stream also flushes the buffer used for the output stream. You can 
 also manually flush the output with the @flush method.
 ----------------------------------------------------------------------------------*/
void close();

/*-----------------------------------------------------------------------------------
 puts a marker at the current position in the input stream (not all streams support -
 this feature). If more than readlimit bytes have been read from the input stream, t-
 he stream is allowed to forget the marker.
 ----------------------------------------------------------------------------------*/
void mark(int readlimit);

/*-----------------------------------------------------------------------------------
 returns to the last marker. Subsequent calls to read reread the bytes. If there is -
 no current marker, the stream is not reset.
 ----------------------------------------------------------------------------------*/
void reset();

/* returns true if the stream supports marking. */
boolean markSupported();

}


public class OutputStream { /* java.io.OutputStream 1.0 */

/* look InputStream.read */
abstract void write(int n);

void write(byte[] b);

void write(byte[] b, int off, int len);

void close();

void flush();

}

