#include <iostream>
using std::cin; using std::cout; using std::cerr;
using std::istream; using std::ostream; using std::endl;

#include <sstream>
using std::ostringstream; using std::istringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

// members are public by default
struct PersonInfo { 
    string name;
    vector<string> phones;
};

// we'll see how to reformat phone numbers in chapter 17
// for now just return the string we're given
string format(const string &s) 
{ 
    return s; 
}

// we'll see how to validate phone numbers 
// in chapter 17, for now just return true
bool valid(const string &)
{
    return true;
}

vector<PersonInfo> getData(istream &is)
{
    string line, word;
    vector<PersonInfo> people;

    // read the input a line at a time until end-of-file (or other error)
    while (getline(is, line)) {       
        PersonInfo info;            // object to hold this record's data
        istringstream record(line); // bind record to the line we just read
        record >> info.name;        // read the name
        while (record >> word)      // read the phone numbers 
            info.phones.push_back(word);  // and store them
        people.push_back(info); // append this record to people
    }
    
    return people;
}

ostream& process(ostream &os, vector<PersonInfo> people)
{
    // for each entry in people
    for (vector<PersonInfo>::const_iterator entry = people.begin(); 
         entry != people.end(); ++entry) 
    {    
        ostringstream formatted, badNums; // objects created on each loop

        for (vector<string>::const_iterator nums = entry->phones.begin(); 
             nums != entry->phones.end(); ++nums) 
        {
            if (!valid(*nums)) {           
                badNums << " " << *nums;  // string in badNums
            } else {
                formatted << " " << format(*nums);
            }
        }
        if (badNums.str().empty()) {    // there were no bad numbers
            os << entry->name << " " << formatted.str() << endl; 
        } else {                        // otherwise, print the name and bad numbers
            cerr << "input error: " << entry->name 
                 << " invalid number(s) " << badNums.str() << endl;
        }
    }
    
    return os;
}

int main()
{
    process(cout, getData(cin));

    return 0;
}



/*-----------------------------------------------------------------------------------
The sstream header defines three types to support in-memory IO; these types read from 
or write to a string as if the string were an IO stream.

The istringstream type reads a string, ostringstream writes a string,and stringstream
reads and writes the string. Like the fstream types, the types defined in sstream in-
herit from the types we have used from the iostream header. In addition to the opera-
tions they inherit, the types defined in sstream add members to manage the string as-
sociated with the stream. These operations are listed in Table 8.5. They may be call-
ed on stringstream objects but not on the other IO types.

Table 8.5 stringstream-Specific Operations
sstream strm;
    strm is an unbound stringstream. sstream is one of the types defined in the sstr-
    eam header.
sstream strm(s);
    strm is an sstream that holds a copy of the string s. This constructor is explic-
    it.
strm.str()
    Return a copy of the string that strm holds.
strm.str(s)
    Copies the string s int strm. Return void.
*/
