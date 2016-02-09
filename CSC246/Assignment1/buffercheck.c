// Program to test out the buffer capacity of a pipe.

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

// Number of times to write messages into the pipe.  Really, one should
// be enough.
#define TRIALS 100

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

int main( int argc, char *argv[] ) {
  // Make sure we got a read/write size as a command-line argument.
  int n;
  if ( argc != 2 || sscanf( argv[ 1 ], "%d", &n ) != 1 )
    fail( "usage: bufferCheck <rea/write size>" );

  // Make a pipe for, just for measuring its buffer capacity.
  int pfd[ 2 ];
  if ( pipe( pfd ) != 0 )
    fail( "Can't create pipe" );

  // Make a byte array of the requested size.  We use this to write into
  // the pipe and to read from it.  For this test, we don't really care
  // what's in the array.
  char msg[ n ];
  
  // Now, try to write the message into one end of the pipe and then
  // read it back out the other end.  If the message is larger than the
  // pipe's buffer capacity, we will deadlock.
  for ( int i = 0; i < TRIALS; i++ ) {
    // Write into the writing end of the pipe.
    if ( write( pfd[ 1 ], msg, n ) != n ) {
      fail( "Can't write message into the pipe" );
    }

    // Now, read it back from the other end.
    if ( read( pfd[ 0 ], msg, n ) != n ) {
      fail( "Can't read message from the pipe" );
    }
  }

  // Clean up if we succeeded.
  close( pfd[ 0 ] );
  close( pfd[ 1 ] );
}
