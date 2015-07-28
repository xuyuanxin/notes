#include <stdio.h>

/*-----------------------------------------------------------------------------------
 控制字符的通用格式如下: Esc[{attr1};...;{attrn}m

 其中:
 Esc 是转义字符, 其值为"\033";
 [ 是常量的左中括号;
 {attr1};...{attrn} 是若干属性, 通常是由一个有特定意义的数字代替, 每个属性之间用分号分隔;
 m 就是字面常量字符m;

 属性列表如下:
 1. 通用格式控制:
 0 重置所有属性;  1 高亮/加粗;  2 暗淡;  4 下划线;  5 闪烁;  7 反转;  8 隐藏;

 2. 字体颜色
 30 黑色;  31 红色;  32 绿色;  33 黄色;  34 蓝色;  35 品红;  36 青色;  37 白色

 3. 背景色:
 40 黑色;  41 红色;  42 绿色;  43 黄色;  44 蓝色;  45 品红;  46 青色;  47 白色
 ----------------------------------------------------------------------------------*/
int main()
{
    printf("\033[1;40;32m__This text is xxx__\033[0m\n");
    printf("\033[2;40;32m__This text is xxx__\033[0m\n");
    printf("\033[3;40;32m__This text is xxx__\033[0m\n");
    printf("\033[4;40;32m__This text is xxx__\033[0m\n");
    printf("\033[5;40;32m__This text is xxx__\033[0m\n");
    printf("\033[6;40;32m__This text is xxx__\033[0m\n");
    printf("\033[7;40;32m__This text is xxx__\033[0m\n");

    printf("\033[1;4;40;32m__This text is xxx__\033[0m\n");

	
    printf("\033[40;30m__This text is xxx__\033[0m\n");
    printf("\033[40;31m__This text is xxx__\033[0m\n");
    printf("\033[40;32m__This text is xxx__\033[0m\n");
    printf("\033[40;33m__This text is xxx__\033[0m\n");
    printf("\033[40;34m__This text is xxx__\033[0m\n");
    printf("\033[40;35m__This text is xxx__\033[0m\n");
    printf("\033[40;36m__This text is xxx__\033[0m\n");
    printf("\033[40;37m__This text is xxx__\033[0m\n");

    printf("\033[41;30m__This text is xxx__\033[0m\n");
    printf("\033[41;31m__This text is xxx__\033[0m\n");
    printf("\033[41;32m__This text is xxx__\033[0m\n");
    printf("\033[41;33m__This text is xxx__\033[0m\n");
    printf("\033[41;34m__This text is xxx__\033[0m\n");
    printf("\033[41;35m__This text is xxx__\033[0m\n");
    printf("\033[41;36m__This text is xxx__\033[0m\n");
    printf("\033[41;37m__This text is xxx__\033[0m\n");

    printf("\033[42;30m__This text is xxx__\033[0m\n");
    printf("\033[42;31m__This text is xxx__\033[0m\n");
    printf("\033[42;32m__This text is xxx__\033[0m\n");
    printf("\033[42;33m__This text is xxx__\033[0m\n");
    printf("\033[42;34m__This text is xxx__\033[0m\n");
    printf("\033[42;35m__This text is xxx__\033[0m\n");
    printf("\033[42;36m__This text is xxx__\033[0m\n");
    printf("\033[42;37m__This text is xxx__\033[0m\n");

    printf("\033[43;30m__This text is xxx__\033[0m\n");
    printf("\033[43;31m__This text is xxx__\033[0m\n");
    printf("\033[43;32m__This text is xxx__\033[0m\n");
    printf("\033[43;33m__This text is xxx__\033[0m\n");
    printf("\033[43;34m__This text is xxx__\033[0m\n");
    printf("\033[43;35m__This text is xxx__\033[0m\n");
    printf("\033[43;36m__This text is xxx__\033[0m\n");
    printf("\033[43;37m__This text is xxx__\033[0m\n");

    printf("\033[44;30m__This text is xxx__\033[0m\n");
    printf("\033[44;31m__This text is xxx__\033[0m\n");
    printf("\033[44;32m__This text is xxx__\033[0m\n");
    printf("\033[44;33m__This text is xxx__\033[0m\n");
    printf("\033[44;34m__This text is xxx__\033[0m\n");
    printf("\033[44;35m__This text is xxx__\033[0m\n");
    printf("\033[44;36m__This text is xxx__\033[0m\n");
    printf("\033[44;37m__This text is xxx__\033[0m\n");

    printf("\033[45;30m__This text is xxx__\033[0m\n");
    printf("\033[45;31m__This text is xxx__\033[0m\n");
    printf("\033[45;32m__This text is xxx__\033[0m\n");
    printf("\033[45;33m__This text is xxx__\033[0m\n");
    printf("\033[45;34m__This text is xxx__\033[0m\n");
    printf("\033[45;35m__This text is xxx__\033[0m\n");
    printf("\033[45;36m__This text is xxx__\033[0m\n");
    printf("\033[45;37m__This text is xxx__\033[0m\n");

    printf("\033[46;30m__This text is xxx__\033[0m\n");
    printf("\033[46;31m__This text is xxx__\033[0m\n");
    printf("\033[46;32m__This text is xxx__\033[0m\n");
    printf("\033[46;33m__This text is xxx__\033[0m\n");
    printf("\033[46;34m__This text is xxx__\033[0m\n");
    printf("\033[46;35m__This text is xxx__\033[0m\n");
    printf("\033[46;36m__This text is xxx__\033[0m\n");
    printf("\033[46;37m__This text is xxx__\033[0m\n");

	printf("\033[47;30m__This text is xxx__\033[0m\n");
    printf("\033[47;31m__This text is xxx__\033[0m\n");
    printf("\033[47;32m__This text is xxx__\033[0m\n");
    printf("\033[47;33m__This text is xxx__\033[0m\n");
    printf("\033[47;34m__This text is xxx__\033[0m\n");
    printf("\033[47;35m__This text is xxx__\033[0m\n");
    printf("\033[47;36m__This text is xxx__\033[0m\n");
    printf("\033[47;37m__This text is xxx__\033[0m\n");

	return 0;
}
