#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <semaphore.h>

/** Port number used by my server */
#define PORT_NUMBER "26054"

// Maximum number of words the server can hold.
#define MAX_WORDS 10

// Maximum length of a word (in characters)
#define WORD_LEN 19

// Semaphore to protect the critical section
sem_t lock;

//Signal to be used to catch ctrl C
static bool notCtrlC = true;

//global socket for the server
int servSock = 0;

// Type for a single word (with room for the null)
typedef char Word[ WORD_LEN + 1 ];

/** Type for representing the whole set of words.  We don't really
    need to wrap this up in a struct for this program, but it makes it
    easier to re-use code from a previous assignment. */
typedef struct {
  /* Set of words maintained by the server. */
  Word list[ MAX_WORDS ];

  /* Current number of words in the server's set. */
  int count;
} WordSet;

// Global word set.
WordSet wordSet;

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

// Check the list for a specific word
bool queryWord(WordSet *set, char *word) {
  for (int i = 0; i <= set->count; i++) {
    if (strcmp(set->list[i], word) == 0) {
      //word is in the list
      return true;
    }
  }
  //word is not in the list
  return false;
}

// Report the words in the list
void report(WordSet *set, FILE *fp) {
  for (int i = 0; i < set->count; i++) {
    fprintf(fp, "%s\n", set->list[i]);
    fflush(fp);
  }
}

// Remove a word in the list
bool removeWord(WordSet *set, char *word) {
  // use query to check for word
  if (queryWord(set, word) == true) {
    for (int i = 0; i < set->count; i++) {
      if (strcmp(set->list[i], word) == 0) {
        // shift the words over
        for (int j = i; j <= set->count-1; j++) {
          strcpy(set->list[j], set->list[j+1]);
        }
        //decrament the count
        set->count--;
        //word sucessfully removed
        return true;
      }
    }
  }
  else {
    //word not removed
    return false;
  }
  return 0;
}

// Add a specified word to the list
bool addWord(WordSet *set, char *word) {
  // Use query to check for word
  if (queryWord(set, word) == false) {
    if (set->count < MAX_WORDS) {
      // add word to list
      strcpy((set->list[set->count]), word);
      //increment the count
      set->count++;
      //word added to the list
      return true;
    }
  }
  else {
    //word not added to the list
    return false;
  }
  return 0;
}

//Handles the ctrl c interrupt
void intHandler(int error) {
  //keeps a new client from accessing
  notCtrlC = false; 
  printf("\n");
  for (int i = 0; i < wordSet.count; i++) {
    printf("%s\n", wordSet.list[i]);
  }
  //Close server socket
  close(servSock); 
  //Exit from program
  exit(0);
}

/** handle a client connection, close it when we're done. */
void *handleClient( void* sock ) {
  // Here's a nice trick, wrap a C standard IO FILE around the
  // socket, so we can communicate the same way we would read/write
  // a file.
  int Sock = *((int*)sock);
  FILE *fp = fdopen( Sock, "a+" );
  
  // Prompt the user for a command
  fprintf( fp, "cmd> " );
  fflush( fp );

  //word the user gave
  Word word;
  //command the user gave
  char cmd[ 20 ];
  
  while (fscanf( fp, "%19s", cmd) && strcmp( cmd, "quit" ) != 0 ) {
    //only scan if cmd is add or remove
    if (strcmp(cmd, "add") == 0 || strcmp(cmd, "remove") == 0)
      fscanf(fp, "%s", word);
    
    //flush
    fflush(fp); 
    //lock the list
    sem_wait(&lock);

    //add a word 
    if ((strcmp(cmd, "add")) == 0) {
      if (addWord(&wordSet, word) == true) {
        //word was added to the list
        fprintf(fp, "Ok\n");
      }
      else {
        //already on list
        fprintf(fp, "Error\n");
      }
    }//removing the word
    else if ((strcmp(cmd, "remove")) == 0) {
      if (removeWord(&wordSet, word) == true) {
        //word removed from the list
        fprintf(fp, "Ok\n");
      }
      else {
        //word not in the list   
        fprintf(fp, "Error\n");   
      }
    }
    //report all words
    else if (strcmp(cmd, "report") == 0) {
      report(&wordSet, fp);
    }
    else {
      // command is unknown
      fprintf( fp, "Unknown Command: %s\n", cmd );
      fflush( fp );//flush
    }
    // Prompt the user for an command:
    fprintf( fp, "cmd> " );
    fflush( fp ); // flush
    sem_post(&lock);//unlock the list
  }
  // Close the connection with client.
  fclose( fp );
  return NULL;
}

int main( int argc, char *argv[] ) {
  // Prepare a description of server address criteria.
  struct addrinfo addrCriteria;
  memset(&addrCriteria, 0, sizeof(addrCriteria));
  addrCriteria.ai_family = AF_INET;
  addrCriteria.ai_flags = AI_PASSIVE;
  addrCriteria.ai_socktype = SOCK_STREAM;
  addrCriteria.ai_protocol = IPPROTO_TCP;

  // Initialize the semaphore
  sem_init(&lock, 0, 1);

  // Lookup a list of matching addresses
  struct addrinfo *servAddr;
  if ( getaddrinfo( NULL, PORT_NUMBER, &addrCriteria, &servAddr) )
    fail( "Can't get address info" );

  // Try to just use the first one.
  if ( servAddr == NULL )
    fail( "Can't get address" );

  // Create a TCP socket
  servSock = socket( servAddr->ai_family, servAddr->ai_socktype,
                         servAddr->ai_protocol);
  if ( servSock < 0 )
    fail( "Can't create socket" );

  // Bind to the local address
  if ( bind(servSock, servAddr->ai_addr, servAddr->ai_addrlen) != 0 ) {
    close(servSock);
    fail( "Can't bind socket" );
  }
  
  // Tell the socket to listen for incoming connections.
  if ( listen( servSock, 5 ) != 0 )
    fail( "Can't listen on socket" );

  // Free address list allocated by getaddrinfo()
  freeaddrinfo(servAddr);

  // Fields for accepting a client connection.
  struct sockaddr_storage clntAddr; // Client address
  socklen_t clntAddrLen = sizeof(clntAddr);

  //Signal handler for an interrupt signal
  signal(SIGINT, intHandler);
  while ( 1 ) {
    // Accept a client connection.
    int sock = accept( servSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
    if ( sock == -1 ) {
      fail( "Can't accept on socket" );
    }
    else {
      pthread_t client;
      if (pthread_create(&client, NULL, handleClient, &sock) != 0) {
        fail("Can't make client thread\n");
      }
      pthread_detach(client);
    }
  }
  // Never reached .. for now.
  // close the socket.
  close( servSock );
  
  return 0;
}
