
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


