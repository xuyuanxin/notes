
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

/*-----------------------------------------------------------------------------------
 http://www.cnblogs.com/ShaneZhang/archive/2013/06/21/3147648.html

 格式化输出：
 unit64_t     %llu   
 unit32_t     %u
 unit16_t    %hu
 ----------------------------------------------------------------------------------*/
 
/* There is some amount of overlap with <sys/types.h> as known by inet code */
#ifndef __int8_t_defined
# define __int8_t_defined
typedef signed char             int8_t; 
typedef short int               int16_t;
typedef int                     int32_t;
# if __WORDSIZE == 64
typedef long int                int64_t;
# else
__extension__
typedef long long int           int64_t;
# endif
#endif

/* Unsigned.  */
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
#ifndef __uint32_t_defined
typedef unsigned int            uint32_t;
# define __uint32_t_defined
#endif
#if __WORDSIZE == 64
typedef unsigned long int       uint64_t;
#else
__extension__
typedef unsigned long long int  uint64_t;
#endif

