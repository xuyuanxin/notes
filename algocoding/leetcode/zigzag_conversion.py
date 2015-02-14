
####################################################################################
'''
n=5
0       8           16           24    | 8 8 8     2*n-2  
1     7 9        15 17        23 25    | 6 2 6
2   6   10    14    18     21    26    | 4 4 4
3 5     11 13       19  21       27    | 2 6 2
4       12          20           28    | 8 8 8

'''

class Solution:   
    # @return a string 
    def convert_v1(self, s, nRows):    
        if nRows==1: return s 
        if len(s)<=1: return s		
        tmp = []    
        for row in range(nRows):
            if 0==row or (nRows-1)==row:
                idx = row            
                while idx < len(s):
                    tmp.append(s[idx])
                    idx+=(2*nRows-2)
            else:
                idx = row;cnt = 0
                while idx < len(s):
                    tmp.append(s[idx])
                    if(0 == cnt%2):
                        idx+=(2*nRows-2 - row*2)
                    else:
                        idx+=row*2
                    cnt+=1
        return ''.join(tmp)
		
    # @return a string
	# http://blog.csdn.net/hyperbolechi/article/details/43217949
    def convert_v2(self, s, nRows):
        if nRows==1:
            return s
        if len(s)<=1:
            return s
        n=nRows
        size=2*n-2
        result=[]
        for i in range(n):
            j=i
            while j<len(s):
                result.append(s[j])
                if i!=0 and i!=n-1 and j+size-2*i<len(s):
                    result.append(s[j+size-2*i])
                j+=size
        return "".join(result)  

def zigzag_test(s):	
    solu = Solution()
    for i in range(len(s)):
        print '---------->',s,i+1
        print 'v1',solu.convert_v1(s,i+1) 
        print 'v2',solu.convert_v2(s,i+1)    
		
		
print zigzag_test('PAYPALISHIRING')	
solu = Solution()
print 'v1',solu.convert_v1('PAYPALISHIRING',4)	
print 'v2',solu.convert_v2('PAYPALISHIRING',4)	
    
    
    
    
    
    
    
    
    