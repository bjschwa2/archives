#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bradley Schwarz
 * Bjschwa2
 *
 * Program for counting the lines of a text
 * file using fopen fread and fclose.
 * note: I referanced Dr. Sturgill's readfile.c
 */

 #define TWO 2
 #define THREE 3

int main( int argc, char *argv[] )
{
	// Line counter.
	int lines = 0;

	// Iterations to run.
  for(int i=0; i< *argv[THREE]; i++){
    lines = 0;

    // Open a file for reading.
    FILE *fp = fopen( argv[1], "r" );
    if ( fp < 0 )
      exit(1);

    // Read the file in specified amounts.
    int size;
    char buffer[*argv[TWO]];
    while ( ( size = fread( buffer, 1, *argv[TWO], fp ) ) > 0 ) {
      for (int i=0; i<size ; i++){
      	// Look for end lines in the buffer.
        if(buffer[i] == '\n'){
           lines++;
      	}
    	}
  	}
  	// Close the file.
    fclose( fp ); 
	}
// Print number of lines.
printf("num of line = %d\n",lines);
}