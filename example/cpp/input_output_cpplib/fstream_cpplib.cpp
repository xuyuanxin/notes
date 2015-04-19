//Reads three numbers from the file infile.dat, sums the numbers,
 //and writes the sum to the file outfile.dat.
 //(A better version of this program will be given in Display 6.2.)
#include <iostream>
#include <cstdlib>   /*exit*/
#include <fstream>
int main( )
{
    using namespace std;
    ifstream in_stream;
    ofstream out_stream;

    in_stream.open("infile.dat");
	if (in_stream.fail( ))
	{
	    cout << "Input file opening failed.\n";
	    exit(1);
	}

    out_stream.open("outfile.dat");
	
    int first, second, third;
	
    in_stream >> first >> second >> third;
    out_stream << "The sum of the first 3\n"
    << "numbers in infile.dat\n"
    << "is " << (first + second + third)
    << endl;
	
    in_stream.close( );
    out_stream.close( );
    return 0;
}

/*-----------------------------------------------------------------------------------
The fstream header defines three types to support file IO: ifstream to read from a g-
iven file, ofstream to write to a given file, and fstream, which reads and writes a -
given file.

In addition to the behavior that they inherit from the iostream types, the types def-
ined in fstream add members to manage the file associated with the stream. These ope-
rations, listed in Table 8.3, can be called on objects of fstream, ifstream, or ofst-
ream but not on the other IO types.


fstream fstrm;
    creates an unbount file stream. fstream is one of the types defined in the fstre-
    am header.
fstream fstrm(s);
    Creates an fstream and opens the file named s. s can have type string or can be a
    pointer to a C-style character string. The default file mode depends on the  type
    of fstream.
fstream fstrm(s,mode);
    opens s in the given mode.
fstrm.open(s); fstrm.open(s,mode)
    Opens the file named by the s and binds that file to fstrm. Return void.
fstrm.close()
    Close the file to which fstrm is bount. Return void.
fstrm.is_open()
    Returns a bool indicating whether the fileassociated with fstrm was  successfully 
    opend and has not been closed.










-----------------------------------------------------------------------------------*/
