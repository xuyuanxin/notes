//Demonstrates the standard class string.
/*******************************************************************************
            Member Functions of the Standard Class string
 *******************************************************************************
 Constructors
 string str; Default constructor creates empty string object str.
 string str("sample"); Creates a string object with data "sample".
 string str(a_string); Creates a string object str that is a copy of a_string;
 a_string is an object of the class string.
 
 Accessors
 str[i] Returns read/write reference to character in str at index i.
 Does not check for illegal index.
 str.at(i) Returns read/write reference to character in str at index i.
 Same as str[i] , but this version checks for illegal index.
 str.substr(position, length) Returns the substring of the calling object starting at position
 and having length characters.
 str.length( ) Returns the length of str.
 Assignment/modifiers
 str1 = str2; Initializes str1 to str2¡¯s data.
 str1 += str2; Character data of str2 is concatenated to the end of str1.
 str.empty( ) Returns true if str is an empty string; false otherwise.
 str1 + str2 Returns a string that has str2¡¯s data concatenated to the
 end of str1¡¯s data.
 str.insert(pos, str2); Inserts str2 into str beginning at position pos.
 str.erase(pos, length); Removes substring of size length, starting at position pos.
 Comparison
 str1 == str2 str1 != str2 Compare for equality or inequality; returns a Boolean
 value.
 str1 < str2 str1 > str2
 str1 <= str2 str1 >= str2
 Four comparisons. All are lexicographical comparisons.
 Finds
 str.find(str1) Returns index of the first occurrence of str1 in str. If str1
 is not found then the special value string::npos is
 returned.
 str.find(str1, pos) Returns index of the first occurrence of string str1 in str;
 the search starts at position pos.
 str.find_first_of(str1, pos) Returns the index of the first instance in str of any character
 in str1, starting the search at position pos.
 str.find_first_not_of
  (str1, pos)
 Returns the index of the first instance in str of any character
 not in str1, starting the search at position pos.

 ******************************************************************************/



#include <iostream>

#include <string>    /* in order to use the class string, your code must */
using namespace std; /* contain string and using namespace std*/

int string2();
int string4();

int main( )
{
/*declares the string variable phrase and initializes it to the empty string.*/
    string phrase;

/* declares noun to be of type string and initializes it to a string value 
   equivalent to the C string "ants"*/
    string adjective("fried"), noun("ants");

    string wish = "Bon appetit!";
	
    phrase = "I love " + adjective + " " + noun + "!";
    cout << phrase << endl << wish << endl;

	string2();
	string4();
	
    return 0;
}

void new_line( )
{
    char next_char;
    do
    {
        cin.get(next_char);
    } while (next_char != '\n');
}


/*******************************************************************************
 the extraction operator >> ignores initial whitespace and stops reading when it 
 encounters more whitespace.For example, consider the following code;
				string s1, s2;
				cin >> s1;
				cin >> s2;
 If the user types in 
                  May the hair on your toes grow long and curly!
 then s1 will receive the value "May" with any leading (or trailing) whitespace
 deleted. The variable s2 receives the string "the". Using the extraction operator
 >> and cin, you can only read in words; 
 *******************************************************************************
                getline for Objects of the Class string
 The getline function for string objects has two versions:
         istream& getline(istream& ins, string& str_var,char delimiter);
 and
         istream& getline(istream& ins, string& str_var);
 The first version of this function reads characters from the istream object given 
 as the first argument (always cin in this chapter), inserting the characters into 
 the string variable @str_var until an instance of the delimiter character is 
 encountered. The delimiter character is removed from the input and discarded. The 
 second version uses '\n'  for the default value of delimiter; otherwise, it works 
 the same.These getline functions return their first argument (always cin in this
 chapter), but they are usually used as if they were void functions.
			 
 If you want to read one character at a time, you can use cin.get
 ******************************************************************************/
int string2( )
{
    string first_name, last_name, record_name;
    string motto = "Your records are our records.";
    cout << "Enter your first and last name:\n";
    cin >> first_name >> last_name;
    new_line( );
    record_name = last_name + ", " + first_name;
    cout << "Your name in our records is: ";
    cout << record_name << endl;
    cout << "Our motto is\n" << motto << endl;
    cout << "Please suggest a better (one-line) motto:\n";
    getline(cin, motto);
    cout << "Our new motto will be:\n";
    cout << motto << endl;
    return 0;
}

