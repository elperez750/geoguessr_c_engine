#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int manual_string_length(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {

    }

    return i;
}


char* manual_string_copy(char *str) {
    size_t len = strlen(str);
    char *copy_str = malloc(len * sizeof(char));


    if (copy_str == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }


    size_t i;
    for(i=0; i < strlen(str); i++) {
        copy_str[i] = str[i];
    }
    
    copy_str[i] = '\0';

    return copy_str;
}


char *append_string(char *src, char *dest) {
    size_t src_len = strlen(src);
    size_t dest_len = strlen(dest);



    size_t total_length = src_len + dest_len + 2;
    char *new_char = malloc(total_length);

    if (new_char == NULL) {
        perror("Memory could not be allocated");
        return NULL;
    }

    char *current_pos = new_char;


    memcpy(current_pos, src, src_len);

    current_pos += src_len;

    *current_pos = ' ';
    current_pos++;

    strcpy(current_pos, dest);


    
    return new_char;









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