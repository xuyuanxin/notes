/*******************************************************************************
 <functional> Function objects
 Function objects are objects specifically designed to be used with a syntax similar 
 to that of functions. In C++, this is achieved by defining member function operator() 
 in their class, like for example:
         struct myclass 
         {
             int operator()(int a) {return a;}
         } myobject;
         int x = myobject (0);           // function-like syntax with object myobject 
 They are typically used as arguments to functions, such as predicates or comparison 
 functions passed to standard algorithms.
 *******************************************************************************  
                    std::less (class template)   <functional>
 *******************************************************************************       
 template <class T> struct less;
 Function object class for less-than inequality comparison
 Binary function object class whose call returns whether the its first argument 
 compares less than the second (as returned by operator <).

 Generically, function objects are instances of a class with member function 
 operator() defined. This member function allows the object to be used with the 
 same syntax as a function call.

 It is defined with the same behavior as:
		template <class T> 
		struct less : binary_function <T,T,bool>  // c++98 
		{
		    bool operator() (const T& x, const T& y) const {return x<y;}
		};

		template <class T> 
		struct less  // c++11 
		{
		  bool operator() (const T& x, const T& y) const {return x<y;}
		  typedef T first_argument_type;
		  typedef T second_argument_type;
		  typedef bool result_type;
		}; 

 ---->Template parameters
 @T:Type of the arguments to compare by the functional call.The type shall support 
 the operation (operator<).

 ---->Member functions
 bool operator() (const T& x, const T& y)
 Member function returning whether the first argument compares less than the 
 second (x<y).

 ---->Member types
 member type	       definition	      notes
 first_argument_type	T	     Type of the first argument in member operator()
 second_argument_type	T	     Type of the second argument in member operator()
 result_type	         bool	     Type returned by member operator() 
 ******************************************************************************/
