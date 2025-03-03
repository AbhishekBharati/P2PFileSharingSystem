#include <stdio.h>
#include <stdlib.h>
#include "tracker_client.h"
#include "network.h"
#include "file_transfer.h"

void run_server(int port) {
    int server_sock = initialize_network();
    bind_socket(server_sock, port);
    start_listening(server_sock);

    printf("🔵 Server Mode: Waiting for a client...\n");

    int client_sock = accept_connection(server_sock);
    if (client_sock < 0) {
        perror("❌ Error Accepting the connection...");
        return;
    }

    char save_filename[256];
    printf("Enter the filename to save as: ");
    scanf("%255s", save_filename);

    printf("📥 Receiving file and saving as: %s\n", save_filename);
    receive_file(client_sock, save_filename);

    close(client_sock);
    close(server_sock);
}

void run_client() {
    char server_ip[INET_ADDRSTRLEN];
    int port;

    printf("Enter the peer IP to connect to: ");
    scanf("%s", server_ip);

    printf("Enter the peer port to connect to: ");
    scanf("%d", &port);


    int sockFd = connect_to_peer(server_ip, port);
    if (sockFd < 0) {
    printf("Code Broke");
        perror("❌ Error Connecting to the peer...");
        return;
    }

    char fileName[256];
    printf("Enter the filename to send: ");
    scanf("%255s", fileName);

    printf("📤 Sending file: %s\n", fileName);
    send_file(sockFd, fileName);

    close(sockFd);
}

int main() {
    char tracker_ip[INET_ADDRSTRLEN];
    int tracker_port;
    int peer_port;
    char peer_name[50];

    printf("Enter Tracker IP: ");
    scanf("%s", tracker_ip);
    
    printf("Enter Tracker Port: ");
    scanf("%d", &tracker_port);

    printf("Enter Your Peer Name: ");
    scanf("%s", peer_name);

    printf("Enter Your Listening Port: ");
    scanf("%d", &peer_port);

    // Register the peer with the tracker
    register_with_tracker(tracker_ip, tracker_port, peer_name, peer_port);

    // Main menu after registration
    int choice;
    while (1) {
        printf("\n============================\n");
        printf("  📡 P2P File Sharing System  \n");
        printf("============================\n");
        printf("1️⃣ Start as Server (Receive File)\n");
        printf("2️⃣ Start as Client (Send File)\n");
        printf("3️⃣ Get List of Peers\n");
        printf("4️⃣ Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            run_server(peer_port);
        } 
        else if (choice == 2) {
            run_client();
        } 
        else if (choice == 3) {
            request_peer_list(tracker_ip, tracker_port);
        } 
        else if (choice == 4) {
            printf("🔴 Exiting...\n");
            break;
        } 
        else {
            printf("❌ Invalid choice! Please enter 1, 2, 3, or 4.\n");
        }
    }

    return 0;
}

