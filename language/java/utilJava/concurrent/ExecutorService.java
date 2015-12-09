

public interface ExecutorService extends Executor
{




/*-----------------------------------------------------------------------------------
 @timeout - the maximum time to wait
 @unit - the time unit of the timeout argument
 @Returns:true if this executor terminated and false if the timeout elapsed before t-
     ermination
 @Throws: InterruptedException - if interrupted while waiting
 
 Blocks until all tasks have completed execution after a shutdown request, or the ti-
 meout occurs, or the current thread is interrupted, whichever happens first.
 ----------------------------------------------------------------------------------*/
boolean awaitTermination(long timeout,TimeUnit unit); throws InterruptedException

/*-----------------------------------------------------------------------------------
 @Throws:SecurityException 
 
 Initiates an orderly shutdown in which previously submitted tasks are executed,  but 
 no new tasks will be accepted. Invocation has no additional effect if already shut -
 down. This method does not wait for previously submitted tasks to complete executio-
 n. Use @awaitTermination to do that.
 ----------------------------------------------------------------------------------*/
void shutdown();

/*-----------------------------------------------------------------------------------
 @task - the task to submit
 @Returns:a Future representing pending completion of the task
 @Throws:
     RejectedExecutionException - if the task cannot be scheduled for execution
     NullPointerException - if the task is null
     
 Submits a Runnable task for execution and returns a Future representing that task. -
 The Future's get method will return null upon successful completion.
 ----------------------------------------------------------------------------------*/
Future<?> submit(Runnable task);



}

