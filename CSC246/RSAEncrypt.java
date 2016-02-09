import java.io.File;
import java.util.Scanner;

import javax.crypto.Cipher;
import java.security.PublicKey;
import java.security.KeyFactory;
import java.security.spec.X509EncodedKeySpec;

import javax.xml.bind.DatatypeConverter;

/** Given an RSA public key stored in the file, public.txt, read a
    message from the user and encrypt it with the key.  Write the
    encrypted message as a string of hexadecimal. */
public class RSAEncrypt {
  public static void main(String[] args) throws Exception {
    // Read in the key and get it as a byte array.
    Scanner keyScanner = new Scanner( new File( "public.txt" ) );
    String hexKey = keyScanner.nextLine();
    byte[] rawKey = DatatypeConverter.parseHexBinary( hexKey );
    
    // Make a key specification based on this key.
    X509EncodedKeySpec pubKeySpec = new X509EncodedKeySpec( rawKey );

    // Get an RSA key based on this specification
    KeyFactory keyFactory = KeyFactory.getInstance( "RSA" );
    PublicKey publicKey = keyFactory.generatePublic( pubKeySpec );

    // Make a cipher object that will encrypt using this key.
    Cipher cipher = Cipher.getInstance( "RSA" );
    cipher.init( Cipher.ENCRYPT_MODE, publicKey );
    
    // Prompt for a plaintext string to enrypt.
    Scanner scanner = new Scanner( System.in );
    System.out.print( "String to encrypt: " );
    String msg = scanner.nextLine();

    // Convert the message to an array of bytes and encrypt it.
    byte[] rawMsg = msg.getBytes();
    byte[] rawCiphertext = cipher.doFinal( rawMsg );

    // Print out the encrypted messaage in hex.
    System.out.println( DatatypeConverter.printHexBinary( rawCiphertext ) );
  }
}
