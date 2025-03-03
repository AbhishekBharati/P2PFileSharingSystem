#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "network.h"
#include "utils.h"

// Function to initialize the network (Creating Socket) :-
int initialize_network(){
  int sockFd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockFd < 0){
    handle_error("Error Creating the Socket : ");
  }
  return sockFd;
}

// Function to bind the socket to a specific Port :-
int bind_socket(int sockFd, int port){
  struct sockaddr_in server_addr;

  // Clear memory and set values :-
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any I.P. Address.
  server_addr.sin_port = htons(port);

  // Binding the socket to the I.P. Address and Port
  if(bind(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
    handle_error("Error binding Socket");
  }
  return 0;
}

// Function to listen for incoming connections from other peers :-
int start_listening(int sockFd){
  if(listen(sockFd, 5) < 0){
    handle_error("Error Listening for connections");
  }
  printf("Server is Listening for incoming connections... \n");
  return 0;
}

// Function to accept incoming client connections :-
int accept_connection(int sockFd){
  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  int new_sock = accept(sockFd, (struct sockaddr *)&client_addr, &client_len);
  if(new_sock < 0){
    handle_error("Error Accepting Connection");
  }
  printf("New Connection Established \n");
  return new_sock;
}

// Function to connect to another peer (client-side)
int connect_to_peer(const char *ip, int port){
  int sockFd = initialize_network(); // Init Socket
  struct sockaddr_in peer_addr;

  memset(&peer_addr, 0, sizeof(peer_addr));
  peer_addr.sin_family = AF_INET;
  peer_addr.sin_port = htons(port);

  if(inet_pton(AF_INET, ip, &peer_addr.sin_addr) <= 0){
    handle_error("Invalid IP Address");
  }

  // Connect to Peer :-
  if(connect(sockFd, (struct sockaddr *)&peer_addr, sizeof(peer_addr)) < 0){
    perror("Connection Failed...\n");
    return -1;
  }
  printf("Connected to the peer %s : %d\n", ip, port);
  return sockFd;
}
