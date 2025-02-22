#ifndef NETWORK_H
#define NETWORK_H

// Function declarations for networking :-
int initialize_network(); // Init Network Socket.
int bind_socket(int sockFd, int port); // Bind Socket to a Port.
int start_listening(int sockFd); // Start Listening for incoming Connections.
int accept_connection(int sockFd); // Accept incoming peer connecctions.
int connect_to_peer(const char *ip, int port); // Connect to another Peer.

#endif
