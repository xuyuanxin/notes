/* http://www.tutorialspoint.com/c_standard_library/index.htm */

/*-----------------------------------------------------------------------------------
NULL
    A null-pointer constant is an integral constant expression that evaluates to zero 
    (like 0 or 0L), or the cast of such value to type void* (like (void*)0).
    A null pointer constant can be converted to any pointer type (or pointer-to-member 
    type), which acquires a null pointer value. This is a special value that indicates 
    that the pointer is not pointing to any object.
EXIT_FAILURE
    This is the value for the exit function to return in case of failure.
EXIT_SUCCESS
    This is the value for the exit function to return in case of success. 
-----------------------------------------------------------------------------------*/
#define NULL          /* null pointer constant. */
#define EXIT_FAILURE  /*  */
#define EXIT_SUCCESS  /* */



/*-----------------------------------------------------------------------------------
 @str
    C-string beginning with the representation of an integral number.
 @func
    Convert string to integer
 @ret
    On success,the function returns the converted integral number as an int value. If 
    the converted value would  be out of the range of representable values by an int, 
    it causes undefined behavior. See @strtol for a more robust cross-platform alter-
    native when this is a possibility. 

 The function first discards as many whitespace characters (as in isspace) as necess-
 ary until the first non-whitespace character is found. Then, starting from this cha-
 racter, takes an optional initial plus or minus sign followed by as many base-10 di-
 gits as possible, and interprets them as a numerical value. 
 The string can contain additional characters after those that form the integral num-
 ber, which are ignored and have no effect on the behavior of this function. If the -
 first sequence of non-whitespace characters in  @str is not a valid integral number, 
 or if no such sequence exists because either @str is empty or it contains only whit-
 espace characters, no conversion is performed and zero is returned.    
-----------------------------------------------------------------------------------*/
int atoi (const char * str);


/*-----------------------------------------------------------------------------------
 @str
    C-string containing the representation of an integral number.
 @func
    Convert string to long integer
 @ret
    On success, the function returns the converted integral number as a long int val-
    ue. If  no valid conversion could be performed, a zero  value is returned. If the 
    converted value would be out of the range  of representable values by a long int, 
    it causes undefined behavior. See strtol for a more robust cross-platform alter-
    native when this is a possibility.

 The function first discards as many whitespace characters (as in @isspace) as neces-
 sary until the first non-whitespace character is found. Then, starting from this ch-
 aracter, takes an optional initial plus or minus sign followed by as many base-10 d-
 igits as possible, and interprets them as a numerical value.
 The string can contain additional characters after those that form the integral num-
 ber, which are ignored and have no effect on the behavior of this function.
 If the first sequence of non-whitespace characters in str is not a valid integral n-
 umber, or if no such sequence exists because either str is empty or it contains onl-
 y whitespace characters, no conversion is performed and zero is returned.    
-----------------------------------------------------------------------------------*/
long int atol ( const char * str );


/************************************************************************************
 @ret:
    0 if OK, nonzero on error
 @func
    The @putenv function takes a string of the form name=value and places it in the
    environment list. If name already exists, its old definition is first removed.
************************************************************************************/
int putenv(char *str);


/*-----------------------------------------------------------------------------------
 @ptr
    Pointer to a memory block previously allocated with malloc, calloc or realloc. A-
    lternatively, this can be a null pointer , in which case a new block is allocated 
    (as if malloc was called).
 @size
    New size for the memory block, in bytes.
 @func
    Reallocate memory block. Changes the size of the memory block pointed to by @ptr.
 @ret
    A null-pointer indicates either that @size was zero(an thus @ptr was deallocated), 
    or that the function did not allocate storage (and thus the block pointed by @ptr 
    was not modified).(C90 C++98)
    A null-pointer indicates that the function failed to allocate storage, and thus -
    the block pointed by @ptr was not modified.(C99 C11 C++11)

 The function may move the memory block to a new location ( whose address is returned 
 by the function). The content of the memory block is preserved up to the lesser of -
 the new and old sizes, even if the block is moved to a new location. If the new size 
 is larger, the value of the newly allocated portion is indeterminate.    

 1 In case that @ptr is a null pointer, the function behaves like @malloc , assigning 
   a new block of size bytes and returning a pointer to its beginning.
 2 if @size is zero, the memory previously allocated at @ptr is deallocated as if a -
   call to @free was made, and a null pointer is returned.(C90 C++98)
   If @size is zero, the return value depends on the particular library implementati-
   on: it may either be a null pointer or some other location that shall not be dere-
   ferenced.(C99 C11 C++11)
 3 If the function fails to allocate the requested block of memory, a null pointer is 
   returned, and the memory block pointed to by argument @ptr is not deallocated ( it 
   is still valid, and with its contents unchanged).

reference
    http://www.cplusplus.com/reference/cstdlib/realloc/?kw=realloc
    http://blog.csdn.net/snlying/article/details/4005238
example: realloc_eg01()
-----------------------------------------------------------------------------------*/
void* realloc (void* ptr, size_t size);

/*-----------------------------------------------------------------------------------
 @num
    Number of elements to allocate.
 @size
    Size of each element.
 @fun
    Allocate and zero-initialize array
 @ret
    On success, a pointer to the memory block allocated by the function. The type of 
    this pointer is always void*, which can be cast to the desired type of data poin-
    ter in order to be dereferenceable. If the function failed to allocate the reque-
    sted block of memory, a null pointer is returned.

 Allocates a block of memory for an array of @num elements, each of them @size bytes 
 long, and initializes all its bits to zero. The effective result is the allocation -
 of a zero-initialized memory block of (@num*@size) bytes.
 If @size is zero, the return value depends on the particular library implementation 
 (it may or may not be a null pointer), but the returned pointer shall not be derefe-
 renced.

reference
example:
-----------------------------------------------------------------------------------*/
void* calloc (size_t num, size_t size);


/*-----------------------------------------------------------------------------------
 @ptr
    Pointer to a memory block previously allocated with malloc, calloc or realloc.
 @func
    Deallocate memory block
    
 A block of memory previously allocated by a call to malloc, calloc or realloc is de-
 allocated, making it available again for further allocations. If @ptr does not point 
 to a block of memory allocated with the above functions,it causes undefined behavior.
 If @ptr is a null pointer, the function does nothing. Notice that this function does 
 not change the value of @ptr itself, hence it still points to the same (now invalid) 
 location.

reference
    http://www.cplusplus.com/reference/cstdlib/free/?kw=free
example:
-----------------------------------------------------------------------------------*/
void free (void* ptr);


/* Returns the absolute value of parameter n  */
int abs (int n);






/* This function is a GNU extension. #include <malloc.h>*/
size_t malloc_usable_size (void *ptr); 


void realloc_eg01()
{
	nptr = realloc(ptr, newsize);
	if (nptr == NULL) {
		/* Handle error */
	} else { /* realloc() succeeded */
		ptr = nptr;
	}
}

/*-----------------------------------------------------------------------------------
 The system() function allows the calling program to execute an arbitrary shell comm-
 and. 

 example: system("ls | wc");

-----------------------------------------------------------------------------------*/
int system(const char *command);


void* malloc (size_t size);


