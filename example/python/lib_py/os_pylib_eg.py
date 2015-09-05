#_*_coding:UTF-8_*_

import os  
for root, dirs, files in os.walk(r'F:\mygit\notes\example\python\lib_py'):  
    print root   #当前遍历到的目录的根  
    print dirs   #当前遍历到的目录的根下的所有目录  
    print files  #当前遍历到的目录的根下的所有文件 