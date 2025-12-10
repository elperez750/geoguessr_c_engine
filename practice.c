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
    char line[16] = "Nami";

    char str1[16] = "Elliott";
    char str2[16] = "Perez";

    int length = manual_string_length(line);
    char *string = manual_string_copy(line);

    printf("This is the length: %d\n", length);
    printf("This is the copy string: %s\n", string);


    char *new_char = append_string(str1, str2);

    printf("%s\n", new_char);

    printf("This is the result after strcat: %s\n", str1);
    int other_length = strlen(line);

    printf("%d\n", other_length);

    free(string);
    free(new_char);

    return 1;
}