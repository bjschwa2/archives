#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Bradley Schwarz
 * Bjschwa2
 *
 * This program can use multiple CPU cores to solve
 * a computationally intensive problem more quickly.
 */

 #define THREE 3

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

// Dynamically allocated list of numbers
int *numList;

// Number of values on the numList.
int numCount;

void readNumbers( char const *fileName ) {
  FILE *fp = fopen( fileName, "r" );
  if ( !fp )
    fail( "Can't open number list file" );
  
  // Initialize a resizable array of numbers.
  numCount = 0;
  int capacity = 10;
  numList = (int *) malloc( capacity * sizeof( int ) );

  // Read as many numbers as we can.
  int val;
  while ( fscanf( fp, "%d", &val ) == 1 ) {
    // Grow the array if needed.
    if ( numCount >= capacity ) {
      capacity *= 2;
      numList = (int *) realloc( numList, capacity * sizeof( int ) );
    }
    
    // Copy the latest number into the list.
    numList[ numCount++ ] = val;
  }
}

// Simple iterative gcd calculation.
int gcd( int a, int b ) {
  while ( b != 0 ) {
    int c = a % b;
    a = b;
    b = c;
  }

  return a;
}

int main( int argc, char *argv[] ) {
  if ( argc != THREE )
    fail( "usage: pairs <file-name> <numberOfWorkers>" );

  //parents reads the list
  readNumbers( argv[ 1 ] );

  //get number of workers
  int numWork = atoi(argv[2]);

  //total
  int total = 0;

   //makes a pipe
  int workpipe[ 2 ];
  if ( pipe( workpipe ) != 0 )
    fail( "Can't create pipe" );

  //makes workers
  pid_t wor[numWork];

  //puts the workers to work
  for(int i=0; i< numWork; ++i){

    //forks workers
    if ( (wor[i] = fork()) < 0 ) {
    fprintf( stderr, "Fork failed\n" );
    exit( 0 );

    //if its a worker
    }else if ( wor[i] == 0 ) {

      // Check pairs of different numbers.
      int wtotal=0;
      for ( int j = i; j < numCount; j+=numWork )
        for ( int k = j + 1; k < numCount; k++ )
          if ( gcd( numList[ j ], numList[ k ] ) == 1 )
            wtotal++;

      //lock the pipe
      lockf( workpipe[1], F_LOCK, 0 );

      //write to the pipe
      int size = write( workpipe[ 1 ], &wtotal, sizeof(wtotal) );
      if ( size < 0 )
        fail( "Can't write into pipe" );

      //unlock pipe
      lockf( workpipe[1], F_ULOCK, 0 );

      exit(0);
    }
  }

  //parents collects the values
  for(int i = 0; i<numWork; i++){
      int ntotal=0;

      //reads from the pipe
      read( workpipe[ 0 ], &ntotal, sizeof( ntotal ) );

      //adds the workers totals together
      total+= ntotal;
  }

  // Print the resulting total.
  printf( "Total: %d\n", total );
  return 0;
}