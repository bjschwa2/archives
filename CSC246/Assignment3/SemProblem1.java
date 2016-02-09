import java.util.Random;
import java.util.concurrent.Semaphore;

public class SemProblem1 {
	/** Number of times for each thread to loop. */
	static final public int LIMIT = 2000;
	private static int count = 0;// the number of letters printed per line

	// create semaphores
	private static Semaphore allowA = new Semaphore(1);
	private static Semaphore allowB = new Semaphore(1);
	private static Semaphore allowC = new Semaphore(1);
	private static Semaphore allowNew = new Semaphore(0);

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

	static class Fred extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {
				allowA.acquireUninterruptibly();// acquire the allowA semaphore
				hesitate(10);

				System.out.print("a");
				count++;// increment count
				if (count == 3)// can we print out a new line
					allowNew.release();// release the newline semaphore

			}
		}
	}

	static class Wilma extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {
				allowB.acquireUninterruptibly();// take control of the allowB semaphore
				hesitate(10);

				System.out.print("b");
				count++;// increment line print count
				if (count == 3)// can we print out a new line
					allowNew.release();// release the newline semaphore

			}
		}
	}

	static class Pebbles extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {
				allowC.acquireUninterruptibly();
				hesitate(5);
				
				System.out.print("c");
				count++;// increment the character count line variable
				if (count == 3)// can we print a newline
					allowNew.release();// release the newline semaphore
				hesitate(5);
				allowNew.acquireUninterruptibly();// take control of the newline
													// semaphore

				System.out.print("\n");
				allowA.release();// release the allowA semaphore
				allowB.release();// release the allowB semaphore
				allowC.release();// release the allowC semaphore
				count = 0;// reset count to 0

			}
		}
	}

	public static void main(String[] args) {
		// Make our threads.
		Thread t1 = new Fred();
		Thread t2 = new Wilma();
		Thread t3 = new Pebbles();

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
