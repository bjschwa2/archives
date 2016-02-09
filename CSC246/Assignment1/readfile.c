// Example program using the open(), read(), close() system call interface
// to read from a text file.

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

int main(int argc, char *argv[]) {

  int lines = 0;

  for(int i=0; i< *argv[3]; i++){

    lines = 0;

    // Open a file for reading.
    int fd = open( argv[1], O_RDONLY );
    if ( fd < 0 )
      fail( "Can't open example.txt for reading" );


    // Read the file in 10-byte gulps.
    int len;
    char buffer[ *argv[2]];
    while ( ( len = read( fd, buffer, sizeof( buffer ) ) ) > 0 ) {
      // We got some of the file, print it out (note that it's not a
      // null-terminated string, just a buffer of len characters.
      // for ( int i = 0; i < len; i++ )
      //   printf( "%c", buffer[ i ] );
      for (int i=0; i<=len ; i++){
        if(buffer[i] == '\n'){
           lines++;
      }
    }
  }
    // We read up to the end-of-file, close the file and exit.
    close( fd );
  
    
}
 
printf("num of line = %d\n",lines);
}
