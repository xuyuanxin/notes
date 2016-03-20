/*-----------------------------------------------------------------------------------
 http://www.cnblogs.com/cpoint/p/3368993.html C语言中可变参数函数实现原理
 http://www.cnblogs.com/cpoint/p/3374994.html stdarg.h头文件源代码分析



 The header declares a type va_list and three macros, va_start, va_arg, and va_end.


*/

typedef char *va_list;

void va_start( va_list arg_ptr, prev_param ); 
type va_arg( va_list arg_ptr, type ); 
void va_end( va_list arg_ptr ); 



/*
 Compute the average of the specified number of values.

 The function declares a variable called var_arg with which to access the
unspecified portion of the argument list. This variable is initialized by calling
va_start. The first parameter is the name of the va_list variable, and the second
parameter is the last named argument before the ellipsis. This initialization sets the
var_arg variable to point to the first of the variable arguments.
To access an argument, va_arg is used. This macro takes two parameters: the
va_list variable and the type of the next value in the list. In this example, the variable
arguments are all integers. In some functions, you may have to determine the type of
the next argument by examining previously obtained data.34 va_arg returns the value
of this argument and advances var_arg to point to the next variable argument.
Finally, va_end is called after the last access to the variable arguments.

Note that the variable arguments must be accessed one by one, in order, from start to
finish. You can stop early if you wish, but there isn?t any way to begin accessing in the
middle of the list. In addition, because the variable portion of the argument list is not
prototyped, the default argument promotions are performed on all values passed as
variable arguments.

You may also have noticed the requirement that there must be at least one
named argument in the argument list; you cannot use va_start without it. This
argument provides a way to locate the varying portion of the argument list



*/
float average( int n_values, ... )
{
    va_list var_arg;
    int count;
    float sum = 0;

    /*
    ** Prepare to access the variable arguments.
    */
    va_start( var_arg, n_values );

    /*
    ** Add the values from the variable argument list.
    */
    for( count = 0; count < n_values; count += 1 )
    {
        sum += va_arg( var_arg, int );
    }

    /*
    ** Done processing variable arguments.
    */
    va_end( var_arg );

    return sum / n_values;
}




#ifndef _STDARG_H
#define _STDARG_H


#ifdef __GNUC__
/* The GNU C-compiler uses its own, but similar varargs mechanism. */

typedef char *va_list;

/* Amount of space required in an argument list for an arg of type TYPE.
 * TYPE may alternatively be an expression whose type is used.
 */

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#if __GNUC__ < 2

#ifndef __sparc__
#define va_start(AP, LASTARG)                                           \
 (AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#else
#define va_start(AP, LASTARG)                                           \
 (__builtin_saveregs (),                                                \
  AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#endif

void va_end (va_list);          /* Defined in gnulib */
#define va_end(AP)

#define va_arg(AP, TYPE)                                                \
 (AP += __va_rounded_size (TYPE),                                       \
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

#else    /* __GNUC__ >= 2 */

#ifndef __sparc__
#define va_start(AP, LASTARG)                         \
 (AP = ((char *) __builtin_next_arg ()))
#else
#define va_start(AP, LASTARG)                    \
  (__builtin_saveregs (), AP = ((char *) __builtin_next_arg ()))
#endif

void va_end (va_list);        /* Defined in libgcc.a */
#define va_end(AP)

#define va_arg(AP, TYPE)                        \
 (AP = ((char *) (AP)) += __va_rounded_size (TYPE),            \
  *((TYPE *) ((char *) (AP) - __va_rounded_size (TYPE))))

#endif    /* __GNUC__ >= 2 */

#else    /* not __GNUC__ */


typedef char *va_list;

#define __vasz(x)        ((sizeof(x)+sizeof(int)-1) & ~(sizeof(int) -1))

#define va_start(ap, parmN)    ((ap) = (va_list)&parmN + __vasz(parmN))
#define va_arg(ap, type)      \
  (*((type *)((va_list)((ap) = (void *)((va_list)(ap) + __vasz(type))) \
                            - __vasz(type))))
#define va_end(ap)


#endif /* __GNUC__ */

#endif /* _STDARG_H */


