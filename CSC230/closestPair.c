// Programming exercise working with arrays of strcuts.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define PT_LIMIT 100

// Representation for a point, a location along with a name.
struct Point {
  char name[ 16 ];
  int x, y;
};

// Read a list of points from standard input, starting with the number of points
// then name x y for each point.
// Return the number of points.
int readPoints( struct Point ptList[] )
{
  int len;
  scanf( "%d", &len );

  // Add code to read the given number of points into pList.
  // Be sure to prevent buffer overflow in the point list and in
  // the name of each point.
  // ...
  for (int i = 0 ; i < len; i++){
    scanf("%s %d %d\n",ptList[i].name, &ptList[i].x, &ptList[i].y);
  }

  return len;
}

// Representation for a pair of integers,
// used as the return value of findNearest.
struct Pair {
  int a, b;
};

// A function to compute the distance between two points
// We're using pass-by-value here, but pass by reference
// would be more efficient.
double distance( struct Point p1, struct Point p2 )
{
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return sqrt( dx * dx + dy * dy );
}

// Check all pairs of points, find the closest two and return
// their indices in an instance of struct Pair.  On a tie, any pair
// of equally close points is OK.
// There are more efficient ways to do this.
struct Pair findNearest( struct Point ptList[], int len )
{
  // See, this is what we're talking about with assert, it's
  // for checking things that had better be true.
  assert( len > 2 );

  // Storage for the closest two points found so far.
  int bestA = 0, bestB = 1;

  for ( int a = 0; a < len; a++ )
    for ( int b = a + 1; b < len; b++ )
      // Add code to compare the distance between points a and b
      // with the distance beteen the best pair found so far.
      if ((distance(ptList[a], ptList[b])) < (distance(ptList[bestA],ptList[bestB]))) {
        bestA = a;
        bestB = b;
      }

  // Return a pair holding the indices of the two closest points.
      struct Pair pair = {.a = bestA, .b = bestB};
  return pair ;
}


int main()
{
  // A list of points.
  struct Point ptList[ PT_LIMIT ];

  // Read all the points
  int len = readPoints( ptList );

  // find the closest pair.
  struct Pair pair = findNearest( ptList, len );
  
  // Report it.
  printf( "%s and %s are closest\n", ptList[ pair.a ].name, ptList[ pair.b ].name );

  return 0;
}
