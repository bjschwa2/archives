import java.util.Scanner;
import java.io.IOException;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.SocketTimeoutException;
import java.net.InetAddress;
 
/** Client program to request portions of files and to request
    permissions changes from the server. */
public class FileClient {
  /** Port number at which the client receives packets.  Has to be different
      from the server's port, in case we run on the same host. */
  public static final int CLIENT_PORT = 26055;
   
  /** Time to wait until the program gets bad output */
  public static final int WAIT = 2;
   
  /** Starts the client taking in 2 or 4 arguments to get the whole
    list back or just a single line from a file. */
  public static void main( String[] args ) {
    // Make sure the command-line arguments are good.
    if ( ! ( args.length == 2 && args[ 1 ].equals( "list" ) ) &&
         ! ( args.length == 4 && args[ 1 ].equals( "get" ) ) ) {
      System.err.println( "usage: FileClient <server_host> <list>" );
      System.err.println( "usage:            <server_host> <get> <file> <line>" );
      System.exit( 0 );
    }
    // The recieve buffer
    byte[] rBuffer = new byte [ 1024 ]; 
    // The packet
    DatagramPacket rPacket = new DatagramPacket( rBuffer, rBuffer.length); 
    // String being sent and recived
    String s = null;
    // If the request is for a list
    if ( args.length == 2){ 
        // set s to list
        s = "list"; 
        // If the request is for a line
    } else if ( args.length == 4 ){ 
        s = ""; // reset s
        // set s to the arguments
        s = args[1] + " " + args[2] + " " + args[3]; 
    } else {
      // not enough arguments
        System.err.println("Error, too few arguments"); 
    }
    // Try to send the datagram through the socket and get a response
    try{
        DatagramSocket newSock = new DatagramSocket( CLIENT_PORT );
        newSock.setSoTimeout(WAIT);
        try {
            // Make address list
            InetAddress[] aList = InetAddress.getAllByName( args[ 0 ] ); 
            // Turn string to bytes
            byte[] newBuffer = s.getBytes(); 
            // make send packet
            DatagramPacket sPacket = new DatagramPacket( newBuffer, newBuffer.length,
                    aList[ 0 ],
                    // Package the byte string
                    FileServer.SERVER_PORT ); 
            // send data to the server
            newSock.send(sPacket); 
            // Get response
            newSock.receive(rPacket); 
            // make a response
            String rCall = new String( rBuffer, 0, rPacket.getLength() );
            // Print the response
            System.out.println(rCall); 
            // check for timeout
        } catch (SocketTimeoutException e){ 
            System.out.println("No Response.");
        }
    // check error in the communication
    } catch ( IOException e ){ 
        System.err.println("Error in communicationg with the server" + e);
    }
  }
}