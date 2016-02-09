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

const int BLOCK_SIZE = 1024;

int main() {
  // Make a shared memory segment 1KB in size
  int shmid = shmget( 9876, BLOCK_SIZE, 0666 | IPC_CREAT );
  if ( shmid == -1 )
    fail( "Can't create shared memory" );

  char *sbuffer = (char *)shmat( shmid, 0, 0 );
  if ( sbuffer == (char *)-1 )
    fail( "Can't map shared memory segment into address space" );

  // Read a line of text from the user
  printf( "Enter a message: " );
  fgets( sbuffer, BLOCK_SIZE - 1, stdin );

  // Tell the receiver that we have filled in the string.
  sbuffer[ BLOCK_SIZE - 1 ] = 1;

  // Busy wait for the receiver to use the string.
  // This is bad.
  while ( sbuffer[ BLOCK_SIZE - 1 ] )
    ;

  // Release our reference to the shared memory segment.
  shmdt( sbuffer );

  // Tell the OS we no longer need the segment.
  shmctl( shmid, IPC_RMID, 0 );

  return 0;
}
