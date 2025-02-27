#include "file_transfer.h"

int send_file(int socket, const char *filename){
  FILE *file = fopen(filename, "rb"); // Open file in binary Mode
  if (file == NULL) {
        perror("🛑 Error Opening File");
        return -1;
    } 

  char buffer[CHUNK_SIZE];
  size_t bytes_read;

  while((bytes_read = fread(buffer, 1, CHUNK_SIZE, file)) > 0){
    printf("📝 Sending chunk (%ld bytes):\n%.*s\n", bytes_read, (int)bytes_read, buffer);
    printf("📝 fread() read %ld bytes before sending.\n", bytes_read);


    if(send(socket, buffer, bytes_read, 0) < 0){
      perror("Error Sending the file");
      fclose(file);
      return -1;
    }
  }

  // Send EOF signal to indicate end of the transfer :-
  send(socket, "EOF", 3, 0);

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

  char buffer[CHUNK_SIZE];
  ssize_t bytes_received;

  // Receive File in Chunks :-
  while(1) {
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

      buffer[bytes_received] = '\0';  // Null-terminate for debugging
      printf("📝 Received chunk (%ld bytes):\n%.*s\n", bytes_received, (int)bytes_received, buffer);


    // Check the EOF Signal :-
    if(bytes_received == 3 && strncmp(buffer, "EOF", 3) == 0){
      break;
    }

    fwrite(buffer, 1, bytes_received, file);
  }

  fclose(file);
  printf("File received successfully! \n");
  return 0;
}
