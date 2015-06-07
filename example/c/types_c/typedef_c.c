/*-----------------------------------------------------------------------------------
 typedef声明, 简称typedef, 为现有类型创建一个新的名字. typedef的使用方法如下:
     typedef existing_type new_type_name ;
 注意:typedef并不创建新的类型. 它仅仅为现有类型添加一个同义字.
 
     typedef unsigned int WORD; 
 定义了一个unsigned int的同义词, 名字为WORD, 你可以在任何需要int的上下文使用WORD.

 ----> typedef和数组,指针
 我们可以不用象下面这样重复定义有81个字符元素的数组:
     char line[81]; 
     char text[81];
 定义一个typedef, 每当要用到相同类型和大小的数组时, 可以这样:
     typedef char Line[81]; 
     Line text, secondline;

 同样, 可以象下面这样隐藏指针语法:
     typedef char * pstr; 
     pstr str = "abc";
     int mystrcmp(pstr, pstr);

 ----> typedef和函数
 /notes/example/c/pointer_c/pointer_base_c.c



 ----------------------------------------------------------------------------------*/
