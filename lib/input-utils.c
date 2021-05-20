#include <stdio.h>
#include <string.h>
#include "./input-utils.h"

// ***Yoinked from class demo on validating string input***

// clear stdin buffer
void clear_to_newline() {
    int c;
    while((c = getchar()) != '\n');
}

// improved fgets that applies buffer handling
void fgets_str_stdin(char *dest, size_t max) {
    fgets(dest, max, stdin);

    // Look for the newest newline in the read data
    char *first_newline = strchr(dest, '\n');

    if(first_newline == NULL) {
        // clear buffer
        clear_to_newline();
    }
    else {
        // change \n to \0
        *first_newline = '\0';
    }
}
