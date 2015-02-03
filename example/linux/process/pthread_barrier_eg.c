#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

#define NTHR 8/*number of threads */
#define NUMNUM 8000000L /* number of numbers to sort */
#define TNUM (NUMNUM/NTHR) /* number to sort per thread */
long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

#ifdef SOLARIS
#define heapsort qsort
#else
extern int heapsort(void *, size_t, size_t,int (*)(const void *, const void *));
#endif

/*
 Compare two long integers (helper function for heapsort)
*/
int complong(const void *arg1, const void *arg2)
{
	long l1 = *(long *)arg1;
	long l2 = *(long *)arg2;
	if (l1 == l2)
	    return 0;
	else if (l1 < l2)
	    return -1;
	else
	    return 1;
}

/*
 Worker thread to sort a portion of the set of numbers.
*/
void *thr_fn(void *arg)
{
	long idx =(long)arg;
	heapsort(&nums[idx], TNUM, sizeof(long), complong);
	pthread_barrier_wait(&b);
	return((void *)0);
}

/*
 Merge the results of the individual sorted ranges.
*/
void merge()
{
	long idx[NTHR];
	long i, minidx, sidx, num;
	for (i = 0; i < NTHR; i++)
	    idx[i] = i * TNUM;
	for (sidx = 0; sidx < NUMNUM; sidx++) {
	    num = LONG_MAX;
	    for (i = 0; i < NTHR; i++) {
	        if ((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num)) {
	            num = nums[idx[i]];
	            minidx = i;
	        }
	    }
	    snums[sidx] = nums[idx[minidx]];
	    idx[minidx]++;
	}
}

/*-----------------------------------------------------------------------------------
 This example shows the use of a barrier in  a simplified situation where the threads
 perform only one task.In more realistic situations, the worker threads will continue
 with other activities after the call to @pthread_barrier_wait returns.

 In the example, we use eight threads to divide the job of sorting 8 million numbers.
 Each thread sorts 1 million numbers using the heapsort algorithm. Then the main thr-
 ead calls a function to merge the results.

 We don't need to use the PTHREAD_BARRIER_SERIAL_THREAD return value from
 @pthread_barrier_wait to decide which thread merges the results , because we use the 
 main thread for this task. That is why we specify the barrier count as one more than
 the number of worker threads; the main thread counts as one waiter.

 If we write a program to sort 8 million numbers with heapsort using 1 thread only, 
 On a system with 8 cores, the single-threaded program sorted 8 million numbers in 12.14 
 seconds. On the same system, using 8 threads in parallel and 1 thread to merge the 
 results,the same set of 8 million numbers was sorted in 1.91 seconds,6 times faster.
-----------------------------------------------------------------------------------*/
int main()
{
	unsigned long i;
	struct timeval start, end;
	long long startusec, endusec;
	double	elapsed;
	int  err;
	pthread_t tid;

	srandom(1);
	for (i = 0; i < NUMNUM; i++)
	    nums[i] = random();	
	gettimeofday(&start, NULL);
	pthread_barrier_init(&b, NULL, NTHR+1); /* Create 8 threads to sort the numbers. */
	for (i = 0; i < NTHR; i++) {
	    err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
	    if (err != 0)
	        printf("can't create thread :%d",err);
	}
	pthread_barrier_wait(&b);
	merge();
	gettimeofday(&end, NULL);
	startusec = start.tv_sec * 1000000 + start.tv_usec;
	endusec = end.tv_sec * 1000000 + end.tv_usec;
	elapsed = (double)(endusec - startusec) / 1000000.0;
	printf("sort took %.4f seconds\n", elapsed);
	for (i = 0; i < NUMNUM; i++)
	    printf("%ld\n", snums[i]);
	exit(0);
}


