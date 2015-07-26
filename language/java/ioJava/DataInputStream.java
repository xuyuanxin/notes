
/*-----------------------------------------------------------------------------------
 java.lang.Object
   java.io.InputStream
     java.io.FilterInputStream
       java.io.DataInputStream

 ----------------------------------------------------------------------------------*/

public class DataInputStream extends FilterInputStream implements DataInput /* java.io.DataInputStream */
{ 

/*-----------------------------------------------------------------------------------
 Parameters:
 in - the specified input stream

 Creates a DataInputStream that uses the specified underlying InputStream.
 ----------------------------------------------------------------------------------*/
public DataInputStream(InputStream in);

/* See the general contract of the readFully method of DataInput.readFully() */
public final void readFully(byte[] b, int off, int len) throws IOException;

/* See the general contract of the readInt method of DataInput. */
public final int readInt() throws IOException;

/* See the general contract of the readUTF method of DataInput. */
public final String readUTF() throws IOException;




}

