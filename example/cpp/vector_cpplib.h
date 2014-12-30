/*******************************************************************************
               std::vector (class template )   <vector>
 *******************************************************************************              
 Vectors are sequence containers representing arrays that can change in size.
 Just like arrays, vectors use contiguous storage locations for their elements, 
 which means that their elements can also be accessed using offsets on regular 
 pointers to its elements, and just as efficiently as in arrays. But unlike arrays, 
 their size can change dynamically, with their storage being handled automatically 
 by the container.              
 ******************************************************************************/
template < class T, class Alloc = allocator<T> > class vector; // generic template


/*******************************************************************************
           std::vector::vector (public member function ) constructor
 *******************************************************************************
 @alloc  Allocator object.
    The container keeps and uses an internal copy of this allocator.Member type 
    allocator_type is the internal allocator type used by the container, defined 
    in vector as an alias of its second template parameter(Alloc).If allocator_type 
    is an instantiation of the default allocator (which has no state), this is 
    not relevant.
 @n
    Initial container size (i.e., the number of elements in the container at 
    construction).Member type size_type is an unsigned integral type.
 @val
    Value to fill the container with. Each of the @n elements in the container 
    will be initialized to a copy of this value.Member type value_type is the 
    type of the elements in the container, defined in vector as an alias of its 
    first template parameter (T).
 @first @last
    Input iterators to the initial and final positions in a range. The range used 
    is [first,last), which includes all the elements between first and last, 
    including the element pointed by first but not the element pointed by last.The 
    function template argument InputIterator shall be an input iterator type that 
    points to elements of a type from which value_type objects can be constructed.
 @fun
    Constructs a vector, initializing its contents depending on the constructor 
    version used:
 1 empty container constructor (default constructor)
   Constructs an empty container, with no elements.
 2 fill constructor
   Constructs a container with n elements. Each element is a copy of val.
 3 range constructor
   Constructs a container with as many elements as the range [first,last), with 
   each element constructed from its corresponding element in that range, in the 
   same order.
 4 copy constructor
   Constructs a container with a copy of each of the elements in x, in the same 
   order.    
 ******************************************************************************/
explicit vector (const allocator_type& alloc = allocator_type());
explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type());
template <class InputIterator>
vector (InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type());
vector (const vector& x);


/*******************************************************************************
                  std::vector::begin    public member function
 ret: An iterator to the beginning of the sequence container.
 fun: Return iterator to beginning
  
 Returns an iterator pointing to the first element in the vector. 
 Notice that, unlike member vector::front, which returns a reference to the first 
 element, this function returns a random access iterator pointing to it. 
 If the container is empty, the returned iterator value shall not be dereferenced.

 If the vector object is const-qualified, the function returns a const_iterator. 
 Otherwise, it returns an iterator. 
 Member types iterator and const_iterator are random access iterator types (pointing 
 to an element and to a const element, respectively).
 ******************************************************************************/
      iterator begin();                /* c++98 */
const_iterator begin() const;          /* c++98 */
      iterator begin() noexcept;         /* c++11 */
const_iterator begin() const noexcept;   /* c++11 */



/*******************************************************************************
                  std::vector::end    public member function
 ret: An iterator to the element past the end of the sequence.
 fun: Return iterator to end
  
 Returns an iterator referring to the past-the-end element in the vector container.
 The past-the-end element is the theoretical element that would follow the last 
 element in the vector. It does not point to any element, and thus shall not be 
 dereferenced. 
 Because the ranges used by functions of the standard library do not include the 
 element pointed by their closing iterator, this function is often used in combination 
 with vector::begin to specify a range including all the elements in the container. 
 If the container is empty, this function returns the same as vector::begin.

 If the vector object is const-qualified, the function returns a const_iterator. 
 Otherwise, it returns an iterator.
 Member types iterator and const_iterator are random access iterator types (pointing 
 to an element and to a const element, respectively).
 ******************************************************************************/
      iterator end();                /* c++98 */
const_iterator end() const;          /* c++98 */
      iterator end() noexcept;         /* c++11 */
const_iterator end() const noexcept;   /* c++11 */


