// Multi-threaded program to simulate the players forming 3-person
// teams for, I don't know, let's say Basketball.

#include <stdio.h>
#include <pthread.h>   // for pthreads
#include <stdlib.h>    // for exit
#include <unistd.h>    // for sleep/usleep
#include <string.h>    // for strcmp

#include "RockPaperScissors.h"

#define PLAYERS_PER_TEAM 10

// Names for the players, the first 10 are on the red team,
// the next are on the blue team.
static char playerNames[][ 2 * PLAYERS_PER_TEAM ] = {
  "Lue",
  "Robin",
  "Brandee",
  "Charisse",
  "Jacqueline",
  "Agatha",
  "Joellen",
  "Corinne",
  "Ruthie",
  "Anthony",
  "Aisha",
  "Terra",
  "Clifton",
  "Kermit",
  "Vernice",
  "Katina",
  "Normand",
  "Maurine",
  "Sheryl",
  "Estela"
};

// True if we're printing a lot of messages as players start and finish games.
int verbose = 0;

// General purpose fail function.  Print a message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

/** Function called by each of the red players. */
void *redPlayer( void *arg ) {
  // Get my index.
  int index = *(int *)arg;
  int winCount = 0;

  // Vector of choices this player may make.  There's a slight
  // preference for rock.
  int choices[] = { ROCK, ROCK, PAPER, SCISSORS };

  // Play a fixed number of games.
  for ( int i = 0; i < 200; i++ ) {
    // Wait of a little while.
    usleep( rand() % 10000 );

    // Choose something to throw from our biased list of choices.
    int choice = choices[ random() % ( sizeof(choices) / sizeof(int) ) ];

    // Play a game.
    int result = throwRed( playerNames[ index ], choice );

    // Count wins
    if ( result > 0 )
      winCount++;
  }

  // Report total wins for this player
  printf( "red player %s, %d wins\n", playerNames[ index ], winCount );

  return NULL;
}

/** Function called by each of the red players. */
void *bluePlayer( void *arg ) {
  // Get my index.
  int index = *(int *)arg;
  int winCount = 0;

  // Vector of choices this player may make.  There's a slight
  // preference for PAPER.
  int choices[] = { ROCK, PAPER, PAPER, SCISSORS };

  // Play a fixed number of games.
  for ( int i = 0; i < 200; i++ ) {
    // Wait of a little while.
    usleep( rand() % 10000 );

    // Choose something to throw from our biased list of choices.
    int choice = choices[ random() % ( sizeof(choices) / sizeof(int) ) ];

    // See how we do.
    int result = throwBlue( playerNames[ index ], choice );

    // Count wins
    if ( result > 0 )
      winCount++;
  }

  // Report total wins for this player
  printf( "blue player %s, %d wins\n", playerNames[ index ], winCount );

  return NULL;
}

int main( int argc, char *argv[] ) {
  if ( argc == 2 && strcmp( argv[ 1 ], "-verbose" ) == 0 )
    verbose = 1;

  // Initialize the monitor our threads are using.
  initRockPaperScissors();

  // Thread id for each of the threads
  int tcount = sizeof( playerNames ) / sizeof( playerNames[ 0 ] );
  pthread_t thread[ tcount ];

  // Storage for thread arguments, one per thread.
  int argument[ tcount ];

  // Make all the red players.
  for ( int i = 0; i < PLAYERS_PER_TEAM; i++ ) {
    argument[ i ] = i;
    // Start a thread for this player, giving it index i.
    if ( pthread_create( thread + i, NULL, redPlayer, argument + i ) != 0 )
      fail( "Can't make a red player thread\n" );
  }

  // Make all the blue players.
  for ( int i = PLAYERS_PER_TEAM; i < 2 * PLAYERS_PER_TEAM; i++ ) {
    argument[ i ] = i;
    // Start a thread for this player, giving it index i.
    if ( pthread_create( thread + i, NULL, bluePlayer, argument + i ) != 0 )
      fail( "Can't make a blue player thread\n" );
  }

  // When we're done, join with all the threads.
  for ( int i = 0; i < tcount; i++ )
    pthread_join( thread[ i ], NULL );

  // Print the final win/loss count and finish.
  reportStats();

  // Free any monitor resources.
  destroyRockPaperScissors();

  return 0;
}
