/*
功能：把src所指由NULL结束的字符串的前n个字节复制到dst所指的数组中。
返回：返回指向dst的指针（该指向dst的最后一个元素）
说明：如果src的前n个字节不含NULL字符，则结果不会以NULL字符结束。        
      如果src的长度小于n个字节，则以NULL填充dest直到复制完n个字节(所以拷贝效率低些)。        
      src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。        
*/
char *strncpy(char *dst, const char *src, size_t n); 

