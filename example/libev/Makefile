LD_RUN_PATH=/usr/local/lib/
export LD_RUN_PATH
#gcc  -L/usr/local/lib gf_libev.c -lev
all:
	gcc -LLIBDIR libev_eg01.c -lev
all2: # for cygwin
	gcc  -L/usr/local/lib libev_eg01.c -lev	 	
gf: 
	gcc gf_libev.c -lev
gf2: 
	gcc  -L/usr/local/lib gf_libev.c -lev	
timer: 
	gcc  -L/usr/local/lib timer_libev_eg.c -lev
timer2: 
	gcc timer_libev_eg.c -lev	
