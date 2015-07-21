
/*-----------------------------------------------------------------------------------
 The OutputStreamWriter class turns a stream of Unicode code units into a stream of -
 bytes, using a chosen character encoding. Conversely, the InputStreamReader class t-
 urns an input stream that contains bytes (specifying characters in some character e-
 ncoding) into a reader that emits Unicode code units.
 For example, here is how you make an input reader that reads keystrokes from the co-
 nsole and converts them to Unicode:
     InputStreamReader in = new InputStreamReader(System.in);
 This input stream reader assumes the default character encoding used by the host sy-
 stem, such as the ISO 8859-1 encoding in Western Europe. You can choose a  different 
 encoding by specifying it in the constructor for the InputStreamReader, for example:
     InputStreamReader in = new InputStreamReader(new FileInputStream("kremlin.dat")\
                                                  , "ISO8859_5");
 ----------------------------------------------------------------------------------*/

