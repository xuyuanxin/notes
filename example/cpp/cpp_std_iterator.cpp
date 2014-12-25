// prev example
#include <iostream>     // std::cout
#include <iterator>     // std::next std::reverse_iterator
#include <list>         // std::list
#include <algorithm>    // std::for_each
#include <vector>       // std::vector



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



/*
 reverse_iterator example

 Output:
 myvector: 9 8 7 6 5 4 3 2 1 
*/
int cpp_reverse_iterator_test01 () 
{
    std::vector<int> myvector;

	/* head 0 1 2 3 4 5 6 7 8 9 end */
    for (int i=0; i<10; i++) myvector.push_back(i);

    typedef std::vector<int>::iterator iter_type;
                                                         
    iter_type from (myvector.begin()); /* @from point to 0 */ 
                                                         
    iter_type until (myvector.end());  /* @until point to end */
                                                        
    std::reverse_iterator<iter_type> rev_until (from); /* @rev_until point to head */
                                                         
    std::reverse_iterator<iter_type> rev_from (until); /* @rev_from point to 9 */

    std::cout << "myvector:";
	
    while (rev_from != rev_until)
        std::cout << ' ' << *rev_from++;
	
    std::cout << '\n';

    return 0;
}

/* 
 reverse_iterator::base example 
 Output:
 myvector: 0 1 2 3 4 5 6 7 8 
 */
int cpp_reverse_iterator_test_base () 
{
    std::vector<int> myvector;

	/*head 0 1 2 3 4 5 6 7 8 9 tail*/
    for (int i=0; i<10; i++) myvector.push_back(i);

    typedef std::vector<int>::iterator iter_type;

    std::reverse_iterator<iter_type> rev_end (myvector.begin()); /*@rev_end point to head */
    std::reverse_iterator<iter_type> rev_begin (myvector.end()); /*@rev_begin point to 9 */

    std::cout << "myvector:";
    for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}


int main()
{
}
