import pandas
d = pandas.read_csv(r".\data.csv") 
print '1---->\n', d

d = pandas.read_csv(r".\data.csv",header=None) 
print '2---->\n', d

d = pandas.read_csv(r".\data.csv",header=None,names=['index','domain']) 
print '3---->\n', d

'''
-------------- data.csv
1,a.com
2,b.com
3,c.com
--------------

1---->
   1  a.com
0  2  b.com
1  3  c.com
2---->
   0      1
0  1  a.com
1  2  b.com
2  3  c.com
3---->
   index domain
0      1  a.com
1      2  b.com
2      3  c.com
'''