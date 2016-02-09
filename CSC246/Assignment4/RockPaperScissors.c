#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


#include "RockPaperScissors.h"
// throws for each type
int redRock = 0;
int redPaper = 0;
int redScissor = 0;

//red wins for each throw
int redRockW = 0;
int redPaperW = 0;
int redScissorW = 0;

//locks other players out from the red team
pthread_mutex_t redLock;

pthread_mutex_t proceed;

//signals blue team that red team is ready to play
pthread_cond_t redThrowFight;

//determines if red team has a player ready
static bool redReady;

//keeps track of whether or not a red player is playing
static bool redInUse = false;

//what the red team throws 
static int redThrow;

//signals the blue team that the red
// team has players ready
pthread_cond_t redThrowAvail;

//signals blue team the red team is 
//  ready to play
pthread_cond_t redThrowFight;

//signal red team that blue has printed
//  its name
pthread_cond_t bluePrinted;

static bool blueNamePrinted = false;

//a count of how many red players are ready
static int redPlayers = 0;

//blue throws for each type
int blueRock = 0;
int bluePaper = 0;
int blueScissor = 0;

//blue wins for each throw
int blueRockW = 0;
int bluePaperW = 0;
int blueScissorW = 0;

//lock for the blue team
pthread_mutex_t blueLock;

//keeps track if there are currently
//  blue players available
pthread_cond_t blueThrowAvail;

//signals the red team that the blue team
// is ready to play
pthread_cond_t blueThrowFight;

pthread_cond_t redCont;

pthread_cond_t blueCont;

//signals the red team that the blue team
//  has printed their name
pthread_cond_t bluePrintName;

//true when red team has printed out its information
static bool redPrinted = false;

//determines if blue team has a player ready
static bool blueReady;

//what the red team throws 
static int blueThrow;

//a count of how many blue players are ready
static int bluePlayers = 0;

//true if a blue player is currently playing
static bool blueInUse = false;

static int blueResult;

static bool aware = false;

void initRockPaperScissors() {
    redPrinted = false;
    redInUse = false;
    blueNamePrinted = false;
    blueInUse = false;

    //create and initialize the red team lock
    
    pthread_mutex_init( &redLock, NULL );


    pthread_cond_init(&redCont, NULL);

    pthread_cond_init(&blueCont, NULL);


    //create and initialize the red team available Condition
    pthread_cond_init(&redThrowFight, NULL);

    //create and initialize the blue team lock
    pthread_mutex_init( &blueLock, NULL );



    pthread_cond_init(&blueThrowAvail, NULL);

    //create and initialize the condition
    // that fight flags are set for blue team
    pthread_cond_init(&blueThrowFight, NULL);

    //create and initialize the condition
    // that fight flags are set for blue team
    pthread_cond_init(&bluePrintName, NULL);

    //condition that the blue teams name has been printed
    pthread_cond_init(&bluePrinted, NULL);

}

void destroyRockPaperScissors() {


}

/** Called by a red player when they want to play, passing in the
    player's name and what they want to throw from among the three
    constants defined above. */
