/* Bradley Schwarz
 * Bjschwa2
 * A simple program designed to perform basic bit operators.
 */

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
 * Combine the high-order 9 bits from a with the low-order 7 bits from
 * b and return the result.  (I can do this in one line, but you don't
 * have to.)
 */
unsigned short merge97( unsigned short a, unsigned short b ) {

 unsigned short high = a & 0xff80; 
 unsigned short low =  b & 0x007F;

 return(  high + low );

}

/*
 * Here, you're manipulating a bit field.  Interpret bits 11 through 5
 * in a (with bit 0 being the low-order bit) as a 7-bit unsigned
 * integer value.  Double the value stored in these bits and return
 * the result, leaving the remaining bits unchanged (even if there's
 * overflow when you double the value of this field).
 */
unsigned short field115( unsigned short a ) {

unsigned short val = a & 0x0FE0;

val = val >> 4;

unsigned short newVal = val * 2; 

newVal = newVal & 0x00FE;

newVal = newVal << 4;

unsigned short newA = a & 0XF01F;

return newA | newVal;

}

  int main()
{
  // See what your functions do.

  printf( "%x\n", merge97( 0x3B84, 0x9D72 ) );
  printf( "%x\n", merge97( 0xFFFF, 0xFFFF ) );
  printf( "%x\n", merge97( 0x0000, 0x0000 ) );
  printf( "%x\n", merge97( 0xBA76, 0x35D9 ) );
  printf( "%x\n", merge97( 0x248E, 0x67C5 ) );


  printf( "===========\n" );

  printf( "%x\n", field115( 0x0000 ) );
  printf( "%x\n", field115( 0xFFFF ) );
  printf( "%x\n", field115( 0x0FF0 ) );
  printf( "%x\n", field115( 0x1234 ) );
  printf( "%x\n", field115( 0x5678 ) );
  printf( "%x\n", field115( 0x9ABC ) );
  printf( "%x\n", field115( 0xDEF0 ) );

  // Make sure it does the right thing (this is like a little unit test for
  // your function (covering the same test cases as above).

  assert( merge97(0x3B84, 0x9D72) == 0x3BF2 );
  assert( merge97(0xFFFF, 0xFFFF) == 0xFFFF );
  assert( merge97(0x0000, 0x0000) == 0x0000 );
  assert( merge97(0xBA76, 0x35D9) == 0xBA59 );
  assert( merge97(0x248E, 0x67C5) == 0x24C5 );

  assert( field115(0x0000) == 0x0000 );
  assert( field115(0xFFFF) == 0xFFDF );
  assert( field115(0x0FF0) == 0x0FD0 );
  assert( field115(0x1234) == 0x1454 );
  assert( field115(0x5678) == 0x5CD8 );
  assert( field115(0x9ABC) == 0x955C );
  assert( field115(0xDEF0) == 0xDDD0 );

  return 0;
}