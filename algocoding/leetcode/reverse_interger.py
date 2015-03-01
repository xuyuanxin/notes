#coding=utf-8
def reverse(self, x):
    if x==0:
        return x
    string=str(x)
    if string[0]=='-':
        rever=string[-1:0:-1]
        self=int('-'+rever)
        if(self<-0x80000000):
            return 0
        else:
            return self
    else:
        rever=string[-1::-1]
        self=int(rever)		
        if(self>0x7fffffff):
            return 0
        else:
            return self

def reverse_interger_test(x):
    result=reverse(0,x)
    print x,'->',result

reverse_interger_test(123);	
reverse_interger_test(1534236469);
reverse_interger_test(-1563847412);
