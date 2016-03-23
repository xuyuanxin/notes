
public class Executors extends Object
{

/*-----------------------------------------------------------------------------------
 @returns: the newly created thread pool
 
 Creates a thread pool that creates new threads as needed, but will reuse  previously 
 constructed threads when they are available. These pools will typically improve  the 
 performance of programs that execute many short-lived asynchronous tasks. Calls to -
 execute will reuse previously constructed threads if available. If no existing thre-
 ad is available, a new thread will be created and added to the pool. Threads that h-
 ave not been used for sixty seconds are terminated and removed from the cache. Thus, 
 a pool that remains idle for long enough will not consume any resources. Note that -
 pools with similar properties but different details (for example, timeout parameter-
 s) may be created using ThreadPoolExecutor constructors.
 ----------------------------------------------------------------------------------*/
public static ExecutorService newCachedThreadPool();

/*-----------------------------------------------------------------------------------
 @threadFactory - the factory to use when creating new threads
 @returns:the newly created thread pool
 @Throws: NullPointerException - if threadFactory is null

 Creates a thread pool that creates new threads as needed, but will reuse  previously 
 constructed threads when they are available, and uses the provided ThreadFactory  to 
 create new threads when needed.
 ----------------------------------------------------------------------------------*/
public static ExecutorService newCachedThreadPool(ThreadFactory threadFactory);





/*-----------------------------------------------------------------------------------
 @nThreads - the number of threads in the pool
 @Returns:the newly created thread pool
 @Throws: IllegalArgumentException - if nThreads <= 0

 Creates a thread pool that reuses a fixed number of threads operating off a shared -
 unbounded queue. At any point, at most @nThreads threads will be active processing -
 tasks. If additional tasks are submitted when all threads are active, they will wait 
 in the queue until a thread is available. If any thread terminates due to a  failure 
 during execution prior to shutdown, a new one will take its place if needed to exec-
 ute subsequent tasks. The threads in the pool will exist until it is explicitly    -
 @shutdown.
 ----------------------------------------------------------------------------------*/
public static ExecutorService newFixedThreadPool(int nThreads);



}

