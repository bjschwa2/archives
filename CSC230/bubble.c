// Code to read numbers from standard input into a linked
// list, then sort them, then print them out.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node for building our linked list.
struct NodeTag {
  // Value in this node.
  int value;

  // Pointer to the next node.
  struct NodeTag *next;
};

// A short type name to use for a node.
typedef struct NodeTag Node;

/*
  Read numbers from standard input until we hit the end-of-file,
  putting the numbers in the list pointed to by head.  The head
  pointer is passed by reference.
*/
void readNumbers( Node **head )
{
  Node **tail = head;

  int x;
  while ( scanf( "%d", &x ) == 1 ){
    // Make a node for value x and add it to the list.
    // ...
    Node *n = (Node *)malloc( sizeof( Node ) );
    n->value = x;
    n->next = *tail;
    *tail = n;
  }
}

/*
  Bubble sort the list.
*/
void bubbleSort( Node **head )
{
  bool sorted = false;

  while ( !sorted ) {
    // Assume it's sorted until we see a swap.
    sorted = true;

    // Traverse the list, swapping consecutive nodes that are out of order.
    // Set sorted to false if you find any that are out of order (so we'll
    // keep taking passes through the list until it's in sorted order).
    // ...
    for ( Node *n = *head; n->next != NULL; n = n->next ){
      if(n->next->value < n->value) {
        int temp = n->next->value;
        n->next->value = n->value;
        n->value = temp;
        sorted = false;

      }
    }

  }
}

int main()
{
  // Pointer to the head node.
  Node *head = NULL;

  // Read a list of numbers from standard input.
  readNumbers( &head );

  // Sort them
  bubbleSort( &head );

  // Print all the items on the list.
  // ...
  for ( Node *n = head; n; n = n->next )
    printf( "%d ", n->value );
  printf( "\n" );

  // Free all the nodes.
  while ( head ) {
    Node *n = head;
    head = head->next;
    free( n );
  }

  return 0;
  }