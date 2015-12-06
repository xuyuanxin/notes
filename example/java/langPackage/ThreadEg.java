

public class ThreadEg extends Thread{ 
    public ThreadEg(String name) {
        super(name);
    } 

    public void run() {
        for(int i = 0;i<5;i++){
            for(long k= 0; k <100000000;k++);
            System.out.println(this.getName()+" :"+i);
        } 
    } 

    public static void main(String[] args) {
        Thread t1 = new ThreadEg("Thread1");
        Thread t2 = new ThreadEg("Thread2");
        t1.start(); 
        t2.start(); 
    } 
}

