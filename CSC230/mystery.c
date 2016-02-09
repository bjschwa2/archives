/*******************************************************************
* Bradley Schwarz
* CSC230, HW1
*
* an exercise in program formatting
*******************************************************************/
#include <stdio.h>

int function( int, int );

/* Begins the program serves as the main fuction
 * Determines the largest number in the attic and prints it
 * Inputs: none
 * Output: 0 
 * Pre/Post conditions: none
 */
int main( void )
{
  int a[] = {162, 198, 91, 84, 371, -111, 243, 42};
  int c = 8, t = 0;

  for(int b = 0; b < c; b++) {
    t = function(t, a[b]);
  
  }
  printf("%d\n", t);
  return 0;
 
}

/* Determines which number is larger and then returns it. 
 * Inputs: int q, int z
 * Output: int q, int z 
 * Pre/Post conditions: The largest number is returned.
 */
int function(int q, int z)
{
  if(q > z) {
    return q;
  }  
  return z;
}