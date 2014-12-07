/*******************************************************************************
stream:
    A stream is a flow of characters (or other kind of data). 
input stream:
    If the flow is into your program, the stream is called an input stream. 
output stream:
    If the flow is out of your program, the stream is called an output stream.


The @cin that you have already used is an input stream connected to the keyboard,
and @cout is an output stream connected to the screen. These two streams are 
automatically available to your program, as long as it has an include directive 
that names the header file iostream. Once the streams are connected to the desired 
files, your program can do file I/O the same way it does I/O using the keyboard 
and screen.

In C++, a stream is a special kind of variable known as an object. The streams 
@cin and @cout are already declared for you, but if you want a stream to connect 
to a file, you must declare it just as you would declare any other variable. 
        ifstream in_stream;
        ofstream out_stream;
The types ifstream and ofstream are defined in the library with the header file 
fstream, 
        #include <fstream>
        using namespace std;


opening the file 
    Stream variables, such as in_stream and out_stream declared earlier, must
    each be connected to a file. This is called opening the file and is done 
    with a function named open. For example, suppose you want the input stream
    in_stream connected to the file named infile.dat. Your program must then
    contain the following before it reads any input from this file:
        in_stream.open("infile.dat");
        
Once you have declared an input stream variable and connected it to a file using 
the open function, your program can take input from the file using the extraction 
operator >>. For example, 
        int one_number, another_number;
        in_stream >> one_number >> another_number;
Every file should be closed when your program is finished getting input from the 
file or sending output to the file. 
        in_stream.close( );
Notice that the function close takes no arguments. If your program ends normally 
but without closing a file, the system will automatically close the file for you.

A File Has Two Names
Every input and every output file used by your program has two names. The external 
file name is the real name of the file, but it is used only in the call to the 
function open, which connects the file to a stream. After the call to open, you 
always use the stream name as the name of the file.

Appending to a File
If you want to append data to a file so that it goes after any existing
contents of the file, open the file as follows.
        Output_Stream.open(File_Name, ios::app);
EXAMPLE
        ofstream outStream;
        outStream.open("important.txt", ios::app);
ios::app is a special constant that is defined in iostream and so requires the 
following include directive:#include <iostream>


If the file does not exist, this will create an empty file with that name to 
receive your program's output, but if the file already exists, then all the 
output from your program will be appended to the end of the file, so that old 
data in the file is not lost. 

********************************************************************************
The member function get takes one argument, which should be a variable of type 
char. That argument receives the input character that is read from the input stream. 
For example, the following reads in the next input character from the keyboard and 
stores it in the variable next_symbol:
        char next_symbol;
        cin.get(next_symbol);
It is important to note that your program can read any character in this way. 

The Member Function put
Every output stream has a member function named put. The member function put takes 
one argument which should be an expression of type char. When the member function 
put is called, the value of its argument (called Char_Expression below) is output 
to the output stream.
SYNTAX
        Output_Stream.put(Char_Expression);
EXAMPLES
        cout.put(next_symbol);
        cout.put('a');
If you wish to use put to output to a file, you use an output-file stream in place 
of the stream cout. For example, if out_stream is an output stream for a file, then 
the following will output the character 'Z' to the file connected to out_stream:
        out_stream.put('Z');
Before you can use put with an output-file stream, such as out_stream, your program 
must first connect the stream to the output file with a call to the member function 
open.

If your program uses cin.get or cout.put, then just as with other uses of cin and 
cout, your program should include the following directive:
        #include <iostream>
Similarly, if your program uses get for an input-file stream or put for an output-file 
stream, then just as with any other file I/O, your program should contain the following 
directive:
        #include <fstream>

*/
