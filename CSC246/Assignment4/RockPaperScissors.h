#ifndef __ROCK_PAPER_SCISSORS_H__
#define __ROCK_PAPER_SCISSORS_H__

/** Interface for the RockPaperScissors monitor.  If I was programming in
    C++, this would all be wrapped up in a class.  Since we're using
    C, it's just a collection of functions, with an initialization
    function to init the state of the whole monitor. */

/** Initialize the monitor. */
void initRockPaperScissors();

/** Destroy the monitor, freeing any resources it uses. */
void destroyRockPaperScissors();

// The three alternatives for what a player can throw
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

/** Called by a red player when they want to play, passing in the
    player's name and what they want to throw from among the three
    constants defined above. */
int throwRed( char const *name, int choice );

/** Called by a blue player when they want to play, passing in the
    player's name and what they want to throw from among the three
    constants defined above. */
int throwBlue( char const *name, int choice );

/** Print a report of how many wins and throws each team has had with each symbol. */
void reportStats();

#endif
