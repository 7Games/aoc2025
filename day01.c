#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "slh.h"

int dial_position = 50;
int part1_count = 0; // inc every set on 0
int part2_count = 0; // inc every click on 0

void rotate(int rot) {
    for (int i = 0; i < abs(rot); i++) {
        dial_position += (rot / abs(rot));

        if (dial_position == -1) {
            dial_position = 99;
        } else if (dial_position == 100) {
            dial_position = 0;
        }

        if (dial_position == 0) {
            part2_count++;
        }
    }
}

int decode(char* str) {
    int neg = 1;

    switch (tolower(str[0])) {
    case 'r':
        neg = 1;
        break;
    case 'l':
        neg = -1;
        break;
    default:
        fprintf(stderr, "ERROR: Cannot decode rotation direction '%c'", str[0]);
        exit(1);
    }

    return atoi(++str) * neg;
}

int main(void) {
    char* data = read_file("day01.data");
    char* token = strtok(data, "\n");

    printf("Day 01\n");
    printf("-----------------------------\n");

    while (token != NULL) {
        rotate(decode(token));
        printf("%i\n", dial_position);

        if (dial_position == 0) {
            printf("GOT");
            part1_count++;
        }

        token = strtok(NULL, "\n");
    }

    free(data);

    printf("-----------------------------\n");
    printf("Final Dial Position:\t%i\n", dial_position);
    printf("Part 1 Answer:\t\t%i\n", part1_count);
    printf("Part 2 Answer:\t\t%i\n", part2_count);

    return 0;
}
