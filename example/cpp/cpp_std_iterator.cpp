// prev example
#include <iostream>     // std::cout
#include <iterator>     // std::next
#include <list>         // std::list
#include <algorithm>    // std::for_each



/*
 Output: The last element is 90
 */
int cpp_iterator_test_prev () 
{
  std::list<int> mylist;
  
  for (int i=0; i<10; i++) 
      mylist.push_back (i*10);

  std::cout << "The last element is " << *std::prev(mylist.end()) << '\n';

  return 0;
}


int main()
{
    cpp_iterator_test_prev();
}
