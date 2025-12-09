#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    char *method;
    char *path;
    char *version;
} RequestLine;



RequestLine* parse_request_line(char *request) {
    char method[20];
    char path[256];
    char version[20];

    RequestLine *details = malloc(sizeof(RequestLine));
    int items_assigned = sscanf(request, "%19s %255s %19s", method, path, version);
    if (items_assigned >= 3) {
        details->method = strdup(method);
        details->path = strdup(path);
        details->version = strdup(version);
    }

    return details;





    
}


int main() {
    char request1[] = "GET /index.html HTTP/1.1";
    RequestLine *parsed1 = parse_request_line(request1);
    printf("Method: %s\n", parsed1->method);   // GET
    printf("Path: %s\n", parsed1->path);       // /index.html
    printf("Version: %s\n", parsed1->version); // HTTP/1.1

    char request2[] = "POST /api/users HTTP/1.1";
    RequestLine *parsed2 = parse_request_line(request2);
    printf("Method: %s\n", parsed2->method);   // POST
    printf("Path: %s\n", parsed2->path);       // /api/users
    printf("Version: %s\n", parsed2->version); // HTTP/1.1

    // Don't forget to free!
    free(parsed1->method);
    free(parsed1->path);
    free(parsed1->version);
    free(parsed1);
    // Same for parsed2
    free(parsed2->method);
    free(parsed2->path);
    free(parsed2->version);
    free(parsed2);

    return 1;
}