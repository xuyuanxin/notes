
public class OutputStream { /* java.io.FileInputStream 1.0 */
FileInputStream(String name);
FileInputStream(File file);

}

public class FileOutputStream { /* java.io.FileOutputStream 1.0 */
FileOutputStream(String name);
FileOutputStream(String name, boolean append);
FileOutputStream(File file);
FileOutputStream(File file, boolean append);

}

public class BufferedInputStream { /* java.io.BufferedInputStream 1.0 */
BufferedInputStream(InputStream in);

}

public class BufferedOutputStream  { /* java.io.BufferedOutputStream  1.0 */
BufferedOutputStream(OutputStream out);

}

public class PushbackInputStream  { /* java.io.PushbackInputStream  1.0 */
PushbackInputStream(InputStream in);
PushbackInputStream(InputStream in, int size);
void unread(int b);
}

