// vector::begin/end
#include <iostream>
#include <vector>

/* 
 test begin/end 
 output:
 myvector contains: 1 2 3 4 5
 */
int cpp_vector_test01 ()
{
    std::vector<int> myvector;
	
    for (int i=1; i<=5; i++) 
		myvector.push_back(i);

    std::cout << "myvector contains:";

	for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
        std::cout << ' ' << *it;
	
    std::cout << '\n';

    return 0;
}

int main()
{
    cpp_vector_test01();
}

#include <iostream>
#include <vector>
using namespace std;


/*******************************************************************************
                                    Vectors
 *******************************************************************************
 Vectors are used very much like arrays are used, but a vector does not have a 
 fixed size. If it needs more capacity to store another element, its capacity is 
 automatically increased. Vectors are defined in the library <vector>,which places 
 them in the std namespace. Thus, a file that uses vectors would include the 
 following (or something similar):
               #include <vector>
               using namespace std;
 The vector class for a given Base_Type is written vector<Base_Type>. Two sample 
 vector declarations are
               vector<int> v; //default constructor producing an empty vector.
               vector<AClass> record(20); //vector constructor
                                          //for AClass to initialize 20 elements.
 Elements are added to a vector using the member function push_back, as illustrated 
 below:
               v.push_back(42);
 Once an element position has received its first element, either with push_back 
 or with a constructor initialization, that element position can then be accessed 
 using square bracket notation, just like an array element.

 Size and Capacity
 The size of a vector is the number of elements in the vector. The capacity of a 
 vector is the number of elements for which it currently has memory allocated. 
 For a vector v, the size and capacity can be recovered with the member functions 
 v.size( ) and v.capacity( ) .
 可以使用系统默认的capacity，也可以自己设置


 public member function
 std::vector::pop_back  void pop_back();
 Delete last element Removes the last element in the vector, effectively reducing 
 the container size by one.

 
 ******************************************************************************/
int main( )
{
    vector<int> v;
	
    v.push_back(6);/*push_back添加数据*/
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
	
    return 0;
}
