/*
----> Array Names
 In C, when the name of an array is used in almost any expression, the value of the -
 name is a pointer constant that is the address of the first element of the array . -
 Its type depends on the type of the array elements: if they are int , then the value 
 of the array name is a "constant pointer to int". If they are something else, then -
 the value of the array name is a "constant pointer to something else".Note-that this 
 value is a pointer constant as opposed to a pointer variable ; you cannot change the 
 value of a constant. 

 There are only two places where this pointer substitution does not occur¡ªwhen an a-
 rray name is an operand of either sizeof or the unary operator &. sizeof returns the 
 size of the entire array, not the size of a pointer to the array. Taking the address 
 of an array name gives a pointer to the first element in the array, not a pointer to 
 some substituted pointer constant value.

     int a[10];
     int b[10];
     b = a; // illegal
 You cannot use the assignment operator to copy all the elements of one array to ano-
 ther array; you must use a loop and copy one element at a time.

----> Subscripts
     int array[10];
     int *ap = array + 2;

ap 
    The expression &array[2] is equivalent.
*ap 
	the indirection follows the pointer to the location it is pointing at, which is -
	array[2].	 You could also write *(array + 2) .
ap[0]
    Remember, a subscript in C is exactly like an indirection expression , so you can
    use one anywhere you can use indirection. In this case, the equivalent expression 
    is *( ap + ( 0 ) ), Therefore it has the same answer: array [2] .
ap + 6 
    If ap points to array[2], this addition gives a pointer to the location six integ-
    ers later in the array, which is equivalent to array + 8 or &array[8] .   
*ap + 6 
    this expression is the same as array[2] + 6.
*(ap + 6) 
    The parentheses force the addition to go first , so this time we get the value of 
    array[8]. Observe that the indirection used here is in exactly the same form as -
    the indirection of a subscript.
&ap 
    This expression is perfectly legal, but there is no equivalent expression involv-
    ing @array because you cannot predict where the compiler will locate @ap relative 
    to @array
ap[-1] 
    A subscript is just an indirection expression; convert it to that form and then -
    evaluate it @ap points at the third element ( the one whose subscript is two), so 
    using an offset of ©\1 gets us the previous element: array[1] .
2[array]
    it is legal. Convert it to the equivalent indirection expression and you will see 
    its validity: *( array + 2 )

----> Declaring Array Parameters
 Here is an interesting question. What is the correct way to declare a function para-
 meter if you intend to pass it an array name argument? Is it declared as a  pointer,
 or as an array? the following function prototypes are equivalent:
    int strlen( char *string );
    int strlen( char string[] );
 You can use either declaration, but which is "more correct"? The pointer. The argum-
 ent is really a pointer, not the array. Also, the expression @sizeof string will pr-
 oduce the size of a pointer to a character, not the size of the array. 

----> Initialization
--------> Incomplete Initialization
     int vector[5] = { 1, 2, 3, 4, 5, 6 }; //error,
     int vector[5] = { 1, 2, 3, 4 };//is legal,the last element is initialized to zero.
--------> Automatic Array Sizing
    int vector[] = { 1, 2, 3, 4, 5 };//the compiler makes the array just big enough t-
                                     //o hold the initializers that were given. 
--------> Character Array Initialization
	char message[] = { 'H', 'e', 'l', 'l', 'o', 0 };
 The code works, but it is cumbersome for all but the shortest strings. Therefore,the
 language Standard provides a shorthand notation for initializing character arrays:
	char message[] = "Hello";
 Although this looks like a string literal, it is not . It is simply an alternate way 
 of writing the initializer list in the previous example. 
 Here is an example:
     char message1[] = "Hello";
     char *message2 = "Hello";
 The initializers look alike, but they have different meanings. The first initializes 
 the elements of a character array, but the second is a true siring literal. The poi-
 nter variable is initialized to point to wherever the literal is stored,

----> Multidimensional Arrays
 An array is called multidimensional if it has more than one dimension. Consider this 
 progression of declarations:
     int a;
     int b[10];
     int c[6][10];
     int d[3][6][10];
 @a is a single integer. By adding the dimension to the next declaration, @b is a ve-
 ctor containing ten integer elements. But all that has been done for @c is to add a-
 nother dimension, so we can view @c as a vector containing six elements, except that 
 each of those elements happens to be a vector of ten integers. In other words, @c is 
 a one-dimensional array of one-dimensional arrays. The same can be said of @d: it is 
 an array of three elements, each of which is an array of six elements, and each of -
 those is an array of ten integers. More concisely, @d is an array of three arrays of 
 six arrays of ten integers each.

 For example, the declaration:
     int matrix[3][10];
     
matrix
    Its type is "pointer to an array of ten integers", It points to the first array -
    of ten integers.
matrix + 1
    is also a "pointer to an array of ten integers", but it points to a different row 
    of the matrix.	( the value one is scaled by the size of an array of ten integers )
*(matrix + 1)
    Its type is "pointer to integer"
*( matrix + 1 ) + 5
    point to matrix[1][5], 
*( *( matrix + 1 ) + 5 )
    If used as an R-value, you would get the value stored there. As an L-value, the -
    location would receive a new value. matrix[1][5]

----> Pointers to Arrays
 Are these declarations legal?
     int vector[10], *vp = vector;//OK
     int matrix[3] [10], *mp = matrix;//Error
 @matrix is not a pointer to an integer, it is a pointer to an array of integers. How 
 would we declare a pointer to an array of integers?
      int (*p)[10];
 the parentheses surrounding the indirection force it to go first. So @p is a pointer 
 to something, but to what? The subscript is applied next, so @p points to some kind 
 of array. There aren't any more operators in the declaration expression, so each e-
 lement of the array is an integer.
      int (*p)[10] = matrix; //makes p point to the first row of matrix.
 If you intend to perform any arithmetic with the pointer, avoid this kind of declar-
 ation:     
      int (*p)[] = matrix;   // maybe error
 
----> Multidimensional Arrays as Function Arguments
 Here are two examples to illustrate the difference:
     int vector[10];
     ...
     func1( vector );
 The type of the argument @vector is a pointer to an integer, so func1 can be protot-
 yped in either of the following ways:
     void func1( int *vec );
     void func1( int vec[] );
 Now let's look at a matrix.
     int matrix[3][10];
     ...
     func2( matrix );
 Here the type of the argument matrix is a pointer to an array of ten integers . What 
 should the prototype for func2 look like? Either of the following forms could be used:
     void func2( int (*mat)[10] );
     void func2( int mat[][10] );





*/
