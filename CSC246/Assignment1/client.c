#include "common.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

/* Bradley Schwarz
 * Bjschwa2
 *
 * This program is the client that 
 * communicates using POSIX message queues
 */

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

int main(int argc, char *argv[]) {

	if ( argc != 3 )
    fail( "usage: client <add/remove/query> <word>" );

  // make arguments into char
  char *word = argv[2];
  char *para = argv[1];

  // Open the message queue for talking to the server.
  mqd_t serverQueue = mq_open( SERVER_QUEUE, O_WRONLY );
  mqd_t clientQueue = mq_open( CLIENT_QUEUE, O_RDONLY );
  if ( serverQueue == -1  || clientQueue == -1)
    fail( "Can't open message queue" );

  // Send the parameter(arg 2)
  mq_send( serverQueue, para, strlen( para ), 0 );

  // Send the word (arg 3)
  mq_send( serverQueue, word, strlen( word ), 0 );
  
  
  //receive the answer from server
  char ans[MESSAGE_LIMIT +1];
  int len = mq_receive(clientQueue, ans, sizeof( ans ), NULL);
  if(len >=0){
  	for ( int i = 0; i < len; i++ )
      printf( "%c", ans[ i ] );
    	printf("\n");
  }

  // We're done, close our copy of the queue (which would happen when we exit anyway).
  mq_close( serverQueue );
  mq_close( clientQueue );

  exit(0);
}