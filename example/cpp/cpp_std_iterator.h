
/*******************************************************************************
                   std::prev function template C++11
 *******************************************************************************                  
 @it: iterator to base position.BidirectionalIterator shall be at least a bidirectional 
      iterator.
 @n:  Number of element positions offset (1 by default).difference_type is the numerical 
      type that represents distances between iterators of the BidirectionalIterator type.
 ret: An iterator to the element n positions before it.
 fun: Get iterator to previous element
  
 Returns an iterator pointing to the element that it would be pointing to if 
 advanced -n positions.
 If it is a random-access iterator, the function uses just once operator+ or 
 operator-.Otherwise, the function uses repeatedly the increase or decrease 
 operator (operator++ or operator--) on the copied iterator until n elements 
 have been advanced.
 ******************************************************************************/
template <class BidirectionalIterator>
BidirectionalIterator prev (BidirectionalIterator it,
typename iterator_traits<BidirectionalIterator>::difference_type n = 1);

/*******************************************************************************
     std::reverse_iterator::reverse_iterator  public member function <iterator>
 *******************************************************************************       
 Constructs a reverse iterator object: 
 1 default constructor
   Constructs a reverse iterator that points to no object. The internal base iterator 
   is value-initialized.
 2 initalization constructor
   Constructs a reverse iterator from some original iterator @it. The behavior of 
   the constructed object replicates the original, except that it iterates through 
   its pointed elements in the reverse order.
 3 copy / type-cast constructor
   Constructs a reverse iterator from some other reverse iterator. The constructed 
   object keeps the same sense of iteration as rev_it.

 @it:An iterator,whose sense of iteration is inverted in the constructed object.
 Member type iterator_type is the underlying bidirectional iterator type (the class 
 template parameter: Iterator).
 @rev_it:An iterator of a reverse_iterator type, whose sense of iteration is preserved.   
 ******************************************************************************/
reverse_iterator();
explicit reverse_iterator (iterator_type it);
template <class Iter>
reverse_iterator (const reverse_iterator<Iter>& rev_it);


/*******************************************************************************
        std::reverse_iterator::base public member function <iterator>
 *******************************************************************************       
 ret:A copy of the base iterator, which iterates in the opposite direction.Member 
     type iterator_type is the underlying bidirectional iterator type (the class 
     template parameter: Iterator).       
 fun:Return base iterator				   
				   
 The base iterator is an iterator of the same type as the one used to construct the 
 reverse_iterator, but pointing to the element next to the one the reverse_iterator 
 is currently pointing to (a reverse_iterator has always an offset of -1 with respect 
 to its base iterator).
 ******************************************************************************/
iterator_type base() const;
