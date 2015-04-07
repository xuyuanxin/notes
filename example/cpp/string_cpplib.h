/*-----------------------------------------------------------------------------------
In addition to the built-in types, C++ defines a rich library of abstract data types. 
Among the most important library types are string, which supports variable-length ch-
aracter strings, and vector, which defines variable-size collections. Associated with 
string and vector are companion types known as iterators,which are used to access the 
characters in a string or the elements in a vector.

The built-in types are defined directly by the C++ language. These types represent f-
acilities present in most computer hardware, such as numbers or characters. The stan-
dard library defines a number of additional types of a higher-level nature that comp-
uter hardware usually does not implement directly.

A string is a variable-length sequence of characters. To use the string type, we must
include the string header. Because it is part of the library,string is defined in the
std namespace. Our examples assume the following code:
#include <string>
using std::string;


-----------------------------------------------------------------------------------*/




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


/*******************************************************************************
              std::string::string (public member function )
 *******************************************************************************
 @str
    Another string object, whose value is either copied or acquired.
 @pos
    Position of the first character in @str that is copied to the object as a 
    substring.If this is greater than str's length, it throws out_of_range.
    Note: The first character in @str is denoted by a value of 0 (not 1).
 @len
    Length of the substring to be copied (if the string is shorter, as many 
    characters as possible are copied).A value of @npos indicates all characters 
    until the end of @str.
 @s
    Pointer to an array of characters (such as a c-string).
 @n
    Number of characters to copy.
 @c
    Character to fill the string with. Each of the @n characters in the string 
    will be initialized to a copy of this value.
 @first @last
    Input iterators to the initial and final positions in a range. The range used 
    is [first,last), which includes all the characters between first and last, 
    including the character pointed by first but not the character pointed by last.
    The function template argument InputIterator shall be an input iterator type 
    that points to elements of a type convertible to char.If InputIterator is an 
    integral type, the arguments are casted to the proper types so that signature(5) 
    is used instead.
 @il
    An initializer_list object.These objects are automatically constructed from 
    initializer list declarators.    
 @fun:
    Constructs a string object, initializing its value depending on the constructor
    version used:
 1 empty string constructor (default constructor)
   Constructs an empty string, with a length of zero characters.
 2 copy constructor
   Constructs a copy of str.
 3 substring constructor
   Copies the portion of @str that begins at the character position @pos and spans 
   @len characters (or until the end of @str, if either @str is too short or if 
   @len is @npos).
 4 from c-string
   Copies the null-terminated character sequence (C-string) pointed by s.
 5 from buffer
   Copies the first @n characters from the array of characters pointed by s.
 6 fill constructor
   Fills the string with @n consecutive copies of character @c.
 7 range constructor
   Copies the sequence of characters in the range [first,last), in the same order.
 8 initializer list
   Copies each of the characters in il, in the same order.
 9 move constructor
   Acquires the contents of @str.@str is left in an unspecified but valid state.    
 ******************************************************************************/
string(); /* 1 c++98 */
string (const string& str); /* 2 c++98 */
string (const string& str, size_t pos, size_t len = npos); /* 3 c++98 */
string (const char* s); /* 4 c++98 */
string (const char* s, size_t n); /* 5 c++98 */
string (size_t n, char c); /* 6 c++98 */
template <class InputIterator>
string  (InputIterator first, InputIterator last); /*7  c++98 */
string (initializer_list<char> il); /* 8 c++11 */
string (string&& str) noexcept; /* 9 c++11 */


/*******************************************************************************
             std::operator+ (string) Non-member function overloads
 *******************************************************************************
 @lhs  @rhs
 Arguments to the left- and right-hand side of the operator, respectively.If of 
 type char*, it shall point to a null-terminated character sequence.
 @ret:
 returns a newly constructed @string object with its value being the concatenation 
 of the characters in @lhs followed by those of @rhs.
 ******************************************************************************/
string operator+ (const string& lhs, const string& rhs); /* c++98 */
string operator+ (const string& lhs, const char*   rhs); /* c++98 */
string operator+ (const char*   lhs, const string& rhs); /* c++98 */
string operator+ (const string& lhs, char          rhs); /* c++98 */
string operator+ (char          lhs, const string& rhs); /* c++98 */


/*******************************************************************************
             std::string::begin (public member function)   <string>
 *******************************************************************************
 @ret
    returns an iterator pointing to the first character of the string.If the string 
    object is const-qualified, the function returns a const_iterator. Otherwise, it 
    returns an iterator.Member types iterator and const_iterator are random access 
    iterator types (pointing to a character and to a const character,respectively).
 ******************************************************************************/
iterator begin(); /* c++98 */
const_iterator begin() const; /* c++98 */


/*******************************************************************************
             std::string::end (public member function)   <string>
 *******************************************************************************
 @ret
	Returns an iterator pointing to the past-the-end character of the string.

 The past-the-end character is a theoretical character that would follow the last 
 character in the string. It shall not be dereferenced.Because the ranges used by 
 functions of the standard library do not include the element pointed by their 
 closing iterator, this function is often used in combination with string::begin 
 to specify a range including all the characters in the string.If the object is 
 an empty string, this function returns the same as string::begin.
 ******************************************************************************/
iterator end(); /* c++98 */
const_iterator end() const; /* c++98 */




