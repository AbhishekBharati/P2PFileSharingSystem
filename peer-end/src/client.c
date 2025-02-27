#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "network.h"
#include "file_transfer.h"

int main(){
  int port = 8080; // Using this port for communication.
  const char *server_ip = "127.0.0.1"; // LocalHost for testing.

  // Connect to server 
  int sockFd = connect_to_peer(server_ip, port);

  if(sockFd < 0){
    perror("Error Connecting to the server");
    return -1;
  }

  printf("Connected to the server...");
  send_file(sockFd, "./test_file.txt");

  // Close the Connection
  close(sockFd);
  return 0;
}
