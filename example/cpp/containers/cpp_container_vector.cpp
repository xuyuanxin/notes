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
