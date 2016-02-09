// Using function pointers in qsort and to
// decide how individual items should be printed.

#include <stdio.h>
#include <stdlib.h>

int myComp( const void *a, const void *b )
{
  int *ptra = (int*)a;
  int *ptrb = (int*)b;
  int valueb =*ptrb;
  int valuea =*ptra;


  if (*ptrb < 0){
    valueb =  valueb*-1;
  }
  if(*ptra < 0){
    valuea = valuea*-1;
  }
  if(valuea == valueb){
    return 1;

  }else{

 return (valuea - valueb );
}

  // Fill in your own comparison function.
  // ...
}

void sortList( int *list, int len )
{
      qsort (list, len, sizeof(int), myComp);
        list++;
  // Call qsort to sort the given list.
  // ...
}

// Used to print an item in the list.
void printItem( int val )
{
  if ( val < 0 )
    printf( "(%d) ", -val );
  else
    printf( "%d ", val );
}

void printList( int *list, int len, void (*fp)(int val)
                // ...
                )
{
    while (len) {
        fp(*list);
        list++;
        len--;
    }
    printf("\n");
    // Print each item using a provided function pointer.
  // ...
}

int main()
{
  // An array of a bunch of 10-element lists.
  int listOfLists1[][ 10 ] = {
    { 300, 26, 804, 559, 315, 623, 611, 648, -26, 265 },
    { 369, -622, -821, 224, 295, 276, 238, -99, -46, 465 },
    { -830, -725, 675, 990, -33, -815, 229, -751, 748, 190 },
    { -232, -290, -65, 277, 13, -915, -912, -929, 932, 982 },
    { 259, -547, -975, -638, 230, 310, -800, -583, -510, 800 },
    { 940, 631, -940, 645, -811, -669, -940, -333, -27, 940 }
  };

  // An array of pointers, each pointing to a different list
  int *listOfLists2[] = {
    (int []) { 563, 315, -853, -958, 720, -837, -162, 541, 739, -392 },
    (int []) { -431, 924, 32, -150, -414, -749, 86, -283, 35, -472 },
    (int []) { -672, 381, -371, 874, 682, -561, -229, 23, -194, 196 },
    (int []) { 441, 181, 903, -193, 327, 45, -993, 68, 599, -446 },
    (int []) { 546, 920, -806, -646, -751, -75, 644, -690, -125, 328 }
  };

  // Sort then print each list of lists.  These representations are different, but
  // we can use them both as if they are an array int arrays.

  // For the first, we're getting to each inner array by indexing
  // into a rectangular 2D array.

  for ( int i = 0; i < sizeof( listOfLists1 ) / sizeof( listOfLists1[ 0 ] ); i++ ) {
    sortList( listOfLists1[ i ], 10 );
    printList( listOfLists1[ i ], 10, printItem );
  }

  printf( "\n" );

  // For the second, we're getting to each inner array by looking up a pointer
  // in an array of pointers.

  for ( int i = 0; i < sizeof( listOfLists2 ) / sizeof( listOfLists2[ 0 ] ); i++ ) {
    sortList( listOfLists2[ i ], 10 );
    printList( listOfLists2[ i ], 10, printItem );
  }
}                                                                                                   
