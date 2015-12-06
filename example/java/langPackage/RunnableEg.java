
class DoSomething implements Runnable {
    private String name;

    public DoSomething(String name) {
        this.name = name;
    } 

    public void run() {
        for (int i = 0; i < 5; i++) {
            for (long k = 0; k < 100000000; k++) ;
            System.out.println(name + ": " + i);
        } 
    } 
}

public class RunnableEg {
    public static void main(String[] args) {
        DoSomething ds1 = new DoSomething("Thread1");
        DoSomething ds2 = new DoSomething("Thread2");

        Thread t1 = new Thread(ds1);
        Thread t2 = new Thread(ds2);

        t1.start(); 
        t2.start(); 
    } 
}

