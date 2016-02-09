import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Scanner;

/**
 * Hashing program, inserts keys from input file and allows user to find key at index
 * or find index that key resides.
 * @author Spencer Clem
 * @author Ryan Aznar
 * March 6th, 2014
 * CSC 316
 */
public class Hash {

	//global current index for order keys are inserted
	private static int index = 0;
	//define hash table
	private static final int M = 101;

	private Key[] hash_table = new Key[M];

	public static void main(String[] args) {
		System.out.println("Enter input file: ");
		Scanner scan = new Scanner(System.in);
		int L = 0;
		Scanner fscan = null;

		try {
			fscan = new Scanner(new File(scan.next()));
			L = fscan.nextInt();
		} catch (FileNotFoundException e) {
			System.out.println("File not found.");
			System.exit(1);
		}
		//create max value
		int[] max = new int[L];
		for (int i = 0; i < L; i++) {
			max[i] = fscan.nextInt();
		}
		fscan.nextLine();

		long totalTime = 0; //time taken to insert all keys, ignoring file I/O time
		Hash hash = new Hash();
		//read keys and input into data structure.		
		do 
		{
			int next = fscan.nextInt();
			if (next == -911) {
				break; //end of file.
			}
			else {
				int[] key = new int[L]; //individual line
				if (next > max[0]) {
					fscan.nextLine(); //invalid input
					continue;
				}
				key[0] = next; //save first value, not eof
				for (int i = 1; i < L; i++) {
					int current = fscan.nextInt();
					if (current > max[i]) {
						System.out.println("Invalid key, position " + i +  " > max values.");
						fscan.nextLine(); //invalid input
						continue;
					}
					key[i] = current; //input entire key
				}
				//input key into data structure here
				//generate index value from key itself
				long nowTime = System.nanoTime(); //get time
				int hashed = hash.hashfunction(key);
				
				//insert key at index created by hash function
				hash.insert(hashed, key);
				totalTime += System.nanoTime() - nowTime; //delta time to insert key from file
			}
		} while (true);
		//find out data usage in bytes.
		int bytes = 0;
		for (int i = 0; i < M; i++) {
			if (hash.hash_table[i] == null) continue;
			int numberOfKeyItems = hash.hash_table[i].overflow.size();
			int sizeOfKeyItems = numberOfKeyItems * (L + 1 + 1); //array size L, + 1 for index, + 1 for link to next element.
			sizeOfKeyItems *= 4; //integers have 4 bytes
			bytes += sizeOfKeyItems;
		}
		System.out.println("Total number of bytes used in data structure: " + bytes);
		System.out.println("Time taken to insert all keys: " + totalTime / 1000000 + "ms");
		fscan.close(); //done reading file
		//begin hashing
		while (true) {
			System.out.println("Input a key(k), an index(i), or (q) to quit: ");
			String in = scan.next();
			switch (in) {
			case "k":
				System.out.println("Input key of length " + L + ":");
				int[] key = new int[L];
				for (int i = 0; i < L; i++) {
					int next = scan.nextInt();
					if (next > max[i]) {
						System.out.println("Invalid key.");
						scan.nextLine();
						break;
					}
					key[i] = next;
				}
				int hashed = hash.hashfunction(key);
				int index = hashed % M;
				if (hash.hash_table[index] != null) {
					boolean found = false;	
					for (int i = 0; i < hash.hash_table[index].overflow.size(); i++) {
						if (Arrays.equals(hash.hash_table[index].overflow.get(i).key, key)) {
							System.out.println("Key found at index " + 
									hash.hash_table[index].overflow.get(i).index_inserted 
									+  "... Key value is: " + 
									toString(hash.hash_table[index].overflow.get(i).key));
							found = true;
							break;
						}
					}
					if (!found) System.out.println("Key not found.");
				}
				else System.out.println("Key not found.");
				break;
			case "i":
				System.out.println("Enter the index of a key: ");
				int index1 = scan.nextInt();
				if (index1 >= hash.index || index1 < 0) {
					System.out.println("Index invalid. No key exists.");
					break;
				}
				//search for index here.
				boolean found = false;
				for (int i = 0; i < M; i++) {
					if (found) break;
					if (hash.hash_table[i] == null) continue; //no keys were inserted at this index
					for (int j = 0; j < hash.hash_table[i].overflow.size(); j++) {
						if (hash.hash_table[i].overflow.get(j).index_inserted == index1) {
							System.out.println("Key #" + index1 + " inserted is: " + 
									toString(hash.hash_table[i].overflow.get(j).key));
							found = true;
							break;
						}
					}
				}
				if (!found) System.out.println("Key not found.");
				break;
			case "q":
				System.out.println("Quitting.");
				System.exit(0);
			}
		}
	}

	static String toString(int[] key) {
		String keys = "";
		for (int i = 0; i < key.length; i++) {
			keys += key[i] + " ";
		}
		return keys;
	}

	/**
	 * insert key via division hashing method. 
	 * key has been converted via hashfunction method to an integer previously
	 * @param hashvalue
	 * @param key
	 */
	void insert(int hashvalue, int[] key) {
		int index = hashvalue % this.M;
		if (this.hash_table[index] == null) {
			this.hash_table[index] = new Key();
		}
		this.hash_table[index].add(key);
	}

	/**
	 * need to develop a collision avoidance strategy and better hashing method
	 * @param key
	 * @return
	 */
	int hashfunction(int[] key) {
		int sum = 0;
		for (int i = 1; i <= key.length; i++) {
			sum += key[i - 1] * i; //multiply key value part times its individual index
		}
		return sum;
	}
	
	private static class Key {
		private LinkedList<KeyItem> overflow;

		public Key() {
			this.overflow = null;
		}

		/**
		 * collision avoidance handled by appending to linked list.
		 * @param key
		 */
		public void add(int[] key) {
			if (overflow == null) overflow = new LinkedList<KeyItem>();
			for (KeyItem k : overflow) {
				if (Arrays.equals(k.key, key)) {
					//ignore this key, it has already been inserted
					return;
				}
			}
			overflow.add(new KeyItem(key, index++));
		}

		private static class KeyItem {
			private int[] key;
			private int index_inserted;

			public KeyItem(int[] key, int order_inserted) {
				// TODO Auto-generated constructor stub
				this.key = key;
				this.index_inserted = order_inserted;
			}
		}
	}
}

