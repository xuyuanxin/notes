'''
file()�ڽ��������Ĺ��ܵ���open(),���ǿ��Կ��������Ǹ��ļ�����(�����ļ�����)��������int()�������Ͷ���dict()�����ֵ����


file(	filename[, mode[, bufsize]])

file()������2.2�������ĺ���������open()����һ�����൱��open()�ı�����������open()��ֱ��һЩ��


����һ���ļ������ݺܼ򵥣�



text = file(filename).read()


������ʡ����ģʽ(mode)��������ȱʡΪ��r'��


���� Python �Ѿ�֧��������Ҫƽ̨�Ļس�������\n����Unix�Ļ��з�����r'��Macintosh�Ļ��з�����\r\n����Windows�Ļ��з�����ô�ڴ��ļ�ʱʹ�á�U'��rU��ģʽ�Ϳ���ͬʱ֧�������ֻ��з���


���Ҫ���ļ�����һ���еĴ����ж��ַ�����



��һ���Խ��ı��ж���һ���б��У��ٶ��б���д���


lines = file(filename).readlines()
for line in lines:
    print line



ʹ���ļ������readline()��������һ���еĴ���


f = file(filename)
while True:
    line = f.readline()
    if line:
        print line
    else:
        break



���о���2.3�е��·�������forѭ����ֱ��ʹ���ļ�����


for line in file(filename):
    print line


������Ϊ�ļ������������˵������ܡ�


ע�⣺���������ÿһ�ж����лس����������ĳЩ������������Ҫ������ȥ����

'''
def file(name[, mode[, buffering]]):
    pass