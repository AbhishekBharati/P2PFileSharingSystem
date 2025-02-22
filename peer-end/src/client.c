#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "network.h"

int main(){
  int port = 8080; // Using this port for communication.
  const char *server_ip = "127.0.0.1"; // LocalHost for testing.

  // Connect to server 
  int sockFd = connect_to_peer(server_ip, port);

  printf("Connected to the server...");

  // Close the Connection
  close(sockFd);
  return 0;
}
