/*-----------------------------------------------------------------------------------
cin   an istream object that reads the standard input
cout  an ostream object that writes to the standard output
cerr  an ostream object, typically used for program error messages, that writes to t-
      he standard error

To support these different kinds of IO processing, the library defines a collection -
of IO types. These types, are defined in three separate headers: 
iostream defines the basic types used to read from and write to a stream
fstream  defines the types used to read and write named files
sstream  defines the types used to read and write in-memory strings.

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

-----------------------------------------------------------------------------------*/

