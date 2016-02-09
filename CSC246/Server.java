import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.Random;
import java.util.ArrayList;
import javax.crypto.Cipher;
import java.security.PrivateKey;
import java.security.KeyFactory;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.GeneralSecurityException;
import javax.xml.bind.DatatypeConverter;

/**
 * Bradley Schwarz
 *
 * A server that keeps up with a public key for every user, along with a map
 * location for every user.
 */

public class Server {
  Object lock = new Object();

  // the number 19
  public static int NINETEEN = 19;

  // the number 9
  public static int NINE = 9;

  public class handleClient implements Runnable {

    // new socket
    Socket sock = null;

    // A new User
    UserRec user;

    public handleClient(Socket sock) {
      this.sock = sock;
    }

    public void run() {
      try {
        // Get formatted input/output streams for this thread.
        DataOutputStream output = new DataOutputStream(
            sock.getOutputStream());
        DataInputStream input = new DataInputStream(
            sock.getInputStream());

        // encryption setup
        Scanner keyScanner = new Scanner(new File("private.txt"));
        String hexKey = keyScanner.nextLine();
        byte[] rawKey = DatatypeConverter.parseHexBinary(hexKey);

        // create private keys
        PKCS8EncodedKeySpec privKeySpec = new PKCS8EncodedKeySpec(rawKey);
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");
        PrivateKey privateKey = keyFactory.generatePrivate(privKeySpec);

        // get cipher instance and set to Encrypt mode
        Cipher cipher = Cipher.getInstance("RSA");
        cipher.init(Cipher.ENCRYPT_MODE, privateKey);

        // encrypt the string "user: " and write
        String send = "user: ";
        byte[] rawSend = send.getBytes();
        byte[] rawCiphertext = cipher.doFinal(rawSend);
        output.writeUTF(DatatypeConverter.printHexBinary(rawCiphertext));

        // get the user and check if valid
        String receive = input.readUTF();
        boolean valid = false;
        for (int i = 0; i < userList.size(); i++) {

          // find users name on list
          if (receive.equals(userList.get(i).name)) {
            this.user = userList.get(i);
            valid = true;
            send = "OK\n";

            //send Ok if valid user
            rawSend = send.getBytes();
            rawCiphertext = cipher.doFinal(rawSend);
            output.writeUTF(DatatypeConverter.printHexBinary(rawCiphertext));
            break;
          }
        }

        // close if not valid user
        if (!valid) {
          sock.close();
        }

        // Get the first client command.
        String request = input.readUTF();

        // while the user doesn't exit.
        while (!request.equals("exit")) {
          String response = "Ok\n";

          // Check if command is up move up if not blocked
          if (request.equals("up")) {
            synchronized (lock) {
              if (user.row - 1 < 0) {
                response = "blocked\n";
              } else {

                // checks for period
                if (map[user.row - 1][user.col] == '.') {
                  map[user.row - 1][user.col] = user.name.charAt(0);
                  map[user.row][user.col] = '.';
                  user.row--;
                } else {
                  response = "blocked\n";
                }
              }
            }

          // Check if command is down move down if not blocked
          } else if (request.equals("down")) {
            synchronized (lock) {
              if (user.row + 1 > NINE) {
                response = "blocked\n";
              } else {

                // checks for period
                if (map[user.row + 1][user.col] == '.') {
                  map[user.row + 1][user.col] = user.name.charAt(0);
                  map[user.row][user.col] = '.';
                  user.row++;
                } else {
                  response = "blocked\n";
                }
              }
            }

          // Check if command is left move left if not blocked
          } else if (request.equals("left")) {
            synchronized (lock) {
              if (user.col - 1 < 0) {
                response = "blocked\n";
              } else {

                // checks for period
                if (map[user.row][user.col - 1] == '.') {
                  map[user.row][user.col - 1] = user.name.charAt(0);
                  map[user.row][user.col] = '.';
                  user.col--;
                } else {
                  response = "blocked\n";
                }
              }
            }

          // Check if command is right move right if not blocked
          } else if (request.equals("right")) {
            synchronized (lock) {
              if (user.col + 1 > NINETEEN) {
                response = "blocked\n";
              } else {

                // checks for period
                if (map[user.row][user.col + 1] == '.') {
                  map[user.row][user.col + 1] = user.name.charAt(0);
                  map[user.row][user.col] = '.';
                  user.col++;
                } else {
                  response = "blocked\n";
                }
              }
            }

          // if command is map print the map
          } else if (request.equals("map")) {
            response = "";
            for (int i = 0; i < map.length; i++) {
              for (int j = 0; j < map[0].length; j++) {
                response += map[i][j];
              }

              // responds with a next line
              response += "\n";
            }

          // user sent an unknown command
          } else {
            response = "invalid command\n";
          }

          // send response though cipher
          rawSend = response.getBytes();
          rawCiphertext = cipher.doFinal(rawSend);
          output.writeUTF(DatatypeConverter.printHexBinary(rawCiphertext));

          // Get the next command.
          request = input.readUTF();
        }

        // We are done communicating with this client.
        sock.close();
      } catch (Exception e) {
        // print error if cant communicate 
        System.out.println("Error");
      }
    }
  }

