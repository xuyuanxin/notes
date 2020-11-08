# os.


def listdir(path) # os.listdir
  '''
  Return a list containing the names of the entries(file or directory) in the direct-
  ory given by @path. The list is in arbitrary order. It does not include the special 
  entries '.' and  '..' even if they are present in the directory.
  '''
  pass

def mkdir(path[, mode]) # os.mkdir
  '''
  Create a directory named @path with numeric @mode mode. The default @mode is 0777 -
  (octal). On some systems, mode is ignored. Where it is used, the current umask val-
  ue is first masked out. If the directory already exists, OSError is raised. 
  '''
  pass
  
def walk(top, topdown=True, onerror=None, followlinks=False):
  '''
  @top
    ��Ҫ������Ŀ¼����·����
  @topdown                                                                             |
    Ĭ��ֵ��"True", ��ʾ���ȷ���Ŀ¼���µ��ļ�, Ȼ���ڱ���Ŀ¼������Ŀ¼. Topdown��ֵ|
	Ϊ"False"ʱ, ���ʾ�ȱ���Ŀ¼������Ŀ¼, ������Ŀ¼�µ��ļ�, ��󷵻ظ�Ŀ¼�µ���|
	��.                                                                              |
  @onerror                                                                             |
    Ĭ��ֵ��"None", ��ʾ�����ļ�����ʱ�����Ĵ���. �����Ϊ��, ���ṩһ���Զ��庯���� |
	ʾ������Ϣ������������׳��쳣��ֹ����.
  @followlinks
    Ĭ��ֵ��False, Ĭ��������ǲ��������ݷ�ʽ��, ���ϵͳ֧����Ҫ����ָ��.
  @return
    os.walk����������Ԫ�飺
    dirpath��  Ŀ¼��·����
    dirnames�� dirpathĿ¼��������Ŀ¼�б�������"."��".."����
    filenames��dirpathĿ¼�����з�Ŀ¼�ļ��б�
  F:\aaa Ŀ¼���������ļ�Ŀ¼�ṹ
  F:\aaa
  |--------1.txt
  |--------2.txt
  |--------3.txt
  |--------4
    |-------5.txt
    |-------6.txt
    |-------7.txt

  # os.walk()��ʹ��  
  import os  
  
  # ö��dirPathĿ¼�µ������ļ�  
  
  def main():    
    fileDir = "F:" + os.sep + "aaa"     # ����F:\aaa Ŀ¼��    
    for root, dirs, files in os.walk(fileDir):  
      print(root)  
      print(dirs)  
      print(files)  
    os.system("pause")     
  if __name__ == '__main__':   
    main()  

  # ���  
  # F:\aaa  
  # ['4']  
  # ['1.txt', '2.txt', '3.txt']  
  # F:\aaa\4  
  # []  
  # ['5.txt', '6.txt', '7.txt']  	
  '''
  pass

os.sep
  The character used by the operating system to separate pathname components. This is 
  '/' for POSIX and '\\' for Windows. Note that knowing this is not sufficient to  be 
  able to parse or concatenate pathnames �� use os.path.split() and os.path.join() �� 
  but it is occasionally useful. Also available via os.path.   
 

''' os.system(command)
Execute the command (a string) in a subshell. 
'''
def system(command):
    pass

'''
15.1.6. Miscellaneous System Information


'''	
