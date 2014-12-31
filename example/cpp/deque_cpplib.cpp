#include <iostream>
#include <deque>
using namespace std;


/*
 output:
 mydeque stores 3 numbers.
 mydeque(first->end):  1 2 3
 */
int deque_push_back ()
{
    std::deque<int> mydeque;

    mydeque.push_back(1);
    mydeque.push_back(2);
    mydeque.push_back(3);

    std::cout << "mydeque stores " << (int) mydeque.size() << " numbers.\n";

    cout << "mydeque(first->end): " ;
    for (std::deque<int>::iterator it = mydeque.begin(); it!=mydeque.end(); ++it)
	    std::cout << ' ' << *it;

    return 0;
}


int main()
{
    deque_push_back();

	return 0;
	
}
