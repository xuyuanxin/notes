
/* V - The result type returned by this Future's get method */
public interface Future<V>
{

/*-----------------------------------------------------------------------------------
 Waits if necessary for the computation to complete, and then retrieves its result.
 Returns:the computed result
 Throws:
 CancellationException - if the computation was cancelled
 ExecutionException - if the computation threw an exception
 InterruptedException - if the current thread was interrupted while waiting
-----------------------------------------------------------------------------------*/
V get() throws InterruptedException,ExecutionException;

/*----------------------------------------------------------------------------------- 
 @timeout - the maximum time to wait
 @unit - the time unit of the timeout argument
 @Returns:the computed result
 @Throws:
 CancellationException - if the computation was cancelled
 ExecutionException - if the computation threw an exception
 InterruptedException - if the current thread was interrupted while waiting
 TimeoutException - if the wait timed out

 Waits if necessary for at most the given time for the computation to complete, and -
 then retrieves its result, if available.
 ----------------------------------------------------------------------------------*/
V get(long timeout,TimeUnit unit)
throws InterruptedException,ExecutionException,TimeoutException;


}


/*---------------------------------------------------------------------------------*/
package com.itbuluoge.mythread;

import java.util.ArrayList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

class TaskWithResult implements Callable<String>
{

  public String call() throws Exception {
    // TODO Auto-generated method stub
    Thread.sleep(1000);
    return "OK";
  }
  
}
public class CallableDemo {

  /**
   * @param args
   * @throws Exception 
   * @throws InterruptedException 
   */
  public static void main(String[] args) throws InterruptedException, Exception {
    // TODO Auto-generated method stub
    ExecutorService exec=Executors.newCachedThreadPool();
    Future<String> st=exec.submit(new TaskWithResult());
    
    /*同步结果，并且设置超时时间*/
    System.out.println(st.get(10000, TimeUnit.MILLISECONDS));
    System.out.println("over");
    
    
  }

}

