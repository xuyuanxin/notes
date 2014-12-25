#include <iostream>     // std::cout
#include <algorithm>    // std::includes, std::sort std::find_if
#include <vector>       // std::vector




// includes algorithm example
bool myfunction (int i, int j) { return i<j; }

/*
 Output:
 container includes continent!
 container includes continent!
*/
int cpp_algorithm_includes () 
{
    int container[] = {5,10,15,20,25,30,35,40,45,50};
    int continent[] = {40,30,20,10};

    std::sort (container,container+10);
    std::sort (continent,continent+4);

    // using default comparison:
    if ( std::includes(container,container+10,continent,continent+4) )
        std::cout << "container includes continent!\n";

    // using myfunction as comp:
    if ( std::includes(container,container+10,continent,continent+4, myfunction) )
        std::cout << "container includes continent!\n";

    return 0;
}

bool IsOdd (int i) {
  return ((i%2)==1);
}

/* 
 find_if example
 Output:
 The first odd value is 25
*/
int cpp_algorithm_find_if () 
{
    std::vector<int> myvector;

    myvector.push_back(10);
    myvector.push_back(25);
    myvector.push_back(40);
    myvector.push_back(55);

    std::vector<int>::iterator it = std::find_if (myvector.begin(), myvector.end(),IsOdd);
    std::cout << "The first odd value is " << *it << '\n';

    return 0;
}
