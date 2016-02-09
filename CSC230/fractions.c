/*
 * Print the decimal approximation of a set of fractions.
 */
#include <stdio.h>
#include <stdlib.h>

#define LIMIT 4

int main( void ) {

  for (int i = 1 ; i <= LIMIT ; i++ ){

  	printf(" \n");
  
  	for (int j = 1 ; j <= LIMIT ; j++ ){

  	  float z =  (float)i/ (float)j;

      printf( "%d / %.d  = %.2f  ", i,j,z );

    }
  }
  
  return EXIT_SUCCESS;
}