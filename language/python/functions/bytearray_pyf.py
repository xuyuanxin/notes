bytearray([source [, encoding [, errors]]])
˵����bytearray([source [, encoding [, errors]]])����һ��byte���顣Bytearray������һ���ɱ�����У����������е�Ԫ�ص�ȡֵ��ΧΪ [0 ,255]��

����source: 

���sourceΪ�������򷵻�һ������Ϊsource�ĳ�ʼ�����飻

���sourceΪ�ַ���������ָ����encoding���ַ���ת��Ϊ�ֽ����У�

���sourceΪ�ɵ������ͣ���Ԫ�ر���Ϊ[0 ,255]�е�������

���sourceΪ��buffer�ӿ�һ�µĶ�����˶���Ҳ���Ա����ڳ�ʼ��bytearray.��

ʾ����
>>> a = bytearray(3) 
>>> a
bytearray(b'\x00\x00\x00')
>>> a[0]
0
>>> a[1]
0
>>> a[2]
0
>>> b = bytearray("abc")
>>> b
bytearray(b'abc')
>>> b[0]
97 
>>> b[1]
98
>>> b[2]
99
>>> c = bytearray([1, 2, 3])
>>> c
bytearray(b'\x01\x02\x03')
>>> c[0]
1
>>> c[1]
2
>>> c[2]
3
>>> d = bytearray(buffer("abc"))
>>> d
bytearray(b'abc')
>>> d[0]
97
>>> d[1]
98
>>> d[2]
99