/*******************************************************************************
 input
		42
         Hello hitchhiker.
 However, while n is indeed set to the value of 42, line is set equal to the empty 
 string.Using cin >> n skips leading whitespace on the input, but leaves the rest
 of the line, in this case just '\n' , for the next input. n this case, the @getline 
 see the '\n'  and stops reading, so @getline reads an empty string. 

         cin.ignore(1000, '\n');
 With these arguments, a call to the ignore member function will read and discard 
 the entire rest of the line up to and including the '\n'  (or until it discards 
 1,000 characters if it does not find the end of the line after 1,000 characters).
 ******************************************************************************/
int string3()
{
    int n;
    string line;
    cin >> n;
    getline(cin, line);
}


/*******************************************************************************
 member function named @length("abc" len is 3) that takes no arguments and returns 
 the length of the string represented by the string object. 

 There is a member function named @at that does check for illegal index values.
 to change the third character in the string object str to 'X' , you can use either 
 of the following code fragments:
         str.at(2)='X';
 or
         str[2]='X';
 ******************************************************************************/
int string4( )
{
    string first_name, last_name;
    cout << "Enter your first and last name:\n";
    cin >> first_name >> last_name;
    cout << "first name len:" << first_name<<" "<<first_name.length()<<endl;
    cout << "last  name len:" << last_name<<" "<< last_name.length()<<endl;
	
    cout << "Your last name is spelled:\n";
    int i;
	
    for (i = 0; i < last_name.length( ) ; i++)
    {
        cout << last_name[i] << " ";
        last_name[i] = '-';
    }
    cout << endl;
    for (i = 0; i < last_name.length( ); i++)
        cout << last_name[i] << " "; //Places a "-" under each letter.
    cout << endl;
    cout << "Good day " << first_name << endl;
    return 0;
}

/*******************************************************************************
           Converting Between string Objects and C Strings
 *******************************************************************************
 C++ will perform an automatic type conversion to allow you to store a C string 
 in a variable of type string. For example, the following will work fine:
         char a_c_string[] = "This is my C string.";
 string string_variable;
         string_variable = a_c_string;
 However, the following will produce a compiler error message:
         a_c_string = string_variable; //ILLEGAL
         strcpy(a_c_string, string_variable); //ILLEGAL
 strcpy cannot take a string object as its second argument, and there is no 
 automatic conversion of string objects to C strings, To obtain the C string 
 corresponding to a string object, you must perform an explicit conversion. This 
 can be done with the string member function c_str( ) . 
        strcpy(a_c_string, string_variable.c_str( )); //Legal;
 the assignment operator does not work with C strings. So, just in case you 
 thought the following might work, we should point out that it too is illegal.
        a_c_string = string_variable.c_str( ); //ILLEGAL
 ******************************************************************************/
int string5()
{
}



/*******************************************************************************
 std::string::substr  string substr (size_t pos = 0, size_t len = npos) const;
 @pos:Position of the first character to be copied as a substring.If this is equal 
 to the string length, the function returns an empty string. If this is greater 
 than the string length, it throws out_of_range.Note: The first character is 
 denoted by a value of 0 (not 1).
 @len:Number of characters to include in the substring (if the string is shorter, 
 as many characters as possible are used).A value of string::npos indicates all 
 characters until the end of the string.
 @return:A string object with a substring of this object.The substring is the 
 portion of the object that starts at character position pos and spans len 
 characters (or until the end of the string, whichever comes first).
 ******************************************************************************/
 
int string_mf_substr()
{
	std::string str="We think in generalities, but we live in details.";
											 // (quoting Alfred N. Whitehead)
	
	std::string str2 = str.substr (12,12);	 // "generalities"
	
	std::size_t pos = str.find("live"); 	 // position of "live" in str
	
	std::string str3 = str.substr (pos);	 // get from "live" to the end
	
	std::cout << str2 << ' ' << str3 << '\n';
	
	return 0;

/*
 Output:
 generalities live in details.*/
}

