#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "network.h"

#define BUFFER_SIZE 1024

void get_private_ip(char *ip_buffer){
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock == -1){
    perror("Error Creating Socket...");
    strcpy(ip_buffer, "127.0.0.1");
    return;
  }

  struct sockaddr_in test_addr;
  test_addr.sin_family = AF_INET;
  test_addr.sin_port = htons(80);
  inet_pton(AF_INET, "8.8.8.8", &test_addr.sin_addr);

  connect(sock, (struct sockaddr *)&test_addr, sizeof(test_addr));

  struct sockaddr_in local_addr;
  socklen_t addr_len = sizeof(local_addr);
  getsockname(sock, (struct sockaddr *)&local_addr, &addr_len);

  inet_ntop(AF_INET, &local_addr.sin_addr, ip_buffer, INET_ADDRSTRLEN);
  close(sock);
}

int connect_to_tracker(const char *tracker_ip, int tracker_port){
  int sock = connect_to_peer(tracker_ip, tracker_port);
  if(sock < 0){
    perror("Error connecting to the tracker...");
    return -1;
  }
  return sock;
}

void register_with_tracker(const char *tracker_ip, int tracker_port, const char *peer_name, int peer_port){
  int sock = connect_to_tracker(tracker_ip, tracker_port);
  if(sock < 0) return;

  char private_ip[INET_ADDRSTRLEN];
  get_private_ip(private_ip);

  char request[BUFFER_SIZE];
  snprintf(request, sizeof(request), "REGISTER %s %s %d", peer_name, private_ip, peer_port);

  send(sock, request, strlen(request), 0);
  char response[BUFFER_SIZE];
  recv(sock, response, BUFFER_SIZE, 0);
  printf("Tracker Response : %s \n", response);

  close(sock);
}

void request_peer_list(const char *tracker_ip, int tracker_port){
  int sock = connect_to_tracker(tracker_ip, tracker_port);
  if(sock < 0) return;

  send(sock, "GET_PEERS", 9, 0);
  char response[BUFFER_SIZE];
  recv(sock, response, BUFFER_SIZE, 0);
  printf("Active Peers : \n%s\n", response);

  close(sock);
}
