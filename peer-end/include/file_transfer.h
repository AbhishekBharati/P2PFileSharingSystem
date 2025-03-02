#ifndef FILE_TRANSFER_H
#define FILE_TRANSFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define CHUNK_SIZE 1024 // 1 KB chunk size

// Function to send a file over a Socket :-
int send_file(int socket, const char *filename);

// Function to receive a file from Socket :-
int receive_file(int socket, const char *destination_filename);

#endif

