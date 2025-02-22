#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "network.h"

int main(){
  int port = 8080;
  int sockFd = initialize_network();
  bind_socket(sockFd, port);
  start_listening(sockFd);

  // Accepting a connection from the client
  int client_sock = accept_connection(sockFd);

  printf("Connection established with a client! \n");

  // Close the Connection
  close(client_sock);
  close(sockFd);
  return 0;
}
