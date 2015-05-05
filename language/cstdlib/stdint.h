
//http://www.cnblogs.com/Anker/p/3438480.html
/*intptr_t在不同的平台是不一样的,始终与地址位数相同,因此用来存放地址,即地址.*/
/* Types for `void *' pointers.  */
#if __WORDSIZE == 64
# ifndef __intptr_t_defined
typedef long int		intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned long int	uintptr_t;
#else
# ifndef __intptr_t_defined
typedef int			intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned int		uintptr_t;
#endif
