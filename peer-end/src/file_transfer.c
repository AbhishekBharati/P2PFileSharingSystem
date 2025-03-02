#include "file_transfer.h"

int send_file(int socket, const char *filename){
  FILE *file = fopen(filename, "rb"); // Open file in binary Mode
  if (file == NULL) {
        perror("🛑 Error Opening File");
        return -1;
    } 

  struct stat file_stat;
  if(stat(filename, &file_stat) < 0){
    perror("Error getting the file size");
    fclose(file);
    return -1;
  }

  long file_size = file_stat.st_size;

  // Sending the fileSize to the receiver First :-
  send(socket, &file_size, sizeof(file_size), 0);

  char buffer[1024];
  size_t bytes_read;

  while((bytes_read = fread(buffer, 1, CHUNK_SIZE, file)) > 0){
    if(send(socket, buffer, bytes_read, 0) < 0){
      perror("Error Sending the file");
      fclose(file);
      return -1;
    }
  }

  fclose(file);
  printf("File %s sent successfully!\n", filename);
  return 0;
}

int receive_file(int socket, const char *destination_filename){
  FILE *file = fopen(destination_filename, "wb"); // Open file in binary Mode
  if(file == NULL){
    perror("Error Creating File");
    return -1;
  }

  long file_size;
  recv(socket, &file_size, sizeof(file_size), 0);
  printf("Receiving File... Expected Size : %ld bytes \n", file_size);

  char buffer[CHUNK_SIZE];
  long total_received = 0;
  ssize_t bytes_received;


  // Receive File in Chunks :-
  while(total_received < file_size) {
    bytes_received = recv(socket, buffer, CHUNK_SIZE, 0);
    
    if(bytes_received == 0){
      printf("Connection closed by sender File Transfer Complete... \n");
      break;
    }

    if(bytes_received < 0){
      perror("Error Receiving File...");
      fclose(file);
      return -1;
    }

    fwrite(buffer, 1, bytes_received, file);
    total_received += bytes_received;
    printf("Received %ld/%ld bytes...", total_received, file_size);
  }

  fclose(file);
  printf("File received successfully! \n");
  return 0;
}