int throwRed( char const *name, int choice ) {
    pthread_mutex_lock(&redLock);
    //pthread_mutex_lock(&redLock2);

    redPlayers++;

    while (bluePlayers < 1 || (redInUse == true)) {
        pthread_cond_wait(&blueThrowAvail, &redLock);
    }

    //pthread_mutex_lock(&redLock2);
    pthread_cond_signal(&redThrowAvail);

    redInUse = true;
    int result;

    if (choice == ROCK) {
        redRock++;
    }
    else if (choice == PAPER) {
        redPaper++;
    }
    else if (choice == SCISSORS) {
        redScissor++;
    }
    redThrow = choice;
    redReady = true;

    //signal blue you are ready to play
    pthread_cond_signal(&redThrowFight);

    while (!blueReady) {//while blue isnt ready, wait
        pthread_cond_wait(&blueThrowFight, &redLock);
    }

    if (choice == ROCK) {//determine who wins based on your own
                            //choice and theirs
        if (blueThrow == ROCK) {
            printf("%s -- ", name);
            result = 0;
            blueResult = 0;
        }
        else if (blueThrow == PAPER) {
            bluePaperW++;
            printf("%s -> ", name);
            result = -1;
            blueResult = 1;
        }
        else if (blueThrow == SCISSORS) {
            redRockW++;
            printf("%s <- ", name);
            result = 1;
            blueResult = -1;
        }
    }
    else if (choice == PAPER) {
        if (blueThrow == ROCK) {
            redPaperW++;
            printf("%s <- ", name);
            result = 1;
            blueResult = -1;
        }
        else if (blueThrow == PAPER) {
            printf("%s -- ", name);
            result = 0;
            blueResult = 0;
        }
        else if (blueThrow == SCISSORS) {
            blueScissorW++;
            printf("%s -> ", name);
            result = -1;
            blueResult = 1;

        }
    }
    else if (choice == SCISSORS) {
        if (blueThrow == ROCK) {
            blueRockW++;
            printf("%s -> ", name);
            result = -1;
            blueResult = 1;

        }
        else if (blueThrow == PAPER) {
            redScissorW++;
            printf("%s <- ", name);
            result = 1;
            blueResult = -1;
        }
        else if (blueThrow == SCISSORS) {
            printf("%s -- ", name);
            result = 0;
            blueResult = 0;
        }
    
    }

    redPrinted = true;//red team has printed their name and 
                        // the result
    //let blue team know red team has printed
    pthread_cond_signal(&bluePrintName);

    //while blue team hasnt printed their name, wait
    while (!blueNamePrinted) {
        pthread_cond_wait(&bluePrinted, &redLock);
        pthread_cond_signal(&blueCont);

    }
    

    redPlayers--;//decremant the total red players
    redPrinted = false;//reset red printed
    redReady = false;//reset red team being ready
    redInUse = false;//red teams player is no longer playing
    //pthread_mutex_unlock(&redLock2);//unlock red teams locks
    pthread_mutex_unlock(&redLock);
    return result;

}

/** Called by a blue player when they want to play, passing in the
    player's name and what they want to throw from among the three
    constants defined above. */
int throwBlue( char const *name, int choice ) {
    pthread_mutex_lock(&blueLock);
    bluePlayers++;

    //wait while there aren't any red players or while
        //there a blue player is setting up
    while (redPlayers < 1 || (blueInUse == true)) {
        pthread_cond_wait(&redThrowAvail, &blueLock);
    }

    //pthread_mutex_lock(&blueLock2);
    pthread_cond_signal(&blueThrowAvail);
    blueInUse = true;//there is currently a blue player playing
    
    
    //increment the correct move based on the players choice
    if (choice == ROCK) {
        blueRock++;
    }
    else if (choice == PAPER) {
        bluePaper++;
    }
    else if (choice == SCISSORS) {
        blueScissor++;
    }

    blueThrow = choice;//set blue choice
    blueReady = true;//blue team is ready to play
    //let the red team know a blue team member is ready
    pthread_cond_signal(&blueThrowFight);

    //wait while the red team isn't ready
    while (!redReady) {
        // pthread_cond_signal(&blueThrowFight);
        pthread_cond_wait(&redThrowFight, &blueLock);
    }

    //wait while the red team hasn't printed their name
        //and the result 
    while (!redPrinted) {
        pthread_cond_wait(&bluePrintName, &blueLock);
    }

    printf("%s\n", name);//print the players name
    blueNamePrinted = true;//the players name has been printed
    pthread_cond_signal(&bluePrinted);//alert the red team  
    //while (!aware) {
        pthread_cond_wait(&blueCont, &blueLock);
    //}
    //aware = false;


    bluePlayers--;//decrement the total number of blue players
    blueInUse = false;//the blue team does not have a player in use
    blueReady = false;//blue team is not ready
    blueNamePrinted = false;//blue team has not printed their name yet
    //pthread_mutex_unlock(&blueLock2); 

    pthread_mutex_unlock(&blueLock); 
    
    return blueResult;
}

void reportStats() {

}
