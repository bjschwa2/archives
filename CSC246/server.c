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
 * This program is the server that 
 * communicates using POSIX message queues
 */

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

/* Set of words maintained by the server. */
Word wordList[ MAX_WORDS ];

/* Current number of words in the server's set. */
int wordCount = 0;

int main( int argc, char *argv[] ) {
  // Remove both queues, in case, last time, this program terminated
  // abnormally with some queued messages still queued.
  mq_unlink( SERVER_QUEUE );
  mq_unlink( CLIENT_QUEUE );

  // Prepare structure indicating maximum queue and message sizes.
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 1;
  attr.mq_msgsize = MESSAGE_LIMIT;

  // Make both the server and client message queues.
  mqd_t serverQueue = mq_open( SERVER_QUEUE, O_RDONLY | O_CREAT, 0600, &attr );
  mqd_t clientQueue = mq_open( CLIENT_QUEUE, O_WRONLY | O_CREAT, 0600, &attr );
  if ( serverQueue == -1 || clientQueue == -1 )
    fail( "Can't create the needed message queues" );

  // Repeatedly read and process client messages.  The server
  // will fall out of this loop when the user kils it.
  while ( true ) {

    // buffer for reading from the sender
    char buffer[ MESSAGE_LIMIT ];

    // try to get message
    int len = mq_receive( serverQueue, buffer, sizeof( buffer ), NULL );

    // if message was recieved
    if (len >= 0){

      // apply parameter add
      if(strcmp(buffer, "add" ) == 0){

        if (wordCount <= MAX_WORDS){
          char word[MESSAGE_LIMIT +1];

          // get word
          int len = mq_receive( serverQueue, word, sizeof( word ), NULL );
          if(len >=0){
            int within = 0;

            // check if word is present
            for(int i=0; i<wordCount; i++){
              if(strcmp(wordList[i], word)== 0){
                within = 1;
              } 
            }

            // exit if word is there
            if(within == 1){
              mq_send(clientQueue, "Error", strlen( "Error" ), 0 );

            // make word
            }else{
              Word w;

              strcpy(w, word);
              strcpy(wordList[wordCount], w);
              wordCount++;

              mq_send(clientQueue,"Ok", strlen( "Ok" ), 0 );
              memset(&word[0],0,sizeof(word)); 
            }
          }
        }else{
          mq_send(clientQueue, "Error", strlen( "Error" ), 0 );
        }

      // If remove is parameter
      }else if(strcmp(buffer, "remove")== 0){
        char word[MESSAGE_LIMIT +1];
        int len = mq_receive( serverQueue, word, sizeof( word ), NULL );
        if(len >=0){

     
            // check if word is present
            int within = 0;
            for(int i=0; i< wordCount; i++){
              if(strcmp(wordList[i], word)== 0){
                within = 1;
              }
            }

            if (within == 1){
              // If exists remove word print ok else print error
              for(int i=0; i< wordCount; i++){
                if(strcmp(wordList[i], word) == 0){
                  for(int j= i ; j<= wordCount; j++){
                    strcpy(wordList[j], wordList[j+1]);
                  }
                  wordCount--;
                  memset(&word[0],0,sizeof(word));
                  mq_send(clientQueue, "Ok", strlen( "Ok" ), 0 );
                }
              }

            }else{
              mq_send(clientQueue, "Error", strlen( "Error" ), 0 );
            }
         }

      // If parameter is query  
      }else if( strcmp(buffer, "query") == 0){
        char word[MESSAGE_LIMIT +1];
        int len = mq_receive( serverQueue, word, sizeof( word ), NULL );
        if(len >=0){
          if(wordCount > 0){

            // If word is found print yes else print no
            int within = 0;

            // check if word is present
            for(int i=0; i<wordCount; i++){
              if(strcmp(wordList[i], word)== 0){
                within = 1;
                memset(&word[0],0,sizeof(word));
              }
            }
            if(within == 1){
              mq_send(clientQueue, "Yes", strlen( "Yes" ), 0 );
            }else{
              mq_send(clientQueue, "No", strlen( "No" ), 0 );
            }
          }else{
            mq_send(clientQueue, "No", strlen( "No" ), 0 );
          }
        } 
      }
      memset(&buffer[0],0,sizeof(buffer));
    }
  }

  for ( int i = 0; i < wordCount; i++ )
    printf( "%s", wordList[ i ] );
    printf("\n");

  // Close our two message queues (and delete them).
  mq_close( clientQueue );
  mq_close( serverQueue );

  // Delete the message queues, this is for normal server termination.
  mq_unlink( SERVER_QUEUE );
  mq_unlink( CLIENT_QUEUE );

  return 0;
}
