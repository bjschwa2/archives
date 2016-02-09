#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

int main() {
  // Make a pipe for talking with the child.
  int pfd[ 2 ];
  if ( pipe( pfd ) != 0 )
    fail( "Can't create pipe" );

  // make the child process
  pid_t pid = fork();
  if ( pid  < 0 )
    fail( "Not able to fork a child" );

  // If I'm the child, read two values from the user
  if ( pid == 0 ) {
    // Close the reading end of the pipe.  We don't need it.
    close( pfd[ 0 ] );
    
    // Read a string message from the user.
    char buffer[ 1024 ];
    printf( "Enter a String: " );
    fgets( buffer, sizeof( buffer ), stdin );

    // Send the message over the pipe.
    int pos = 0;
    int slen = strlen( buffer );

    // Push message into pipe, until it's all written.
    while ( pos < slen ) {
      int len = write( pfd[ 1 ], buffer + pos, slen - pos );
      if ( len < 0 )
        fail( "Can't write into pipe" );
      pos += slen;
    }

    close( pfd[ 1 ] );
    return 0;
  }

  if ( pid > 0 ) {
    // I'm the parent, I don't need the writing end of the pipe.
    close( pfd[ 1 ] );

    // Read bytes from the pipe until we hit the end of file.
    char buffer[ 1024 ];
    int len = read( pfd[ 0 ], buffer, sizeof( buffer ) );
    printf( "Message: " );
    while ( len > 0 ) {
      // Write (partial) message to standard output.
      fwrite( buffer, len, 1, stdout );

      // Get more bytes to print.
      len = read( pfd[ 0 ], buffer, sizeof( buffer ) );
    }

    if ( len < 0 )
      fail( "Error reading from pipe" );
  
    // Wait for our child to exit.
    wait( 0 );
  }
}
