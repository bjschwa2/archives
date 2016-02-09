#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* Bradley Schwarz
 * Bjschwa2
 *
 * This program is a Petri dish simulator that
 * simulates the growth of bacteria colonies on
 * a square two dimensional map.
 *
 */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define TWENTY_SIX 26
#define THIRTY_TWO 32
#define MAP_LIMIT 40

int numOfSeed = 0;
int seedList[TWENTY_SIX][2];

// Alphabet for naming seeds
char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
'U', 'V', 'W', 'X', 'Y', 'Z'};

void readColonies( char map[][ MAP_LIMIT ], int mapSize );
int squaredDistance( int *a, int *b );
void growColonies( char map[][ MAP_LIMIT ], int mapSize, int gen );
void inputValid(int value, int maxValue);
void printMap(char map[][MAP_LIMIT], int mapSize);
void exitProgram();

/* Starts the program scans for map size
 * and the amount of generations.
 *
 * Inputs: none
 * Output: exit code
 *
 * Pre/post conditions: None
 */
int main( void )
{
  int mapSize = 0;
  printf("Map size: ");
  int mapInput = scanf("%d", &mapSize);
  inputValid(mapSize, MAP_LIMIT);

  if (mapInput != 1){
    exitProgram();
  }
  
  char map[MAP_LIMIT][MAP_LIMIT];

  for (int i = 0; i < mapSize; i++){
    for (int j = 0; j < mapSize; j++){
      map[i][j] = ' ';
    }
  }

  readColonies(map, mapSize);

  int gen = 0;
  printf("Generations: ");
  int genInput = scanf("%d", &gen);

  if (genInput != 1){
      exitProgram();
    } 

  inputValid(gen, mapSize*mapSize);

  growColonies(map, mapSize, gen);
  printMap(map, mapSize);

  return EXIT_SUCCESS;
}

/* Reads in the number of colonies and fills them 
 * into the map.
 *
 * Inputs: 
 *      map- the map to be used as a petri dish
 *      mapsize- the size of the map
 * Outputs: none
 *
 * Precondition: must have mapsize and map filled with
 * spaces
 * Postcondition: Seeds in map
 */
void readColonies( char map[][ MAP_LIMIT ], int mapSize )
{
  int col = 0;
  int row = 0;

  printf("Number of colonies: ");
  int seedvalid = scanf("%d", &numOfSeed);
  inputValid(numOfSeed, TWENTY_SIX);

  if (seedvalid != 1){
      exitProgram();
    } 

  for(int i = 0; i < numOfSeed; i++){
  
    printf("Seed %c location: ", alphabet[i] );
    int locations = scanf("%d %d", &row, &col );

    if (locations != 2){
      exitProgram();
    }

    inputValid(col, mapSize);
    inputValid(row, mapSize);

    int *ptr = seedList[i];
    *ptr = row;
    ptr++;
    *ptr = col;

    map[row - 1][col - 1] = alphabet[i];
  }
}

/* This function finds the distance between two pointers
 * and then returns it.
 *
 * Inputs:
 *      *a- pointer to the seed
 *      *b- pointer to the location in the map
 * Outputs:
 *      distance- distance between pointer
 *
 * Pre/postcondition: none
 */
int squaredDistance( int *a, int *b )
{
  int aVal = *a;
  a++;
  int bVal = *b;
  b++;

  int cVal = *a;
  int dVal = *b;

  int distance = ((aVal - bVal) * (aVal - bVal)) + ((cVal - dVal) * (cVal - dVal));

  return distance;
}

/* This function makes the seed colonies grow by filling
 * in lowercase values around them.
 *
 * Inputs:
 *      map- the map of Seeds and spaces
 *      mapsize- the size of the map
 *      gen- the amount of generations
 * Outputs: none
 *
 * Precondition: must have seeds in the map
 * Postcondition: map completed
 */
void growColonies( char map[][ MAP_LIMIT ], int mapSize, int gen )
{
  int mapLoc[2];

  for (int q = 1 ; q <= gen; q++){
    for (int k = 1; k <= mapSize ; k++){
      for (int j = 1; j <= mapSize ; j++){

        // sets the current cell in to the array mapLoc
        mapLoc[0] = k;
        mapLoc[1] = j;

        // sets equals to pointer
        int *loc = &mapLoc[0];

        for (int i = 0; i < numOfSeed; i++){

          //sets the ith seed equal to a pointer
          int *seed = seedList[i];

          //finds distance between cell and seed
          int distance = squaredDistance(seed, loc);

          //sets pointer to seedList at current
          int *seed2 = seedList[k];
          int con = 0;
          int avail = 0;

          //checks if current cell is available
          if (map[k-1][j-1] == ' '){
            avail = 1;
          }

          // checks if there is a seed in the current mapLoc
          if (mapLoc[0] == *seed2) {
            seed2++;
            if (mapLoc[1] == *seed2){
              con = 1;
            }
          }

          //if the gen equals distance and its available grow there
          if ((q == distance) && avail && !con){
            char lowCase = alphabet[i];
            lowCase += THIRTY_TWO;
            map[k-1][j-1]= lowCase;
          }

          //checks if other seeds are equal distance from a cell
          for (int l = i+1 ; l < numOfSeed; l++ ){

            //pointer to new seed
            int *ptrSeed = seedList[l];
            int sameDis = squaredDistance(ptrSeed, loc);

            // if same distance and its available put a star
            if ((distance == sameDis) && (distance == q) && (sameDis == q) && avail){
              map[k-1][j-1]= '*';
            }
          }
        }
      }
    }
  }
}

/* Checks if the input is valid.
 *
 * Inputs:
 *      value- the value entered
 *      maxValue- the max value that can be entered
 * Outputs: none
 *
 * Pre/postcondition: none
 */

 void inputValid(int value, int maxValue)
 {

  if (value < 0 || value > maxValue ){
    exitProgram();
  }
}

/* Prints the map properly.
 *
 * Inputs:
 *      map- the map to print
 *      mapsize- how large to make the map
 * Outputs: the map printout
 *
 * Precondition: must have the map created
 * Postcondition: none
 */
 void printMap(char map[][MAP_LIMIT], int mapSize)
 {
   printf("+");
  for (int h = 0; h < mapSize ; h++){
    printf("-");
  }
  printf("+\n");

    for (int i = 0; i < mapSize; i++){
      printf("|");

      for (int j = 0; j < mapSize; j++){


       if (map[i][j] == ' '){
        printf(" ");

       }else{
       printf("%c", map[i][j] );

        }
      }
      printf("|\n");
    }

  printf("+");
  for (int h = 0; h < mapSize ; h++){
    printf("-");
  }
  printf("+\n");

 }


/* exits the program properly.
 *
 * Inputs: none
 * Outputs: none
 *
 * Pre/postcondition: none
 */
 void exitProgram(){
    printf("invalid input\n");
    exit(EXIT_FAILURE);
 }