import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.ArrayList;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
 
/** Server for for maintaining ownership and read permissions for a
    collection of pretend files. */
public class FileServer {
     
  /** Port number used by the server.  */
  public static final int SERVER_PORT = 26054;
   
  /** Record for an individual file. */
  static class FileRec {
    // Name of the file.
    String name;
 
    // List of lines in the file's contents.
    ArrayList< String > contents = new ArrayList< String >();
  }
 
  // List of all files, each with file contents.
  private ArrayList< FileRec > fileList = new ArrayList< FileRec >();
 
  /** Read all the file information from a file named files.txt and
      store them in fileList. */
  private void readFiles() throws IOException {
    Scanner input = new Scanner( new File( "files.txt" ) );
    while ( input.hasNext() ) {
      // Make a new file record and populate it.
      FileRec f = new FileRec();
      f.name = input.next();
 
      // Then, read the file's contents.
      int lines = input.nextInt();
      input.nextLine(); // Eat the rest of this line.
      for ( int i = 0; i < lines; i++ ) {
        String line = input.nextLine();
        f.contents.add( line );
      }
 
      // Add this file record to the end of the list.
      fileList.add( f );
    }
  }
 
  // Repeatedly read requests over UDP and send back responses.
  public void serveRequests() throws IOException {
    DatagramSocket newSock = null; //initialize a socket
    try {// Create a new socket
        newSock = new DatagramSocket( SERVER_PORT );
      } catch( IOException e ){
        System.err.println( "Can't create socket: " + e );
        System.exit( -1 );
      }
    byte[] rBuffer = new byte [1024];// Create a buffer to receive
    DatagramPacket rPacket = new DatagramPacket( rBuffer, rBuffer.length );
    try{
        while( true ){
            // Get a packet
            newSock.receive( rPacket );
            // make new string buffer
            String strBuffer = new String( rBuffer, 0, rPacket.getLength() );
            // Split it into an array
            String split[] = strBuffer.split(" ", 3);
            try {
                if( split[0].equals("list") ){
                    // make buffer a space
                    strBuffer = ""; 
                    // Retrieve all items
                    for(int i = 0; i < fileList.size(); i++){
                        // new space string
                        String sp = "";
                        // fix spacing
                        for (int j = 0 ; j < 16-fileList.get(i).name.length() ; j++){
                            sp += " "; 
                        }
                        // Add the name, space, lines
                        strBuffer += fileList.get(i).name + sp + fileList.get(i).contents.size(); 
                        if( i+1 < fileList.size() ){
                            strBuffer += "\n"; // next line
                        }
                    }
                // If it asked for a line
                } else if ( split[0].equals("get")){
                    // make strBuffer a space
                    strBuffer = "";
                    // number of lines
                    int numLine = Integer.parseInt(split[2]);
                    // not in the list
                    Boolean inList = false;
                    int i = 0;
                    // check for it in the list
                    for(i = 0; i < fileList.size(); i++ ){
                        if(fileList.get(i).name.equals(split[1])){
                            // found in the list
                            inList = true;
                            break;
                        }
                    }
                    // file was in the list and lines were valid
                    if((inList == true) && (fileList.get(i).contents.size() >= numLine)){
                        // Add to the strBuffer
                        strBuffer += fileList.get(i).contents.get(numLine); 
                    // sleep for 2 seconds
                    } else { 
                        try {
                            // sleep for 2 seconds
                            Thread.sleep(2000); 
                        } catch(InterruptedException ex) {
                            Thread.currentThread().interrupt();
                        }
                    }
                // If bad input
                } else {
                    throw new Exception();
                }
            } catch ( Exception e ) {
                System.err.println("Bad Request.");
            }
            // Convert the string to a byte buffer
            byte[] sBuffer = strBuffer.getBytes(); 
            DatagramPacket sPacket = new DatagramPacket( sBuffer, sBuffer.length, rPacket.getAddress(), rPacket.getPort());
            // Send response
            newSock.send( sPacket ); 
        }
    // check for error
    } catch ( IOException e){
        System.err.println("Error can not communicate with client.");
    }
  }

  /** Starts the server. */
  public static void main( String[] args ) {
    FileServer server = new FileServer();
    try {
      server.readFiles();
      server.serveRequests();
    } catch ( IOException e ) {
    }
  }
}