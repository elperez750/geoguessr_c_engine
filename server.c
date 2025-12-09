
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include  <string.h>
#include <stdlib.h> // Include for EXIT_FAILURE


  char* get_header_value(char *request, char *header_name) {
        size_t header_size = strlen(header_name);

        char *line = strstr(request, "\r\n");
        if (!line) return NULL;
        line += 2;

        while (line && *line != '\r') {
            if (strncmp(line, header_name, header_size) == 0) {
                char *colon = strstr(line, ": ");
                if (colon) {
                    return colon + 2;  // Skip ": "
                }

            }
            line = strstr(line, "\r\n");
            if(line)line+=2;

        }
        return NULL;

    }



int main() {
    // Create socket
    //  AF_INET is IPv4
    // SOCK_STREAM is TCP
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Address structure
    /*
    Its like having the following
    typedef struct {
        short sin_family;
        struct in_addr sin_addr
        unsigned short sin_port
    }
    
    */
       
    int opt = 1;
    // This allows the socket to bind even if the port is in TIME_WAIT state.
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

 
    struct sockaddr_in address;
    address.sin_family = AF_INET; // Address family (IPv4 vs IPv6)
    address.sin_addr.s_addr = INADDR_ANY; // IP address
    address.sin_port = htons(8080);  // Port 8080


    /*
    Why htons?
    computer might store 8080 as [31, 144] in memory
    network protocol requires [144, 31] big endian
    */


    // Binding server to address
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // Listen for connections. If four people try to connect simotaneously, the fourth gets rejected
    listen(server_fd, 3);


    while(1) {

        
        // File descriptor
        int client_fd = accept(server_fd, NULL, NULL);


        printf("client file descriptor %d\n", client_fd);

        char buffer[1024];

        // Pulls data from client_fd into buffer. This will read up to 1023 bytes (saves room for null terminator)
        int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        buffer[bytes_read] = '\0';


        
        char method[16];
        char route[256];
        char protocol[16];

        int items_assigned = sscanf(buffer, "%15s %255s %15s", method, route, protocol);
        if (items_assigned >= 2) {
            printf("Method: %s, Route %s, Protocol %s\n", method, route, protocol);
        };

      
        char *host = get_header_value(buffer, "Host");
        if(host) {
            printf("The host was succesfully returned %s\n", host);
        }

        char *user_agent = get_header_value(buffer, "User-Agent");
        if (user_agent) {
            printf("The user agent was succesfully returned! %s\n", user_agent);
        }

        char *success_response = "HTTP/1.1 200 OK\r\n\r\nWelcome";
        char *error_response = "HTTP/1.1 404 Not Found\r\n\r\nFuck you";
        if (strcmp(route, "/") == 0) {
            char *response = "HTTP/1.1 200 OK\r\n\r\nWelcome home!";
            write(client_fd, response, strlen(response));
        } 
        else if (strcmp(route, "/about") == 0) {
            char *response = "HTTP/1.1 200 OK\r\n\r\nThis is my HTTP server in C";
            write(client_fd, response, strlen(response));
        }
        else if (strcmp(route, "/api/data") == 0) {
            char *response = "HTTP/1.1 200 OK\r\n\r\n{\"message\": \"Hello from API\"}";
            write(client_fd, response, strlen(response));
        }
        else {
            write(client_fd, error_response, strlen(error_response));
        
        }

  

       
   
        


        /*
        
        Perfect! Now here's your task:

        **Parse the path from the HTTP request and send the correct response:**

        Right now you're sending `200 OK` for EVERY request. You need to:

        1. Extract the path from the buffer (it's in that first line: `GET /elliott HTTP/1.1`)
        2. Check if the path is `"/"` or something else
        3. Send `"HTTP/1.1 200 OK\r\n\r\n"` if path is `"/"`
        4. Send `"HTTP/1.1 404 Not Found\r\n\r\n"` for any other path

        **Hint:** Remember `sscanf()` I mentioned earlier? You'll need to:
        - Declare a `char path[256];`
        - Use `sscanf()` to extract the path from the buffer
        - Use `strcmp()` to compare it against `"/"`
        - Use an if/else to pick which response to send

        Try implementing this! Test it with:
        ```bash
        curl -v http://localhost:8080/        # Should get 200
        curl -v http://localhost:8080/test    # Should get 404
        ```

        Give it a shot and let me know what you come up with!
        
        */

    
        close(client_fd);
    }



    close(server_fd);


}
