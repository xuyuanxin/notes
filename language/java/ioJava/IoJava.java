/*-----------------------------------------------------------------------------------
 ----> Text Input and Output
 When saving data, you have the choice between binary and text formats. For  example, 
 if the integer 1234 is saved in binary, it is written as the sequence of bytes	 -
 00 00 04 D2 (in hexadecimal notation). In text format, it is saved as the string	 -
 "1234". Although binary I/O is fast and efficient, it is not easily readable by hum-
 ans. When saving text strings, you need to consider the character encoding. In the -
 UTF-16 encoding, the string "1234" is encoded as 00 31 00 32 00 33 00 34 (in hex).

 OutputStreamWriter  

 ----> How to Write Text Output     TextFileTest
 PrintWriter

 ----> How to Read Text Input       TextFileTest
 You already know that:
 1 To write data in binary format, you use a DataOutputStream.
 2 To write in text format, you use a PrintWriter.
 However, before Java SE 5.0, the only game in town for processing text input was the
 BufferedReader class with the readLine method that lets you read a line of text. Yo-
 u need to combine a buffered reader with an input source.
     BufferedReader in = new BufferedReader( \
             new InputStreamReader(new FileInputStream("employee.txt"), "UTF-8));
 The readLine method returns null when no more input is available. A typical input l-
 oop, therefore, looks like this:
 while ((line = in.readLine()) != null)
 {
     do something with line
 }
 However, a BufferedReader has no methods for reading numbers. We suggest that you u-
 se a Scanner for reading text input.
 ----------------------------------------------------------------------------------*/
