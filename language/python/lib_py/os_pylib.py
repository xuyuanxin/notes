# os.


def listdir(path) # os.listdir
  '''
  Return a list containing the names of the entries(file or directory) in the direct-
  ory given by @path. The list is in arbitrary order. It does not include the special 
  entries '.' and  '..' even if they are present in the directory.
  '''
  pass

def walk(top, topdown=True, onerror=None, followlinks=False):
  '''
  @top
    需要遍历的目录树的路径。
  @topdown                                                                             |
    默认值是"True", 表示首先返回目录树下的文件, 然后在遍历目录树的子目录. Topdown的值|
	为"False"时, 则表示先遍历目录树的子目录, 返回子目录下的文件, 最后返回根目录下的文|
	件.                                                                              |
  @onerror                                                                             |
    默认值是"None", 表示忽略文件遍历时产生的错误. 如果不为空, 则提供一个自定义函数提 |
	示错误信息后继续遍历或抛出异常中止遍历.
  @followlinks
    默认值是False, 默认情况下是不会遍历快捷方式的, 如果系统支持需要特殊指定.
  @return
    os.walk方法返回三元组：
    dirpath：  目录的路径。
    dirnames： dirpath目录下所有子目录列表（不包含"."和".."）。
    filenames：dirpath目录下所有非目录文件列表。
  F:\aaa 目录是这样的文件目录结构
  F:\aaa
  |--------1.txt
  |--------2.txt
  |--------3.txt
  |--------4
    |-------5.txt
    |-------6.txt
    |-------7.txt

  # os.walk()的使用  
  import os  
  
  # 枚举dirPath目录下的所有文件  
  
  def main():    
    fileDir = "F:" + os.sep + "aaa"     # 查找F:\aaa 目录下    
    for root, dirs, files in os.walk(fileDir):  
      print(root)  
      print(dirs)  
      print(files)  
    os.system("pause")     
  if __name__ == '__main__':   
    main()  

  # 输出  
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
  able to parse or concatenate pathnames — use os.path.split() and os.path.join() — 
  but it is occasionally useful. Also available via os.path.   
 

''' os.system(command)
Execute the command (a string) in a subshell. 
'''
def system(command):
    pass

'''
15.1.6. Miscellaneous System Information


'''	
