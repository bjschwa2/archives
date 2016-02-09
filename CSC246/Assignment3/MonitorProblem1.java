import java.util.Random;

public class MonitorProblem1 {
	/** Number of times for each thread to loop. */
	static final public int LIMIT = 2000;

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

	/**
	 * Type for our monitor, to control the synchronization of our threads.
	 */
	private static class MyMonitor {
		int count = 0;
		Boolean allowA = false;
		Boolean allowB = false;
		Boolean allowC = false;

		private synchronized void printA() throws InterruptedException {
			while (allowA) {// wait while an A has already been printed
				wait();
			}
			System.out.print("a");
			allowA = true;// set allowA to true
			count++;// increment count
			if (count == 3) {// if 3 letters have been printed out, awaken all
								// threads
				notifyAll();
			}
		}

		private synchronized void printB() throws InterruptedException {
			while (allowB) {
				wait();// wait while a B as already been printed
			}
			System.out.print("b");
			allowB = true;// set allowB to true
			count++;// increment count
			if (count == 3) {
				notifyAll();// if 3 letters have been printed, awaken all
							// threads
			}
		}

		private synchronized void printC() throws InterruptedException {
			while (allowC) {
				wait();// wait while a C has already been printed
			}
			System.out.print("c");
			allowC = true;// set allowC to true
			count++;// increment count
			if (count == 3) {
				notifyAll();// if 3 letters have been printed, awaken all
							// threads
			}

		}

		private synchronized void printNewline() throws InterruptedException {
			while (!allowA || !allowB || !allowC) {
				wait();// if any letter hasn't been printed, wait
			}
			System.out.print("\n");
			allowA = false;//set allowA to false
			allowB = false;//set allowB to false
			allowC = false;//set allowC to false
			count = 0;//reset count
			notifyAll();//awaken all threads

		}
	}

	/** One instance of our monitor, for all our threads to use. */
	private static MyMonitor monitor = new MyMonitor();

	static class Ben extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {

				hesitate(10);

				try {
					monitor.printA();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		}
	}

	static class Johnny extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {

				hesitate(10);

				try {
					monitor.printB();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		}
	}

	static class Susan extends PokyThread {
		public void run() {
			for (int i = 0; i < LIMIT; i++) {

				hesitate(5);

				try {
					monitor.printC();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				hesitate(5);

				try {
					monitor.printNewline();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

	public static void main(String[] args) {
		// Make our threads.
		Thread t1 = new Ben();
		Thread t2 = new Johnny();
		Thread t3 = new Susan();

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
