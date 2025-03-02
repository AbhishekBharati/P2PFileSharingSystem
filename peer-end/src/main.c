#include "network.h"
#include "file_transfer.h"

void run_server() {
  int port = 8080;
  int server_sock = initialize_network();
  bind_socket(server_sock, port);
  start_listening(server_sock);

  printf("Server Mode : Waiting For a Client... \n");

  int client_sock = accept_connection(server_sock);
  if(client_sock < 0){
    perror("Error Accepting the connection...");
    return;
  }

  char save_filename[256];
  printf("Enter the filename to Save as :");
  scanf("%255s", save_filename);

  printf("Receiving File and Saving as : %s\n", save_filename);
  receive_file(client_sock, save_filename);

  close(client_sock);
  close(server_sock);
}

void run_client(){
  const char *server_ip = "127.0.0.1";
  int port = 8080;

  int sockFd = connect_to_peer(server_ip, port);
  if(sockFd < 0){
    perror("Error Connecting to the server...");
    return;
  }

  char fileName[256];
  printf("Enter the filename to send : ");
  scanf("%255s", fileName);

  printf("Sending File... :- %s", fileName);
  send_file(sockFd, fileName);

  close(sockFd);
}


int main(){
  int choice;
  while(1){
      printf("\n============================\n");
      printf("  📡 P2P File Sharing System  \n");
      printf("============================\n");
      printf("1️⃣ Start as Server (Receive File)\n");
      printf("2️⃣ Start as Client (Send File)\n");
      printf("3️⃣ Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
    if(choice == 1){
      run_server();
    } else if (choice == 2){
      run_client();
    } else if (choice == 3){
      printf("Exiting...");
      break;
    } else {
      printf("Invalid Choice... Please choose either 1, 2 or 3 \n");
    }
  }
  return 0;
}
