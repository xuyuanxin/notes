//Demonstrates the standard class string.
#include <iostream>
#include <string>    /* in order to use the class string, your code must */
using namespace std; /* contain string and using namespace std*/


/*
 Output:
s1:
s2: Initial string
s3: str
s4: A char
s5: Another character sequence
s6: xxxxxxxxxx
s7a: **********
s7b: Initial
s7c: I
s7d:
 */
int string_constructor()
{
  std::string s0 ("Initial string");

  std::string s1;
  std::string s2(s0);
  std::string s3(s0, 8, 3);
  std::string s4("A character sequence", 6);
  std::string s5("Another character sequence");
  std::string s6(10, 'x');
  std::string s7a(10, 42); // 42 is the ASCII code for '*'
  std::string s7b(s0.begin(),s0.begin()+7);  
  std::string s7c(s0.begin(),s0.begin()+1);
  std::string s7d(s0.begin(),s0.begin());

  std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
  std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6: " << s6;
  std::cout << "\ns7a: " << s7a << "\ns7b: " << s7b;  
  std::cout << "\ns7c: " << s7c << "\ns7d: " << s7d << '\n';  
  return 0;
}


int string_add()
{
/*declares the string variable phrase and initializes it to the empty string.*/
	string phrase;

/* declares noun to be of type string and initializes it to a string value 
   equivalent to the C string "ants"*/
	string adjective("fried"), noun("ants");

	string wish = "Bon appetit!";
	
	phrase = "I love " + adjective + " " + noun + "!";
	cout << phrase << endl << wish << endl;
	
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
int string_output( )
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

/* 
 Output:
 Test string
 */
int string_begin_end()
{
    std::string str ("Test string");
	
    for ( std::string::iterator it=str.begin(); it!=str.end(); ++it)
        std::cout << *it;
    std::cout << '\n';

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


int main()
{
    string_constructor();

	return 0;
}
