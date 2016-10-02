#coding=utf-8

import shutil
import os

srcdir=r'G:\xdata_picture\DCIM\DCIM'
dstdir1=r'C:\Users\yuanxin\Desktop\’’∆¨\œ¥1’≈'
dstdir2=r'C:\Users\yuanxin\Desktop\’’∆¨\œ¥2’≈'
getlist=[ \
'IMG_7763.JPG,1',\
'IMG_7764.JPG,1',\
'IMG_7767.JPG,1',\
'IMG_7765.JPG,1',\
'IMG_7702.JPG,1',\
'IMG_7709.JPG,1',\
'IMG_7715.JPG,1',\
'IMG_7732.JPG,1',\
'IMG_7733.JPG,1',\
'IMG_7778.JPG,1',\
'IMG_7779.JPG,1',\
'IMG_7785.JPG,1',\
'IMG_7788.JPG,1',\
'IMG_7789.JPG,1',\
'IMG_7790.JPG,1',\
'IMG_7792.JPG,1',\
'IMG_7794.JPG,1',\
'IMG_7796.JPG,1',\
'IMG_7802.JPG,1',\
'IMG_7808.JPG,1',\
'IMG_7821.JPG,1',\
'IMG_7835.JPG,1',\
'IMG_7836.JPG,1',\
'IMG_7837.JPG,1',\
'IMG_7838.JPG,1',\
'IMG_7840.JPG,1',\
'IMG_7845.JPG,1',\
'IMG_7852.JPG,1',\
'IMG_7855.JPG,1',\
'IMG_7856.JPG,1',\
'IMG_7872.JPG,1',\
'IMG_7877.JPG,1',\
'IMG_7883.JPG,1',\
'IMG_7885.JPG,1',\
'IMG_7889.JPG,1',\
'IMG_7891.JPG,1',\
'IMG_7911.JPG,1',\
'IMG_7912.JPG,1',\
'IMG_7913.JPG,1',\
'IMG_7925.JPG,1',\
'IMG_7932.JPG,1',\
'IMG_7933.JPG,1',\
'IMG_7937.JPG,1',\
'IMG_7938.JPG,1',\
'IMG_7939.JPG,1',\
'IMG_7946.JPG,1',\
'IMG_7965.JPG,1',\
'IMG_7966.JPG,1',\
'IMG_7969.JPG,1',\
'IMG_7975.JPG,1',\
'IMG_7992.JPG,1',\
'IMG_7996.JPG,1',\
'IMG_8010.JPG,1',\
'IMG_8011.JPG,1',\
'IMG_8026.JPG,1',\
'IMG_8192.JPG,1',\
'IMG_8200.JPG,1',\
'IMG_8201.JPG,1',\
'IMG_8204.JPG,1',\
'IMG_8205.JPG,1',\
'IMG_8208.JPG,1',\
'IMG_8210.JPG,1',\
'IMG_8211.JPG,1',\
'IMG_8212.JPG,1',\
'IMG_8213.JPG,1',\
'IMG_8214.JPG,1',\
'IMG_8215.JPG,1',\
'IMG_8216.JPG,1',\
'IMG_8217.JPG,1',\
'IMG_8218.JPG,1',\
'IMG_8221.JPG,1',\
'IMG_8223.JPG,1',\
'IMG_8224.JPG,1',\
'IMG_8227.JPG,1',\
'IMG_8228.JPG,1',\
'IMG_8230.JPG,1',\
'IMG_8231.JPG,1',\
'IMG_8232.JPG,1',\
'IMG_8236.JPG,1',\
'IMG_8248.JPG,1',\
'IMG_8250.JPG,1',\
'IMG_8256.JPG,1',\
'IMG_8261.JPG,1',\
'IMG_8262.JPG,1',\
'IMG_8273.JPG,1',\
'IMG_8301.JPG,1',\
'IMG_8302.JPG,1',\
'IMG_8065.JPG,1',\
'IMG_8068.JPG,1',\
'IMG_8069.JPG,1',\
'IMG_8082.JPG,1',\
'IMG_8083.JPG,1',\
'IMG_8084.JPG,1',\
'IMG_8085.JPG,1',\
'IMG_8098.JPG,1',\
'IMG_8101.JPG,1',\
'IMG_8102.JPG,1',\
'IMG_8106.JPG,1',\
'IMG_8108.JPG,1',\
'IMG_8111.JPG,1',\
'IMG_8113.JPG,1',\
'IMG_8121.JPG,1',\
'IMG_8128.JPG,1',\
'IMG_8146.JPG,1',\
'IMG_8148.JPG,1',\
'IMG_8160.JPG,1',\
'IMG_8057.JPG,1',\
'IMG_8056.JPG,1',\
'IMG_8043.JPG,1',\
'IMG_8038.JPG,1',\
'IMG_8037.JPG,1',\
'IMG_8036.JPG,1',\
'IMG_8035.JPG,1',\
'IMG_8036.JPG,1',\
'IMG_8037.JPG,1',\
'IMG_8042.JPG,1',\
'IMG_8051.JPG,1',\
'IMG_8056.JPG,1',\
]


for item in getlist:
    
getlist = set(getlist)

files = os.listdir(srcdir)
#print('files:%s'%(files))
#print('getlist:%s'%(getlist))

for fpath,dirs,fs in os.walk(srcdir):
  for f in fs:
    if f in getlist:
      sfile = os.path.join(fpath,f)
      tfile = os.path.join(dstdir,f)
      print('copy file %s to %s'%(sfile,tfile))
      shutil.copy(sfile,tfile)

exit(0)

for file in files:
    if file in getlist:
        sourceFile = os.path.join(srcdir,file)
        targetFile = os.path.join(dstdir,file)
        print('copy file %s to %s'%(sourceFile,targetFile))
        shutil.copy(sourceFile,targetFile)