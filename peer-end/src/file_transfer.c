#include "file_transfer.h"

int send_file(int socket, const char *filename){
  FILE *file = fopen(filename, "rb"); // Open file in binary Mode
  if(file == NULL){
    perror("Error Opening File");
    return -1;
  }

  char buffer[CHUNK_SIZE];
  size_t bytes_read;
}
