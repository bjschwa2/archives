#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Size of shared buffer */
#define BUF_SIZE 10

int buffer[BUF_SIZE];	// Storage for shared buffer
int first = 0;		// First full slot in the buffer
int num = 0;		// number of elements in buffer

// Lock for access to the buffer.
pthread_mutex_t mon = PTHREAD_MUTEX_INITIALIZER;
// Condition for blocking the consumer, are there some items.
pthread_cond_t itemCond = PTHREAD_COND_INITIALIZER;
// Condition for blocking the producer, are there empty slots.
pthread_cond_t slotCond = PTHREAD_COND_INITIALIZER;

/** General purpose fail function.  Print a message and exit. */
static void fail( char const *msg );

void *producer(void *param) {
  for ( int i=0; i < 1000; i++ ) {
    int item = i;  // Pretend to produce an item, just use the loop counter
    printf ( "Produced item %d\n", item ); fflush( stdout );

    pthread_mutex_lock( &mon );   // Enter the monitor
    while ( num == BUF_SIZE )	// Block until there's a slot
      pthread_cond_wait( &slotCond, &mon );

    // Put item in the buffer.
    buffer[ ( first + num ) % BUF_SIZE ] = item;
    num++;

    // Wake any consumers waiting on an item.
    pthread_cond_signal( &itemCond );

    pthread_mutex_unlock( &mon );  // Leave the monitor
  }

  return NULL;
}

void *consumer(void *param) {
  for ( int i = 0; i < 1000; i++ ) {
    pthread_mutex_lock( &mon ); // Enter the monitor.
    while ( num == 0 )	        // block until there's an item
      pthread_cond_wait( &itemCond, &mon );

    // Remove item from the buffer.
    int item = buffer[ first ];
    first = ( first + 1 ) % BUF_SIZE;
    num--;

    // Wake any producers waiting on an available slot
    pthread_cond_signal( &slotCond );
    pthread_mutex_unlock( &mon );

    printf ( "Consuming item %d\n", item ); fflush( stdout );
  }

  return NULL;
}

int main() {
  pthread_t tid1, tid2;

  // Make one producer and one consumer thread
  if ( pthread_create(&tid1,NULL,producer,NULL) != 0 ||
       pthread_create(&tid2,NULL,consumer,NULL) != 0 )
    fail( "Unable to create consumer thread" );

  // Let the threads do their jobs, wait for them to finish.
  pthread_join( tid1, NULL );
  pthread_join( tid2, NULL );

  return 0;
}

static void fail( char const *msg ) {
  fprintf( stderr, "%s\n", msg );
  exit( -1 );
}

