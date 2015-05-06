// vector::begin/end
#include <iostream>
#include <vector>
using namespace std;

/*-----------------------------------------------------------------------------------
                          Vectors base
 ------------------------------------------------------------------------------------
 Vectors are used very much like arrays are used , but a vector does not have a fixed 
 size. If it needs more capacity to store another element, its capacity is automatic-
 ally increased. Vectors are defined in the library <vector>, which places them in t-
 he std namespace. Thus, a file that uses vectors would include the following (or so-
 mething similar):
               #include <vector>
               using namespace std;
 The vector class for a given Base_Type is written vector<Base_Type>. Two sample vec-
 tor declarations are
               vector<int> v; //default constructor producing an empty vector.
               vector<AClass> record(20); //vector constructor
                                          //for AClass to initialize 20 elements.
 you cannot initialize the ith element using v[i] ; you can only change an element t-
 hat has already been given some value. To add an element to an index position of a -
 vector for the first time, you would normally use the member function push_back.

 If you try to set v[i] for i greater than or equal to v.size( ), then you may or ma-
 y not get an error message, but your program will undoubtedly misbehave at some poi-
 nt. 

 Elements are added to a vector using the member function push_back, as illustrated -
 below:
               v.push_back(42);
 Once an element position has received its first element, either with push_back or w-
 ith a constructor initialization, that element position can then be accessed using -
 square bracket notation, just like an array element.

 ----> Size and Capacity
 The size of a vector is the number of elements in the vector. The capacity of a vec-
 tor is the number of elements for which it currently has memory allocated. For a ve-
 ctor v, the size and capacity can be recovered with the member functions v.size( ) -
 and v.capacity( ) .

 public member function
 std::vector::pop_back  void pop_back();
 Delete last element Removes the last element in the vector, effectively reducing 
 the container size by one.

 ----> access the elements of a vector
     vector<int> v{1,2,3,4,5,6,7,8,9};
     for (auto &i : v) // for each element in v (note: i is a reference)
         i *= i; // square the element value
     for (auto i : v) // for each element in v
         cout << i << " "; // print the element
     cout << endl;
 ----> Computing a vector Index
 We can fetch a given element using the subscript operator. subscripts for vector st-
 art at 0; the type of a subscript is the corresponding size_type; we may use the su-
 bscript operator (the [] operator) to fetch only elements that actually exist. For -
 example,
     vector<int> ivec; // empty vector
     cout << ivec[0]; // error: ivec has no elements!
     vector<int> ivec2(10); // vector with ten elements
     cout << ivec2[10]; // error: ivec2 has elements 0 . . . 9
 It is an error to subscript an element that doesn't exist, but it is an error that -
 the compiler is unlikely to detect. Instead, the value we get at run time is undefi-
 ned.

 To use size_type, we must name the type in which it is defined. A vector type alway-
 s includes its element type:
     vector<int>::size_type // ok
     vector::size_type // error
 ----------------------------------------------------------------------------------*/
int vector_base( )
{
    vector<int> v;
	
    v.push_back(6);
    v.push_back(9);
    v.push_back(1);

    cout << "v.size = " << v.size( )  << endl;	
    cout << "v.capacity = " << v.capacity( )  << endl;

    cout << "vector v:";
	
    for (unsigned int i = 0; i < v.size( ); i++)
        cout << v[i] << " ";
	
    cout << endl;
	
    cout << "vector v(after pop):";
    v.pop_back();
    for (unsigned int i = 0; i < v.size( ); i++)
        cout << v[i] << " ";

    cout << endl;
	
/*******************************************************************************
 sets the capacity to at least 10 more than the number of elements currently in 
 the vector.Note that you can rely on v.reserve to increase the capacity of a
 vector, but it does not necessarily decrease the capacity of a vector if the
 argument is smaller than the current capacity.
 ******************************************************************************/
	v.reserve(v.size( ) + 10);
    cout << "v.capacity = " << v.capacity( )  << endl;
	
	v.reserve(32);/*sets the capacity to at least 32 elements*/
    cout << "v.capacity = " << v.capacity( )  << endl;	

/*******************************************************************************
 If the previous size was less than 24, then the new elements are initialized as
 we described for the constructor with an integer argument. If the previous size
 was greater than 24, then all but the first 24 elements are lost. The capacity is
 automatically increased if need be. 
 ******************************************************************************/
	v.resize(24);/*change the size of a vector*/
    cout << "v.capacity = " << v.capacity( )  << endl;	

    std::cout << "\r\n\r\n";
	
    return 0;
}


