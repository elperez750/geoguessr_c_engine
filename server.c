
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>



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

    // File descriptor
    int client_fd = accept(server_fd, NULL, NULL);


    printf("client file descriptor %d\n", client_fd);

    char buffer[1024];

    // Pulls data from client_fd into buffer. This will read up to 1023 bytes (saves room for null terminator)
    int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    printf("Asked for up to %zu bytes, got %d bytes\n", sizeof(buffer) - 1, bytes_read);
    buffer[bytes_read] = '\0';
    printf("Data: %s\n", buffer);

  
    close(client_fd);
    close(server_fd);


}
