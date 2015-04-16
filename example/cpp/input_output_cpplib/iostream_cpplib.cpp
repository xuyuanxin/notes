/*-----------------------------------------------------------------------------------
cin   an istream object that reads the standard input
cout  an ostream object that writes to the standard output
cerr  an ostream object, typically used for program error messages, that writes to t-
      he standard error

To support these different kinds of IO processing, the library defines a collection -
of IO types. These types, are defined in three separate headers: 
iostream : defines the basic types used to read from and write to a stream
fstream  : defines the types used to read and write named files
sstream  : defines the types used to read and write in-memory strings.

To support languages that use wide characters, the library defines a set of types an-
d objects that manipulate wchar_t data. The names of the widecharacter versions begi-
n with a w. For example, wcin, wcout, and wcerr are the wide-character objects that -
correspond to cin, cout, and cerr, respectively. The wide-character types and objects 
are defined in the same header as the plain char types. For example, the fstream hea-
der defines both the ifstream and wifstream types.

The types ifstream and istringstream inherit from istream. Thus, we can use objects -
of type ifstream or istringstream as if they were istream objects. We can use objects 
of these types in the same ways as we have used cin. For example, we can call getline 
on an ifstream or istringstream object, and we can use the >> to read data from an  -
ifstream or istringstream. Similarly, the types ofstream and ostringstream inherit f-
rom ostream. Therefore, we can use objects of these types in the same ways that we h-
ave used cout.
        istream                          ostream
           |                                |
   ifstream istringstream           ofstream ostringstream


----> No Copy or Assign for IO Objects
ofstream out1, out2;
out1 = out2;              // error: cannot assign stream objects
ofstream print(ofstream); // error: can't initialize the ofstream parameter
out2 = print(out2);       // error: cannot copy stream objects

Because we can't copy the IO types, we cannot have a parameter or return type that i-
s one of the stream types . Functions that do IO typically pass and return the stream 
through references. Reading or writing an IO object changes its state, so the refere-
nce must not be const.

----> Condition States
strm::iostate  
    strm is one of the IO types(iostream fstream sstream). iostate is a machine depe-
    ndent integral type that represents the condition state of a stream.
strm::badbit
    used to indicate that a stream is corrupted . The badbit indicates a system-level 
    failure, such as an unrecoverable read or write error. It is usually not possible 
    to use a stream once badbit has been set. 
strm::failbit
    used to indicate that an IO operation failed. The failbit is set after a recover-
    able error, such as reading a character when numeric data was expected. It is of-
    ten possible to correct such problems and continue using the stream. 
strm::eofbit
    used to indicate that a stream hit end-of-file. Reaching end-of-file sets both  -
    eofbit and failbit. 
strm::goodbit
    used to indicate that a stream is not in an error state. This value is guarante-
    ed to be zero.
s.eof()
    true if eofbit in the stream s is set.
s.fail()
    true if failbit or badbit in the stream s is set.
s.bad()
    true if badbit in the stream s is set.
s.good()
    true if the stream s is in avalid state.
s.clear()
    Reset all condition values in the stream s to valid state. Return void.
s.clear(flags)
    Reset the condition of s to flags. Type of flags is strm::iostate. Return void.
s.setstate(flags)
    Adds specified condition(s) to s. Type of flags is strm::iostate. Return void.
s.rdstate()
    Returns current condition of s as a strm::iostate value.
-----------------------------------------------------------------------------------*/
#include <iostream>
using std::cin; using std::cout; using std::endl;
using std::flush; using std::ends;
using std::unitbuf; using std::nounitbuf;

#include <sstream>
using std::istringstream; 

#include <string>
using std::string;

