/*-----------------------------------------------------------------------------------
 In the Java API, an object from which we can read a sequence of bytes is called an -
 input stream. An object to which we can write a sequence of bytes is called an outp-
 ut stream. These sources and destinations of byte sequences can be (and often are) -
 files, but they can also be network connections and even blocks of memory. The abst-
 ract classes InputStream and OutputStream form the basis for a hierarchy of input/o-
 utput (I/O) classes

 ----> abstract int read()
 The InputStream class has an abstract method:abstract int read(). This method  reads 
 one byte and returns the byte that was read, or -1 if it encounters the end of the -
 input source. The designer of a concrete input stream class overrides this method to 
 provide useful functionality. 

 ----> abstract void write(int b)
 the OutputStream class defines the abstract method: abstract void write(int b). whi-
 ch writes one byte to an output location. Both the read and write methods block unt-
 il the byte is actually read or written. 

 ----> available
 The @available method lets you check the number of bytes that are currently availab-
 le for reading. This means a fragment like the following is unlikely to block:
 int bytesAvailable = in.available();
 if (bytesAvailable > 0)
 {
     byte[] data = new byte[bytesAvailable];
     in.read(data);
 }

 ----> close flush
 When you have finished reading or writing to a stream, close it by calling the     -
 @close method. This call frees up the operating system resources that are in limite-
 d supply. Closing an output stream also flushes the buffer used for the output stre-
 am. You can also manually flush the output with the @flush method. 

 ------------------------------------------------------------------------------------
 java.io.InputStream 1.0
 ----> abstract int read()
 reads a byte of data and returns the byte read; returns -1 at the end of the stream.
       int read(byte[] b)
 reads into an array of bytes and returns the actual number of bytes read, or -1 at -
 the end of the stream; this method reads at most b.length bytes.
       int read(byte[] b, int off, int len)
 reads into an array of bytes and returns the actual number of bytes read, or -1 at -
 the end of the stream.

 ----> long skip(long n)
 skips n bytes in the input stream, returns the actual number of bytes skipped (which 
 may be less than n if the end of the stream was encountered).

 ----> int available()
 returns the number of bytes available, without blocking (recall that blocking  means 
 that the current thread loses its turn).

 ----> void close()
 closes the input stream.

 ----> void mark(int readlimit)
 puts a marker at the current position in the input stream (not all streams support -
 this feature). If more than readlimit bytes have been read from the input stream,  -
 the stream is allowed to forget the marker.

 ----> void reset()
 returns to the last marker. Subsequent calls to read reread the bytes. If there is -
 no current marker, the stream is not reset.

 ----> boolean markSupported()
 returns true if the stream supports marking.
 
------------------------------------------------------------------------------------
java.io.OutputStream 1.0
 ----> abstract void write(int n)
 writes a byte of data.
       void write(byte[] b)
       void write(byte[] b, int off, int len)
 writes all bytes or a range of bytes in the array b.
 
 ----> void close()
 flushes and closes the output stream.

 ----> void flush()
 flushes the output stream¡ªthat is, sends any buffered data to its destination.


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
