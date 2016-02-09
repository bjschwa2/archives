import java.util.Random;

public class MonitorProblem2 {
  /** Number of times for each thread to loop. */
  static final public int LIMIT = 2000;

  /**
    * A thread with a function to let it wait periodically.  In
    * production, you wouldn't really want or need something like this
    * as part of a multi-threaded program.  Here it varies thread
    * execution timing so we see more of the possible execution orders
    * for our threads.  This can help give you confidence that your
    * solution is working correctly. 
    */

  static class PokyThread extends Thread {
    /** Source of randomness for sometimes waiting. */
    private Random rand = new Random();

    /** Make the caller wait between 0 and t milliseconds. */
    protected void hesitate( int t ) {
      try {
        Thread.sleep( rand.nextInt( t ) );
      } catch ( InterruptedException e ) {
      }
    }
  }

  /** Type for our monitor, to control the synchronization of our
      threads. */
  private static class MyMonitor {
    /** Shared value inside the monitor. */
    private int val = 0;

    private synchronized void print() throws InterruptedException {
      while (val % 2 != 0) {// is val odd
    	  wait();// wait while number is odd
      }
      System.out.println( val );

    }

    private synchronized void inc() {
      
      val++;
      if (val % 2 == 0) {// is val even
    	  notifyAll();// awaken threads
      }
    }
  }

  /** One instance of our monitor, for all our threads to use. */
  private static MyMonitor monitor = new MyMonitor();
  
  static class Chris extends PokyThread {
    public void run() {
      for ( int i = 0; i < LIMIT; i++ ) {

        hesitate( 10 );

        try {
			monitor.print();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

      }
    }
  }
  
  static class Meg extends PokyThread {
    public void run() {
      for ( int i = 0; i < LIMIT; i++ ) {

        hesitate( 10 );

        try {
			monitor.print();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

      }
    }
  }
  
  static class Stewie extends PokyThread {
    public void run() {
      for ( int i = 0; i < LIMIT; i++ ) {

        hesitate( 5 );

        monitor.inc();

        hesitate( 5 );

        monitor.inc();
      }
    }
  }
  
  public static void main( String[] args ) {
    // Make our threads.
    Thread t1 = new Chris();
    Thread t2 = new Meg();
    Thread t3 = new Stewie();

    // Start them running.
    t1.start();
    t2.start();
    t3.start();

    // Wait for them to finish.
    try {
      t1.join();
      t2.join();
      t3.join();
    } catch ( InterruptedException e ) {
    }
  }
}
