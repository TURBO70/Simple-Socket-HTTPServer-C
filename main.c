
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

#define PORT 8080

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int address_len = sizeof(address);


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }


    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

 
    while (1) {
        printf("\nWaiting for a connection...\n");

        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&address_len)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        handle_client(client_fd); 
    }

    return 0;
}