/*-----------------------------------------------------------------------------------
Each output stream manages a buffer , which it uses to hold the data that the program 
reads and writes. Using a buffer allows the operating system to combine several outp-
ut operations from our program into a single system-level write(important performance 
boost). There are several conditions that cause the buffer to be flushed( that is, to 
be written) to the actual output device or file:
1 The program completes normally. All output buffers are flushed as part of the retu-
  rn from main.
2 At some indeterminate time, the buffer can become full, in which case it will be f-
  lushed before writing the next value.
3 We can flush the buffer explicitly using a manipulator such as endl.
4 We can use the unitbuf manipulator to set the stream's internal state  to empty the 
  buffer after each output operation. By default, unitbuf is set for cerr, so that w-
  rites to cerr are flushed immediately.
5 An output stream might be tied to another stream. In this case, the buffer of the -
  tied stream is flushed whenever the tied stream is read or written. By default, cin 
  and cerr are both tied to cout. Hence, reading cin or writing to cerr flushes the -
  buffer in cout.

endl
    endl manipulator, which ends the current line and flushes the buffer. 
flush  ends
    flush flushes the stream but adds no characters to the output; ends inserts a nu-
    ll character into the buffer and then flushes it. 
unitbuf  nounitbuf    
    If we want to flush after every output, we can use the unitbuf manipulator . This
    manipulator tells the stream to do a flush after every subsequent write. The nounitbuf 
    manipulator restores the stream to use normal, system-managed buffer flushing.

----> Tying Input and Output Streams Together
When an input stream is tied to an output stream, any attempt to read the input stre-
am will first flush the buffer associated with the output stream. The library ties  -
cout to cin, so the statement
    cin >> ival;
causes the buffer associated with cout to be flushed.

Interactive systems usually should tie their input stream to their output stream. Do-
ing so means that all output, which might include prompts to the user, will be writt-
en before attempting to read the input.
----> tie
There are two overloaded versions of tie: One version takes no argument and returns -
a pointer to the output stream, if any, to which this object is currently tied. The -
function returns the null pointer if the stream is not tied.

The second version of tie takes a pointer to an ostream and ties itself to that ostr-
eam. That is, x.tie(&o) ties the stream x to the output stream o. We can tie either -
an istream or an ostream object to another ostream:
    cin.tie(&cout); // illustration only: the library ties cin and cout for us
                    // 
    ostream *old_tie = cin.tie(nullptr);  // cin is no longer tied. old_tie points to 
                                          // the stream (if any) currently tied to cin
    cin.tie(&cerr); // reading cin flushes cerr, not cout. ties cin and cerr; not a -
                    // good idea because cin should be tied to cout
    cin.tie(old_tie); // reestablish normal tie between cin and cout
To tie a given stream to a new output stream, we pass tie a pointer to the new stream. 
To untie the stream completely, we pass a null pointer. Each stream can be tied to at 
most one stream at a time. However, multiple streams can tie themselves to the same -
ostream.
----> Caution: Buffers Are Not Flushed If the Program Crashes
Output buffers are not flushed if the program terminates abnormally. When a program -
crashes, it is likely that data the program wrote may be sitting in an output  buffer 
waiting to be printed.

-----------------------------------------------------------------------------------*/
int managing_buf()
{
    cout << "hi!" << endl;   // writes hi and a newline, then flushes the buffer
    cout << "hi!" << flush;  // writes hi, then flushes the buffer; adds no data
    cout << "hi!" << ends;   // writes hi and a null, then flushes the buffer
    cout << unitbuf;         // all writes will be flushed immediately
    cout << "first" << " second" << endl; // any output is flushed immediately, no buffering
	cout << nounitbuf;       // returns to normal buffering

	return 0;
}

void read()
{
	cin.setstate(cin.badbit | cin.eofbit | cin.failbit); // turns on both fail and bad bits
}

void off()
{
	cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit); // turns off failbit and badbit but all other bits unchanged
} 


int main()
{
	cout << "before read" << endl;
	if (cin.good()) cout << "cin's good" << endl;
	if (cin.bad()) cout << "cin's bad" << endl;
	if (cin.fail()) cout << "cin's fail" << endl;
	if (cin.eof()) cout << "cin's eof" << endl;
	
	read();
	cout << "after read" << endl;
	if (cin.good()) cout << "cin's good" << endl;
	if (cin.bad()) cout << "cin's bad" << endl;
	if (cin.fail()) cout << "cin's fail" << endl;
	if (cin.eof()) cout << "cin's eof" << endl;
	
	off();
	cout << "after off" << endl;
	if (cin.good()) cout << "cin's good" << endl;
	if (cin.bad()) cout << "cin's bad" << endl;
	if (cin.fail()) cout << "cin's fail" << endl;
	if (cin.eof()) cout << "cin's eof" << endl;

	cout << "cin.rdstate(): " << cin.rdstate() << endl;
	cout << "bad          : " << cin.badbit << endl;
	cout << "eof          : " << cin.eofbit << endl;	
	cout << "fail         : " << cin.failbit << endl;
	cout << "good         : " << cin.goodbit << endl;

	managing_buf();
	
	return 0;
}