  /** Port number used by the server */
  public static final int PORT_NUMBER = 26054;

  /** Record for an individual user. */
  private static class UserRec {
    // Name of this user.
    String name;

    // This user's location on the map.
    int row = -1;
    int col = -1;
  }

  /** Map, an array of characters, with a letter for each user. */
  private char map[][];

  /** List of all the users, whether or not they are logged in. */
  private ArrayList<UserRec> userList = new ArrayList<UserRec>();

  /** Read the map at start-up. */
  private void readMap() throws Exception {
    Scanner input = new Scanner(new File("map.txt"));

    // Read in the map.
    int height = input.nextInt();
    int width = input.nextInt();

    map = new char[height][];
    for (int i = 0; i < height; i++)
      map[i] = input.next().toCharArray();

    // Read in all the users.
    int userCount = input.nextInt();

    for (int k = 0; k < userCount; k++) {
      // Create a record for the next user.
      UserRec rec = new UserRec();
      rec.name = input.next();

      // Make sure this user has a unique initial.
      for (int i = 0; i < userList.size(); i++)
        if (rec.name.charAt(0) == userList.get(i).name.charAt(0))
          throw new Exception("Duplicate user initials");

      // Find this user on the map.
      for (int i = 0; i < map.length; i++)
        for (int j = 0; j < map[i].length; j++)
          if (map[i][j] == rec.name.charAt(0)) {
            rec.row = i;
            rec.col = j;
          }

      if (rec.row < 0)
        throw new Exception("User is not on the map");

      // Add this user to the list of all users.
      userList.add(rec);
    }
  }

  /** Handle interaction with a single client. */
  private void handleClient(Socket sock) {

  }

  /** Esentially, the main method for our server. */
  private void run(String[] args) {
    ServerSocket serverSocket = null;

    // One-time setup.
    try {
      // Read the map and the list of users.
      readMap();

      // Open a socket for listening.
      serverSocket = new ServerSocket(PORT_NUMBER);
    } catch (Exception e) {
      System.err.println("Can't initialize server: " + e);
      System.exit(-1);
    }

    // Keep trying to accept new connections and serve them.
    while (true) {
      try {
        // Try to get a new client connection.
        Socket sock = serverSocket.accept();
        Thread worker = new Thread(new handleClient(sock));
        worker.start();
        // Interact with this client.
      } catch (IOException e) {
        System.err.println("Failure accepting client " + e);
      }
    }
  }

  public static void main(String[] args) {
    // Make a server object, so we can have non-static fields.
    Server server = new Server();
    server.run(args);
  }
}
