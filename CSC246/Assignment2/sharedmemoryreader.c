#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

// Size of the shared block of memory.
const int BLOCK_SIZE = 1024;

int main() {
  // Make a shared memory segment 1KB in size
  int shmid = shmget( 9876, BLOCK_SIZE, 0666 | IPC_CREAT );
  if ( shmid == -1 )
    fail( "Can't create shared memory" );

  // Map the shared memory into my address space
  char *sbuffer = (char *)shmat( shmid, 0, 0 );
  if ( sbuffer == (char *)-1 )
    fail( "Can't map shared memory segment into address space" );

  // Busy wait until the sender marks the memory as ready using the
  // last byte.  This is a poor technique.
  while ( sbuffer[ BLOCK_SIZE - 1 ] == 0 )
    ;

  // Print out the string
  printf( "%s", sbuffer );

  // Tell the writer we are done with the string.
  sbuffer[ BLOCK_SIZE - 1 ] = 0;
  
  // Release our reference to the shared memory segment.
  shmdt( sbuffer );

  return 0;
}
