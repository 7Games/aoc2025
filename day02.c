// gcc -o day02 day02.c -Wall -Werror -Wextra -pedantic && ./day02
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "slh.h"

size_t final_num = 0;

bool is_string_valid(const char* str) {
    size_t len = strlen(str);
    size_t hlen = len / 2; // half len

    if (len % 2 == 0) {
        char* left_side = (char*)malloc((hlen + 1) * sizeof(char));
        char* right_side = (char*)malloc((hlen + 1) * sizeof(char));

        snprintf(left_side, hlen + 1, "%s", str);
        snprintf(right_side, len, "%s", str + hlen);

        if (strcmp(left_side, right_side) == 0) {
            return false;
        }

        free(left_side);
        free(right_side);
    }
    // 40214376762
    // 40214376723
    return true;
}

void do_range(size_t start, size_t end) {
    if (start > end) die(1, "error: start cannot be larger than end");

    for (size_t i = start; i <= end; i++) {
        char* str = num_to_string(i, 10);
        if (!is_string_valid(str)) {
            printf("duplicate id\t%s", str);
            final_num += i;
            printf("\t(%zu)\n", final_num);
        }
        free(str);
    }
}

int main(void) {
    char* data = read_file("day02.data");
    char* segment = strtok(data, ",");

    printf("Day 02\n");
    printf("-----------------------------\n");

    while (segment != NULL) {
        size_t left_side = 0;
        size_t right_side = 0;
        char* buffer = (char*)malloc(strlen(segment) * sizeof(char));
        strcpy(buffer, "");

        if (segment[strlen(segment) - 1] == '\n')
            segment[strlen(segment) - 1] = '\0';

        while (strlen(segment) >= 1) {
            if (segment[0] == '-') {
                left_side = atol(buffer);
                strcpy(buffer, "");
            } else {
                strncat(buffer, segment, 1);
            }
            ++segment;
        }

        right_side = atol(buffer);

        printf("=== %zu-%zu ===\n", left_side, right_side);
        do_range(left_side, right_side);

        free(buffer);
        segment = strtok(NULL, ",");
    }

    free(data);

    printf("-----------------------------\n");
    printf("Final ID: %zu\n", final_num);
    return 0;
}
