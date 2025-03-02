#ifndef TRACKER_CLIENT_H
#define TRACKER_CLIENT_H

void register_with_tracker(const char *tracker_ip, int tracker_port, const char *peer_name, int peer_port);
void request_peer_list(const char *tracker_ip, int tracker_port);

#endif
