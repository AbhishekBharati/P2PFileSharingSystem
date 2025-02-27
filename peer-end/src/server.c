#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "network.h"
#include "file_transfer.h"

int main(){
  int port = 8080;
  int sockFd = initialize_network();
  bind_socket(sockFd, port);
  start_listening(sockFd);

  // Accepting a connection from the client
  int client_sock = accept_connection(sockFd);

  printf("Connection established with a client! \n");
  if(client_sock < 0){
    perror("Error Accepting Connection");
    return -1;
  }

  printf("Receiving File From Client...\n");
  receive_file(client_sock, "received_file.txt");

  // Close the Connection
  close(client_sock);
  close(sockFd);
  return 0;
}
