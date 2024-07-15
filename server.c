

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "server.h"

#define APP_MAX_BUFFER 1024

void handle_client(int client_fd) {
    char buffer[APP_MAX_BUFFER] = {0};
    read(client_fd, buffer, APP_MAX_BUFFER);

    printf("Received Request:\n%s\n", buffer);

    char method[16], path[256];
    sscanf(buffer, "%s %s", method, path);

    if (strcmp(method, "GET") == 0) {
        if (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0) {

            char *http_response = "HTTP/1.1 200 OK\n"
                                  "Content-Type: text/html\n"
                                  "\n"
                                  "<html><body><h1>Hello, World!</h1></body></html>\n";
            write(client_fd, http_response, strlen(http_response));
        } else {
 
            char *http_response = "HTTP/1.1 404 Not Found\n"
                                  "Content-Type: text/plain\n"
                                  "\n"
                                  "404 Not Found\n";
            write(client_fd, http_response, strlen(http_response));
        }
    } else if (strcmp(method, "POST") == 0) {

        char *content_length_header = strstr(buffer, "Content-Length:");
        int content_length = 0;
        if (content_length_header) {
            sscanf(content_length_header, "Content-Length: %d", &content_length);
        }


        char *body_start = strstr(buffer, "\r\n\r\n");
        if (body_start) {
            body_start += 4; 
            int body_len = strlen(body_start);

            if (body_len < content_length) {

                int bytes_to_read = content_length - body_len;
                read(client_fd, body_start + body_len, bytes_to_read);
            }

            char http_response[APP_MAX_BUFFER];
            snprintf(http_response, sizeof(http_response), "HTTP/1.1 200 OK\n"
                                                            "Content-Type: text/plain\n"
                                                            "\n"
                                                            "Received POST data: %s\n", body_start);

            write(client_fd, http_response, strlen(http_response));
        }
    } else {

        char *http_response = "HTTP/1.1 501 Not Implemented\n"
                              "Content-Type: text/plain\n"
                              "\n"
                              "501 Not Implemented\n";
        write(client_fd, http_response, strlen(http_response));
    }

    close(client_fd);
}
