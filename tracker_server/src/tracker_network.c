#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "tracker_handler.h"

#define TRACKER_PORT 9000 // Default Port of the tracker.
#define BUFFER_SIZE 1024

void get_private_ip(char *ip_buffer) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("❌ Error creating socket");
        strcpy(ip_buffer, "127.0.0.1");  // Fallback if we can't detect IP
        return;
    }

    struct sockaddr_in test_addr;
    test_addr.sin_family = AF_INET;
    test_addr.sin_port = htons(80);  // Dummy connection to external IP
    inet_pton(AF_INET, "8.8.8.8", &test_addr.sin_addr);  // Google DNS

    // Try to connect (not actually sending data)
    connect(sock, (struct sockaddr *)&test_addr, sizeof(test_addr));

    // Get assigned IP
    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);
    getsockname(sock, (struct sockaddr *)&local_addr, &addr_len);

    inet_ntop(AF_INET, &local_addr.sin_addr, ip_buffer, INET_ADDRSTRLEN);
    close(sock);
}

void *handle_client(void *arg){
  int client_sock = *(int *)arg;
  free(arg);
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);

  recv(client_sock, buffer, BUFFER_SIZE, 0);
  printf("Received Requests :- %s\n", buffer);
  char command[BUFFER_SIZE], name[50], ip[INET_ADDRSTRLEN];
  int port;

  sscanf(buffer, "%s %s %s %d", command, name, ip, &port);

  if(strcmp(command, "REGISTER") == 0){
    register_peer(name, ip, port);
    send(client_sock, "Peer Registered Successfully... \n", 32, 0);
  } else if( strcmp(command, "GET_PEERS") == 0) {
    char peer_list[BUFFER_SIZE];
    get_peer_list(peer_list, BUFFER_SIZE);
    send(client_sock, peer_list, strlen(peer_list), 0);
  } else if(strcmp(command, "UNREGISTER") == 0){
    unregister_peer(ip, port);
    send(client_sock, "Peer Unregistered Successfully... \n", 35, 0);
  } else {
    send(client_sock, "Invalid request. \n", 19, 0);
  }

  close(client_sock);
  return NULL;
}

// Start the Tracker Server :-
void start_tracker_server() {
  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size = sizeof(client_addr);

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(TRACKER_PORT);

  bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  listen(server_sock, 10);

  char private_ip[INET_ADDRSTRLEN];
  get_private_ip(private_ip);

  printf("Tracker Server Started on %s:%d\n", private_ip, TRACKER_PORT);

  while(1){
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    int *new_sock = malloc(sizeof(int));
    *new_sock = client_sock;

    pthread_t thread;
    pthread_create(&thread, NULL, handle_client, new_sock);
    pthread_detach(thread);
  }

  close(server_sock);
}
