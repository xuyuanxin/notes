

/*******************************************************************************
                std::includes (function template)   <algorithm>
 *******************************************************************************       
 @first1, @last1
   Input iterators to the initial and final positions of the first sorted sequence 
   (which is tested on whether it contains the second sequence). The range used 
   is [first1,last1),including the element pointed by first1 but not the element 
   pointed by last1.
 @first2, @last2
   Input iterators to the initial and final positions of the second sorted sequence 
   (which is tested on whether it is contained in the first sequence). The range 
   used is [first2,last2).
 @comp
   Binary function that accepts two elements as arguments (one from each of the 
   two sequences, in the same order), and returns a value convertible to bool. 
   The value returned indicates whether the element passed as first argument is 
   considered to go before the second in the specific strict weak ordering it defines.
   The function shall not modify any of its arguments.This can either be a function 
   pointer or a function object.
 @fun:
   Test whether sorted range includes another sorted range
 @ret:
   true if every element in the range [first2,last2) is contained in the range 
   [first1,last1), false otherwise.

 The elements are compared using operator< for the first version, and comp for 
 the second. Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) 
 or if (!comp(a,b) && !comp(b,a)).
 
 The elements in the range shall already be ordered according to this same criterion 
 (operator< or comp).

 C++98:If [first2,last2) is an empty range, the result is unspecified.
 C++11:If [first2,last2) is an empty range, the function returns true.
 ******************************************************************************/
template <class InputIterator1, class InputIterator2>
bool includes ( InputIterator1 first1, InputIterator1 last1,
				  InputIterator2 first2, InputIterator2 last2 );
 
template <class InputIterator1, class InputIterator2, class Compare>
bool includes ( InputIterator1 first1, InputIterator1 last1,
				  InputIterator2 first2, InputIterator2 last2, Compare comp );



