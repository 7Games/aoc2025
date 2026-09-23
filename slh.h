#ifndef SLH_H
#define SLH_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: Caller is responsible for freeing returned string
char* read_file(char* file_path) {
    FILE* fp = fopen(file_path, "r");
    char buffer[255];

    char* str = (char*)malloc(255 * sizeof(char));
    size_t str_size = 0;
    size_t str_cap = 255;

    while (fgets(buffer, 255, fp) != 0) {
        size_t len = strlen(buffer);

        if (str_size + len > str_cap) {
            str_cap *= 2;
            str = (char*)realloc(str, str_cap * sizeof(char));
        }

        strncat(str, buffer, len);
        str_size += len;
    }

    fclose(fp);

    return str;
}

#endif // SLH_H
