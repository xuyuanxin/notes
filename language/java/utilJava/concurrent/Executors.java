
public class Executors extends Object
{



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