/*-----------------------------------------------------------------------------------
Output:
The contents of fifth are: 16 2 77 29

vector<int> ivec;           // initially empty
vector<int> ivec2(ivec);    // copy elements, The two vectors must be the same type.
vector<int> ivec3 = ivec;   // copy elements of ivec into ivec3
vector<string> svec(ivec2); // error: svec holds strings, not ints

----> List Initializing a vector
vector<string> articles = {"a", "an", "the"}; // has three elements
vector<string> v2("a", "an", "the");          // error
----> Creating a Specified Number of Elements
We can also initialize a vector from a count and an element value. The count determi-
nes how many elements the vector will have ; the value provides the initial value for 
each of those elements:
    vector<int> ivec(10, -1); // ten int elements, each initialized to -1
    vector<string> svec(10, "hi!"); // ten strings; each element is "hi!"
----> Value Initialization
We can usually omit the value and supply only a size. In this case the library creat-
es a value-initialized element initializer for us. This library-generated value is u-
sed to initialize each element in the container. The value of the element initializer
depends on the type of the elements stored in the vector. If the vector holds elemen-
ts of a built-in type, such as int, then the element initializer has a value of 0. If 
the elements are of a class type, such as string, then the element initializer is it-
self default initialized:
    vector<int> ivec(10); // ten elements, each initialized to 0
    vector<string> svec(10); // ten elements, each an empty string
There are two restrictions on this form of initialization: The first restriction is -
that some classes require that we always supply an explicit initializer. If our vect-
or holds objects of a type that we cannot default initialize , then we must supply an 
initial element value;it is not possible to create vectors of such types by supplying 
only a size.
----> List Initializer or Element Count
In a few cases, what initialization means depends upon whether we use curly braces or 
parentheses to pass the initializer(s). 
    vector<int> v1(10);    // v1 has ten elements with value 0
    vector<int> v2{10};    // v2 has one element with value 10
    vector<int> v3(10, 1); // v3 has ten elements with value 1
    vector<int> v4{10, 1}; // v4 has two elements with values 10 and 1
When we use parentheses, we are saying that the values we supply are to be used to c-
onstruct the object. Thus, v1 and v3 use their initializers to determine the vector's 
size, and its size and element values, respectively. When we use curly braces, {...}, 
we're saying that, if possible, we want to list initialize the object. That is, if t-
here is a way to use the values inside the curly braces as a list of element initial-
izers, the class will do so. Only if it is not possible to list initialize the object 
will the other ways to initialize the object be considered. The values we supply when 
we initialize v2 and v4 can be used as element values. These objects are list initia-
lized; the resulting vectors have one and two elements, respectively.

On the other hand, if we use braces and there is no way to use the initializers to l-
ist initialize the object, then those values will be used to construct the object. F-
or example, to list initialize a vector of strings, we must supply values that can be
used as strings. In this case, there is no confusion about whether to list initialize
the elements or construct a vector of the given size:
    vector<string> v5{"hi"}; // list initialization: v5 has one element
    vector<string> v6("hi"); // error: can't construct a vector from a string literal
    vector<string> v7{10}; // v7 has ten default-initialized elements
    vector<string> v8{10, "hi"}; // v8 has ten elements with value "hi"
Although we used braces on all but one of these definitions, only v5 is list initial-
ized. In order to list initialize the vector, the values inside braces must match the 
element type. We cannot use an int to initialize a string, so the initializers for v7 
and v8 can't be element initializers. If list initialization isn't possible, the com-
piler looks for other ways to initialize the object from the given values.
-----------------------------------------------------------------------------------*/
int vector_constructor()
{
    std::vector<int> first; // empty vector of ints
    std::vector<int> second(4,100); // four ints with value 100
    std::vector<int> third(second.begin(),second.end()); // iterating through second
    std::vector<int> fourth(third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int) );

    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
	
    std::cout << "\r\n\r\n";

    return 0;
}

/*----------------------------------------------------------------------------------- 
 test begin/end 
 output:
 myvector contains: 1 2 3 4 5
 ----------------------------------------------------------------------------------*/
int vector_begin_end ()
{
    std::vector<int> myvector;
	
    for (int i=1; i<=5; i++) 
		myvector.push_back(i);

    std::cout << "myvector contains:";

	for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
        std::cout << ' ' << *it;
	
    std::cout << "\r\n\r\n";

    return 0;
}

int vector_string ()
{
    std::vector<string> myvector;
	
	myvector.push_back("abc");
	myvector.push_back("efg");

    std::cout << "myvector contains:";

	for (std::vector<string>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << endl;
    
    std::cout << "myvector contains2:" << endl;
	
	for (int i = 0; i < myvector.size(); ++i)
        std::cout << myvector[i] << endl ;
	
    std::cout << "\r\n\r\n";

    return 0;
}


int main()
{
    vector_base();
	vector_constructor();
	vector_begin_end();
	vector_string();
	
    return 0;
}



