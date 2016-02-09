import java.util.Random;
import java.util.concurrent.Semaphore;

public class SemProblem2 {
	/** Number of times for each thread to loop. */
	static final public int LIMIT = 2000;
	private static Semaphore sem = new Semaphore(2);

	/**
	 * A thread with a function to let it wait periodically. In production, you
	 * wouldn't really want or need something like this as part of a
	 * multi-threaded program. Here it varies thread execution timing so we see
	 * more of the possible execution orders for our threads. This can help give
	 * you confidence that your solution is working correctly.
	 */
	static class PokyThread extends Thread {
		/** Source of randomness for sometimes waiting. */
		private Random rand = new Random();

		/** Make the caller wait between 0 and t milliseconds. */
		protected void hesitate(int t) {
			try {
				Thread.sleep(rand.nextInt(t));
			} catch (InterruptedException e) {
			}
		}
	}

	/** Value shared by all our threads. */
	static private int val = 0;

	static class Philip extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {
				sem.acquireUninterruptibly(2);// acquire 2 permits for sem
											

				hesitate(10);

				System.out.println(val);
				sem.release(2);// release 2 permits sem 
			}
		}
	}

	static class Leela extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {
				sem.acquireUninterruptibly(2);// acquire 2 permits for sem
												
				hesitate(10);

				System.out.println(val);
				sem.release(2);// release 2 permits for sem 
			}
		}
	}

	static class Bender extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {

				hesitate(5);
				sem.acquireUninterruptibly(2);// acquire 2 permits for sem
									
				val++;

				hesitate(5);

				val++;
				sem.release(2);// release 2 permits for sem 
			}
		}
	}

	public static void main(String[] args) {
		// Make our threads.
		Thread t1 = new Philip();
		Thread t2 = new Leela();
		Thread t3 = new Bender();

		// Start them running.
		t1.start();
		t2.start();
		t3.start();

		// Wait for them to finish.
		try {
			t1.join();
			t2.join();
			t3.join();
		} catch (InterruptedException e) {
		}
	}
}
