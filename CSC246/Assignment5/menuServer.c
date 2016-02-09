#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>

/** Port number used by my server */
#define PORT_NUMBER "26044"

// Maximum string length for menu items.
#define NAME_LIMIT 16

// Record for a menu item, including price and the total
// number sold.
struct Item {
  // Name of the item.
  char name[ NAME_LIMIT + 1 ];
  
  // Price of this item.
  double price;

  // Number of this item sold.
  long int sold;
};

// Number of menu items.
int menuSize;

// Pointer to the menu in memory.
struct Item *menu;

//Signal used to catch ctrl c
static bool running = true;

//Global variable for the server socket
int servSock = 0;

//Handles the interrupt for ctrl c 
void intHandler(int error) {
  printf("\n");
  running = false; //Prevents new clients from entering
  for (int i = 0; i < menuSize; i++) { //Prints out the menu and items sold
      printf("%16s %li\n", menu[i].name, menu[i].sold);
  }
  close(servSock); //Close server socket
  exit(0); //Exit from program
}
// Print out an error message and exit.
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

/** Read the menu. */
void readMenu( const char *menuFile ) {
  FILE *fp = fopen( menuFile, "r" );
  if ( fp == NULL )
    fail( "Can't open menu file" );
  
  // Allocate space for the menu.
  if ( fscanf( fp, "%d", &menuSize ) != 1 )
    fail( "Can't read menu length" );
  menu = (struct Item *)malloc( sizeof( struct Item ) * menuSize );

  // Then, read all the items.
  for ( int i = 0; i < menuSize; i++ ) {
    if ( fscanf( fp, "%16s %lfs\n", menu[ i ].name, &menu[ i ].price ) != 2 )
      fail( "Can't read a menu item and price" );
    menu[ i ].sold = 0;
  }

  fclose( fp );
}

/** Allows clients to order an item if it exists
    in the menu. */
double orderItem( char *toOrder) {
  for (int i = 0; i < menuSize ; i++) {
    if (strcmp(toOrder, menu[i].name) == 0) {
      menu[i].sold++;
      return menu[i].price;
    }
  }
  printf("Unknown Menu Item: %s\n", toOrder);
  return 0.0;
}

/** Handle interaction with a client, closing the connection
    when we're done. */
void *handleClient( void* sock ) {
  // Here's a nice trick, wrap a C standard IO FILE around the
  // socket, so we can communicate the same way we would read/write
  // a file.
  int newSock = *((int*)sock);
  FILE *fp = fdopen( newSock, "a+" );
  
  // Item the user asked for.
  char item[ NAME_LIMIT + 1 ];

  //Prints out the menu when a client connects
  for (int i = 0; i < menuSize; i++) {
    fprintf(fp, "%16s %4.2f\n", menu[i].name, menu[i].price);
  }
  double totalOrder = 0.0;
  // Prompt the user for an item:
  while (strcmp(item, "done") != 0) {
    fprintf(fp, "order (or done)> ");
    fscanf(fp, "%s", item);
    if (strcmp(item, "done") == 0) {
      fflush(fp);
      break;
    }
    fflush(fp);
    totalOrder += orderItem(item); //Retrieves the client's order
  }
  fprintf(fp, "Total: %4.2f\n", totalOrder); //Total price of all of what the client ordered
  fflush(fp);
  fclose( fp );
  return NULL;
}

int main( int argc, char *argv[] ) {
  if ( argc != 2 )
    fail( "usage: menuServer <menu_file.txt>" );

  // Read the menu from a file (so we can change it by restarting
  // the server.
  readMenu( argv[ 1 ] );

  // Prepare a description of server address criteria.
  struct addrinfo addrCriteria;
  memset(&addrCriteria, 0, sizeof(addrCriteria));
  addrCriteria.ai_family = AF_INET;
  addrCriteria.ai_flags = AI_PASSIVE;
  addrCriteria.ai_socktype = SOCK_STREAM;
  addrCriteria.ai_protocol = IPPROTO_TCP;

  // Lookup a list of matching addresses
  struct addrinfo *servAddr;
  if ( getaddrinfo( NULL, PORT_NUMBER, &addrCriteria, &servAddr) )
    fail( "Can't get address info" );

  // Try to just use the first one.
  if ( servAddr == NULL )
    fail( "Can't get address" );
  
  
  // Create a TCP socket
    servSock = socket( servAddr->ai_family, servAddr->ai_socktype,
                         servAddr->ai_protocol);
    if ( servSock < 0 )
    fail( "Can't create socket" );
    
  // Bind to the local address
  if ( bind(servSock, servAddr->ai_addr, servAddr->ai_addrlen) != 0 )
    fail( "Can't bind socket" );
  
  // Tell the socket to listen for incoming connections.
  if ( listen( servSock, 5 ) != 0 )
    fail( "Can't listen on socket" );

  // Free address list allocated by getaddrinfo()
  freeaddrinfo(servAddr);

  // Fields for accepting a client connection.
  struct sockaddr_storage clntAddr; // Client address
  socklen_t clntAddrLen = sizeof(clntAddr);
  
  //Signal handler for an interrupt signal
  signal(SIGINT, intHandler);
  while ( running ) {
    // Accept a client connection.
    int sock = accept( servSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
    if ( sock == -1 ) {
      fail( "Can't accept on socket" );
    }
    else { //Create a new thread for the client
      pthread_t client;
    
      if (pthread_create(&client, NULL, handleClient, (void *)&sock) != 0)
        fail("Can't make client thread\n");
    }
  }
  // Never reached .. for now.
  close( servSock );
  
  return 0;
}
