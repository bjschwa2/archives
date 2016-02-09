import java.io.*;
import java.util.Scanner;
import java.net.Socket;
import javax.crypto.Cipher;
import java.security.PublicKey;
import java.security.KeyFactory;
import java.security.spec.X509EncodedKeySpec;
import java.security.GeneralSecurityException;
import javax.xml.bind.DatatypeConverter;

/** Client supporting simple interaction with the server. */
public class Client {
  public static void main(String[] args) throws Exception {
    // Complain if we don't get the right number of arguments.
    if (args.length != 1) {
      System.out.println("Usage: Client <host>");
      System.exit(-1);
    }
    try {
      // Try to create a socket connection to the server.
      Socket sock = new Socket(args[0], Server.PORT_NUMBER);

      // Get formatted input/output streams for this thread.
      DataInputStream input = new DataInputStream(sock.getInputStream());
      DataOutputStream output = new DataOutputStream(
          sock.getOutputStream());
      // Get the key as a string of hex digits and turn it into a byte
      // array.
      Scanner keyScanner = new Scanner(new File("public.txt"));
      String hexKey = keyScanner.nextLine().trim();
      byte[] rawKey = DatatypeConverter.parseHexBinary(hexKey);

      // Make a key specification based on this key
      X509EncodedKeySpec pubKeySpec = new X509EncodedKeySpec(rawKey);

      // create a key
      KeyFactory keyFactory = KeyFactory.getInstance("RSA");
      PublicKey publicKey = keyFactory.generatePublic(pubKeySpec);

      // make a cypher and set to Decrypt mode
      Cipher cipher = Cipher.getInstance("RSA");
      cipher.init(Cipher.DECRYPT_MODE, publicKey);

      // Read commands from the user and print server responses.
      Scanner scanner = new Scanner(System.in);

      // get the user text prompt from the server
      String response = input.readUTF();

      // decrypt user text prompt and print
      byte[] rawReceive = DatatypeConverter.parseHexBinary(response);
      byte[] rawReceiveText = cipher.doFinal(rawReceive);
      System.out.print(new String(rawReceiveText));

      // get the username from console send to server
      String request = "";
      request = scanner.nextLine();
      output.writeUTF(request);

      // get the response from the server
      response = input.readUTF();

      // Decrypt the servers response and print it
      rawReceive = DatatypeConverter.parseHexBinary(response);
      rawReceiveText = cipher.doFinal(rawReceive);
      System.out.print(new String(rawReceiveText));

      // prompt for the first command
      System.out.print("cmd> ");
      while (scanner.hasNextLine()
          && !(request = scanner.nextLine()).equals("exit")) {

        //send request to server
        output.writeUTF(request);

        // get response
        response = input.readUTF();

        // Decrypt the servers response and print it
        rawReceive = DatatypeConverter.parseHexBinary(response);
        rawReceiveText = cipher.doFinal(rawReceive);
        System.out.print(new String(rawReceiveText));

        // Prompt for the next command.
        System.out.print("cmd> ");
      }

      // Send the done command to the server.
      output.writeUTF(request);
      output.flush();

      // We are done communicating with the server.
      sock.close();
    } catch (IOException e) {
      System.err.println("Error: server communication");
    }
  }
}
