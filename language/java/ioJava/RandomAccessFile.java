/*-----------------------------------------------------------------------------------
 ----> Random-Access Files
 The RandomAccessFile class lets you read or write data anywhere in a file. Disk fil-
 es are random-access, but streams of data from a network are not. You can open a   -
 random-access file either for reading only or for both reading and writing;  specify 
 the option by using the string "r" (for read access) or "rw" (for read/write access) 
 as the second argument in the constructor.
     RandomAccessFile in = new RandomAccessFile("employee.dat", "r");
     RandomAccessFile inOut = new RandomAccessFile("employee.dat", "rw");
 When you open an existing file as a RandomAccessFile, it does not get deleted.

 A random-access file has a file pointer that indicates the position of the next byt-
 e to be read or written. The seek method sets the file pointer to an arbitrary  byte 
 position within the file. The argument to @seek is a long integer between zero and -
 the length of the file in bytes. 

 The @getFilePointer method returns the current position of the file pointer. The   -
 RandomAccessFile class implements both the DataInput and DataOutput interfaces. To -
 read and write from a random-access file, use methods such as readInt/writeInt and -
 readChar/writeChar that we discussed in the preceding section.
 ----------------------------------------------------------------------------------*/
public class RandomAccessFile { /* java.io.RandomAccessFile 1.0 */
RandomAccessFile(String file, String mode);

/*-----------------------------------------------------------------------------------
 @file: The file to be opened
 @mode: "r" for read-only mode, "rw" for read/write mode, "rws" for read/write mode -
 with synchronous disk writes of data and memtadata for every updata, and "rwd" for -
 read/write mode with synchronous disk writes of data only.
 ----------------------------------------------------------------------------------*/
RandomAccessFile(File file, String mode);

/* returns the current location of the file pointer. */
long getFilePointer();

/* sets the file pointer to pos bytes from the beginning of the file. */
void seek(long pos);

/* returns the length of the file in bytes. */
long length()
}
