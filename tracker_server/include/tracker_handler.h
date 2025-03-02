#ifndef TRACKER_HANDLER_H
#define TRACKER_HANDLER_H

#include <netinet/in.h>

void register_peer(const char *name, const char *ip, int port);
void unregister_peer(const char *ip, int port);
void get_peer_list(char *buffer, int buffer_size);

#endif
