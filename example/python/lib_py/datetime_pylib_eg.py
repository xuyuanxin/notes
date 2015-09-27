#_*_coding:UTF-8_*_

from  datetime  import  *  
import  time  
 


# datetime.datetime 
print   'datetime.max:' , datetime.max  
print   'datetime.min:' , datetime.min  
print   'datetime.resolution:' , datetime.resolution  
print   'today():' , datetime.today()  
print   'now():' , datetime.now()  
print   'utcnow():' , datetime.utcnow()  
print   'fromtimestamp(tmstmp):' , datetime.fromtimestamp(time.time())  
print   'utcfromtimestamp(tmstmp):' , datetime.utcfromtimestamp(time.time())

# # ---- 结果 ----   
# (%Y-%m-%d %H:%M:%S %f):  2010-04-07 10:52:18 937000   
# (%Y-%m-%d %H:%M:%S %p):  10-04-07 10:52:18 AM   
# %a: Wed    
# %A: Wednesday    
# %b: Apr    
# %B: April    
# 日期时间%c: 04/07/10 10:52:18    
# 日期%x：04/07/10    
# 时间%X：10:52:18    
# 今天是这周的第3天    
# 今天是今年的第097天    
# 今周是今年的第14周
dt = datetime.now()  
print   '(%Y-%m-%d %H:%M:%S %f): ' , dt.strftime( '%Y-%m-%d %H:%M:%S %f' )  
print   '(%Y-%m-%d %H:%M:%S %p): ' , dt.strftime( '%y-%m-%d %I:%M:%S %p' )  
print   '%%a: %s '  % dt.strftime( '%a' )  
print   '%%A: %s '  % dt.strftime( '%A' )  
print   '%%b: %s '  % dt.strftime( '%b' )  
print   '%%B: %s '  % dt.strftime( '%B' )  
print   '日期时间%%c: %s '  % dt.strftime( '%c' )  
print   '日期%%x：%s '  % dt.strftime( '%x' )  
print   '时间%%X：%s '  % dt.strftime( '%X' )  
print   '今天是这周的第%s天 '  % dt.strftime( '%w' )  
print   '今天是今年的第%s天 '  % dt.strftime( '%j' )  
print   '今周是今年的第%s周 '  % dt.strftime( '%U' )  











