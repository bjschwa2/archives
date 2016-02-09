#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Bradley Schwarz
 * Bjschwa2
 *
 * This program uses 3 different threads to demonstrate
 * concurrent execution.
 */

/** General purpose fail function.  Print a message and exit. */
static void fail( char const *format, ... );

/** Function run by thread 1. */
void *threadfunc1( void *arg ) {
  printf("a");
  printf("b");
  return NULL;
}

/** Function run by thread 2. */
void *threadfunc2( void *arg ) {
  printf("c");
  printf("d");
  return NULL;
}

/** Function run by thread 3. */
void *threadfunc3( void *arg ) {
  printf("e");
  printf("f");
  return NULL;
}

int main( int argc, char *argv[] ) {
  // Structure used to keep up with each new thread.
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;

  // Create then join a bunch of threads.
  for ( int i = 0; i < 100000; i++ ) {
    if ( pthread_create( &thread1, NULL, threadfunc1, NULL ) != 0 ) 
      fail( "Can't create a child thread\n" );
    if ( pthread_create( &thread2, NULL, threadfunc2, NULL ) != 0 ) 
      fail( "Can't create a child thread\n" );
    if ( pthread_create( &thread3, NULL, threadfunc3, NULL ) != 0 ) 
      fail( "Can't create a child thread\n" );

    // Wait for our child thread to exit.
    pthread_join( thread1, NULL );
    pthread_join( thread2, NULL );
    pthread_join( thread3, NULL );
    printf("\n");
  }
  return 0;
}

static void fail( char const *format, ... ) {
  va_list param;
  va_start( param, format );

  vprintf( format, param );
  va_end( param );

  exit( -1 );
}
