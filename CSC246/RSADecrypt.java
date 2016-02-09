import java.io.File;
import java.util.Scanner;
import javax.crypto.Cipher;
import java.security.PrivateKey;
import java.security.KeyFactory;
import java.security.spec.PKCS8EncodedKeySpec;

import javax.xml.bind.DatatypeConverter;

/** Given an RSA public key stored in the file, public.txt, read a
    message from the user and encrypt it with the key.  Write the
    encrypted message as a string of hexadecimal. */
public class RSADecrypt {
  public static void main(String[] args) throws Exception {
    // Read in the key and get it as a byte array.
    Scanner keyScanner = new Scanner( new File( "private.txt" ) );
    String hexKey = keyScanner.nextLine();
    byte[] rawKey = DatatypeConverter.parseHexBinary( hexKey );
    
    // Make a key specification based on this key.
    PKCS8EncodedKeySpec privKeySpec = new PKCS8EncodedKeySpec( rawKey );

    // Get an RSA key based on this specification
    KeyFactory keyFactory = KeyFactory.getInstance( "RSA" );
    PrivateKey privateKey = keyFactory.generatePrivate( privKeySpec );

    // Make a cipher object that will decrypt using this key.
    Cipher cipher = Cipher.getInstance( "RSA" );
    cipher.init( Cipher.DECRYPT_MODE, privateKey );
    
    // Prompt for a string of hexadecimal to decrypt.
    Scanner scanner = new Scanner( System.in );
    System.out.print( "Hex string to decrypt: " );
    String msg = scanner.nextLine();

    // Convert the message to an array of bytes and decrypt it.
    byte[] rawMsg = DatatypeConverter.parseHexBinary( msg );
    byte[] rawPlaintext = cipher.doFinal( rawMsg );

    // Print out the decrypted messaage as a string.
    System.out.println( new String( rawPlaintext ) );
  }
}
