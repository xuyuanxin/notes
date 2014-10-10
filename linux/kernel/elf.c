
Elf32_Ehdr  /*elf文件头*/
Elf32_Shdr  /*段表*/
Elf32_Sym   /*符号表*/



/*
.rel.text 重定位表 .rel.data等
.strtab   字符串表 string table
.shstrtab 段表字符串表 section header string table
.symtab   符号表
基本概念
1 段表
  elf文件有各种各样的段，段表就是表述段属性的结构体数组。每个段对应一个Elf32_Shdr结构体。
2 符号
  符号  :函数、变量统称为符号
  符号名:函数名或符号名就是符号名
  符号值:每个符号有一个对应的值,对于函数和变量来说，符号值就是它们的地址
  强符号:初始化的全局变量或者函数
  弱符号:未初始化的全局变量

结构详解
Elf32_Ehdr
    e_ident[0] ~ [3]    魔数
    e_ident[4]          0x01表示是32位的,0x02表示是64位的
    e_ident[5]          大小端
    e_ident[6]          版本号
    e_ident[7] ~ [15]   保留