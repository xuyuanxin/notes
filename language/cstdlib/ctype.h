
/*-----------------------------------------------------------------------------------
 @c
    Character to be checked, casted to an int, or EOF.
 @ret
    A value different from zero (i.e., true) if indeed c is a white-space character. 
    Zero (i.e., false) otherwise.
 @func
    Checks whether @c is a white-space character.

 white-space characters are any of:
 ' '  (0x20)   space (SPC)
 '\t' (0x09)   horizontal tab (TAB)
 '\n' (0x0a)   newline (LF)
 '\v' (0x0b)   vertical tab (VT)
 '\f' (0x0c)   feed (FF)
 '\r' (0x0d)   carriage return (CR)
-----------------------------------------------------------------------------------*/
int isspace ( int c );


/*-----------------------------------------------------------------------------------
 @c
    Character to be checked, casted to an int, or EOF.
 @func
    Check if character is decimal digit
 @ret
    A value different from zero(i.e.,true) if indeed c is a decimal digit. Zero(i.e., 
    false) otherwise.

 Decimal digits are any of: 0 1 2 3 4 5 6 7 8 9
-----------------------------------------------------------------------------------*/
int isdigit ( int c );



/*-----------------------------------------------------------------------------------
 Check if character is alphabetic
-----------------------------------------------------------------------------------*/
int isalpha ( int c );


