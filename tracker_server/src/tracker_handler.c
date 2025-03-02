#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "tracker_handler.h"

#define MAX_PEERS 100 // Maximum no. of Peers...

typedef struct {
  char name[50];
  char ip[INET_ADDRSTRLEN];
  int port;
} Peer;

Peer peer_list[MAX_PEERS]; // Store all active Peers.
int peer_count = 0;
pthread_mutex_t peer_mutex = PTHREAD_MUTEX_INITIALIZER;

// Add a new Peer to the List :-
void register_peer(const char *name, const char *ip, int port){
  pthread_mutex_lock(&peer_mutex);

  if(peer_count < MAX_PEERS){
    strcpy(peer_list[peer_count].name, name);
    strcpy(peer_list[peer_count].ip, ip);
    peer_list[peer_count].port = port;
    peer_count++;

    printf("Registered Peer: %s [%s:%d]\n", name, ip, port);
  } else {
    printf("Peer Limit Reached! Cannot register more peers.\n");
  }

  pthread_mutex_unlock(&peer_mutex);
}

void unregister_peer(const char *ip, int port){
  pthread_mutex_lock(&peer_mutex);

  for(int i = 0; i < peer_count; i++){
    if(strcmp(peer_list[i].ip, ip) == 0 && peer_list[i].port == port) {
      printf("Unregistering Peer : %s [%s:%d]\n",peer_list[i].name, ip, port);

      // Shifting remaining Peers Down :-
      for(int j = i; j < peer_count; j++){
        peer_list[j] = peer_list[j+1];
      }
      peer_count--;
      break;
    }
  }

  pthread_mutex_unlock(&peer_mutex);
}

void get_peer_list(char *buffer, int buffer_size){
  pthread_mutex_lock(&peer_mutex);

  snprintf(buffer, buffer_size, "PEERS ");
  for(int i = 0; i < peer_count; i++){
    char peer_info[100];
    snprintf(peer_info, sizeof(peer_info), "%s [%s:%d] ",
             peer_list[i].name, peer_list[i].ip, peer_list[i].port);
    strcat(buffer, peer_info);
  }

  pthread_mutex_unlock(&peer_mutex);
}

