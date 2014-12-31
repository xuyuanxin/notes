/*******************************************************************************
               std::deque (class template )   <deque> 
 *******************************************************************************              
 Double ended queue
 deque (usually pronounced like "deck") is an irregular acronym of Double-Ended QUEue. 
 Double-ended queues are sequence containers with dynamic sizes that can be expanded 
 or contracted on both ends (either its front or its back).
 ******************************************************************************/
template < class T, class Alloc = allocator<T> > class deque;


/*******************************************************************************
                  std::deque::push_back    public member function
 *******************************************************************************                 
 @val
    Value to be copied (or moved) to the new element.Member type value_type is 
    the type of the elements in the container, defined in deque as an alias of 
    its first template parameter (T).
 @fun: Add element at the end
    Adds a new element at the end of the deque container, after its current last 
    element. The content of @val is copied (or moved) to the new element.

 The storage for the new elements is allocated using the container's allocator, 
 which may throw exceptions on failure (for the default allocator, bad_alloc is 
 thrown if the allocation request does not succeed).
 ******************************************************************************/
void push_back (const value_type& val);
