#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/* Bradley Schwarz
 * Bjschwa2
 *
 * Program for counting the lines of a text
 * file using open read and close.
 * note: I referanced Dr. Sturgill's readfile.c
 */

 #define TWO 2
 #define THREE 3

int main(int argc, char *argv[]) 
{

  // line counter.
  int lines = 0;

  // Iterations to run.
  for(int i=0; i< *argv[THREE]; i++){
    lines = 0;

    // Open a file for reading.
    int file = open( argv[1], O_RDONLY );
    if ( file < 0 )
      exit(1);

    // Read the file in specified amounts.
    int size;
    char buffer[*argv[TWO]];
    while ( ( size = read( file, buffer, sizeof( buffer ) ) ) > 0 ) {
      for (int i=0; i<size ; i++){
        // Find end lines in buffer.
        if(buffer[i] == '\n'){
           lines++;
        }
      }
    }
    // Close the file.
    close( file ); 
  }

// Print the number of lines.
printf("num of line = %d\n",lines);
}
