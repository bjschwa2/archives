import java.awt.List;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Pairs.java is a program that mimics the implementation
 * of pairs.c except that it is written in java and it utilizes
 * threads.
 * 
 * @author Bradley Schwarz
 */

public class Pairs {

	private static int numWork;
	private static int numCount;
	static ArrayList <Integer> myList;
	private static int total = 0;

	static class MyThread extends Thread {

		/** Unique parameter passed to this thread. */
    private int inValue;

    /** Value computed by this thread. */
    private int result;
    
    /** Make a new MyRunnable, giving it a value to keep. */
    public MyThread( int v ) {
      inValue = v;
    }

    //gcd calculator
    public static int gcd(int a, int b){
    	while ( b != 0 ) {
    		int c = a % b;
    		a = b;
    		b = c;
    	}
    	return a;
  	}

    /** What this thread does when it's run. */
    public void run() {
  		// Check pairs of different numbers.
  	
      for ( int j = inValue; j < numCount; j+=numWork )
        for ( int k = j + 1; k < numCount; k++ )
          if ( gcd( myList.get(j), myList.get(k) ) == 1 )
            result++;

    // add result to total
    total+= result;
    }
	}

	public static void main( String[] args )  throws InterruptedException {

    // gets the file
		File file = new File(args[0]);
		try{
			Scanner fileScan = new Scanner(file);
			numCount = 0;
			myList = new ArrayList<Integer>();
			while (fileScan.hasNextInt()){
				myList.add(fileScan.nextInt());
        // counts integars
				numCount++;
			}
      // closes
			fileScan.close();
		}
		catch(FileNotFoundException e){
			System.out.println("File not found");
		}

    // gives the work to the threads
		numWork = Integer.parseInt(args[1]);
		MyThread[] thread = new MyThread[numWork];
		for(int i= 0; i<numWork ; i++){
			thread[i] = new MyThread( i );
    	thread[i].start();
  	}
    // threads join
  	for(int w = 0; w< numWork; w++){
      thread[w].join();
    }
    // print out the total
    System.out.println("Total: " + total);
	}
}
