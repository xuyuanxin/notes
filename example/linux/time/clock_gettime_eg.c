//test9.c
#include <stdio.h>
#include <time.h>

/* 如果无法编译,默认没有加入该库,请用gcc test9.c -lrt运行 */
int clock_gettime_eg01()
{
	struct timespec time1 = {0, 0};
	clock_gettime(CLOCK_REALTIME, &time1);
	printf("CLOCK_REALTIME: %d, %d", time1.tv_sec, time1.tv_nsec);
	clock_gettime(CLOCK_MONOTONIC, &time1);
	printf("CLOCK_MONOTONIC: %d, %d", time1.tv_sec, time1.tv_nsec);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	printf("CLOCK_PROCESS_CPUTIME_ID: %d, %d", time1.tv_sec, time1.tv_nsec);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);
	printf("CLOCK_THREAD_CPUTIME_ID: %d, %d", time1.tv_sec, time1.tv_nsec);
	printf("\n%d\n", time(NULL));
	sleep(1);
}