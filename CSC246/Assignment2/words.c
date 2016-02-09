#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* Bradley Schwarz
 * Bjschwa2
 *
 * This program uses shared memory to hold 
 * a set of words provided by the user.
 */

// Maximum number of words the server can hold.
#define MAX_WORDS 10

// Maximum length of a word (in characters)
#define WORD_LEN 19

// Type for a single word (with room for the null)
typedef char Word[ WORD_LEN + 1 ];

/** Type for representing the whole set of words. */
typedef struct {
  /* Set of words maintained by the server. */
  Word list[ MAX_WORDS ];

  /* Current number of words in the server's set. */
  int count;

} WordSet;

// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

int inlist( char* input , WordSet* wor){

  int within = 0;
  for(int i=0; i<wor->count; i++){
    if(strcmp(wor->list[i], input)== 0){
      within = 1;
    } 
  }
  return within;
}

int main( int argc, char *argv[] ) {
  // Make sure we have two arguments, and they aren't too long.
  if ( argc != 3 )
    fail( "usage: words [add|query|remove] <word>" );

    // make arguments into char
  char *input = argv[2];
  char *para = argv[1];

  // create a random key
  int key = ftok("/afs/unity.ncsu.edu/users/b/bjschwa2", 'P');

  // allocate shared memory
  int shmid = shmget( key, sizeof(WordSet), 0666 | IPC_CREAT );
  if ( shmid == -1 )
    fail( "Can't create shared memory" );

  WordSet *wor = (WordSet *) shmat(shmid,0,0);
    if (wor == (WordSet*) -1){
      fail("cant enter memory");
    }

    // checks if add
    if(strcmp( para, "add" ) == 0){
      if(inlist(input,wor)==0){
        if((wor->count) < MAX_WORDS){
          strcpy((wor->list[wor->count]), input);
          wor->count++;
          printf("Ok\n");
        }
      }else{
        printf("Error\n");
      }
    //checks if remove
    }else if( strcmp( para, "remove")==0){
      if(inlist(input,wor)==1){
        for(int i=0; i< wor->count; i++){
          if(strcmp(wor->list[i], input) == 0){
            for(int j= i ; j<= wor->count; j++){
              strcpy(wor->list[j], wor->list[j+1]);
            }
            wor->count--;
            printf("OK\n");
          }
        }
      }else{
        printf("Error\n");
      }
    // checks if query
    }else if(strcmp(para, "query") == 0){
      if( inlist(input,wor) == 1){
        printf("Yes\n");
      }else{
        printf("No\n");
      }
    }
  return 0;
}
