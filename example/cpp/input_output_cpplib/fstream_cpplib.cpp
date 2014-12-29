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

