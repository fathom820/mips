#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "registers.h"
#include "instructions.h"

int main(int argc, char* argv[]) {
    bool showContent = true;
    FILE *file = NULL;

    /**
     * read input file
     * user must enter 1 argument, the name of the file they wish to run
     */
    if (argc != 2) {
        printf("Error: expected single .asm file as input\n", argv[1]);
        exit(EXIT_FAILURE);
    } else {
        printf("Opening file...\n");
        file = fopen(argv[1], "r");                                                         // file ptr

        // attempt to open file - if failed, end program
        if (file == NULL) {
            printf("Error: file %s was not found or couldn't be opened\n", argv[1]);
            exit(EXIT_FAILURE);
        } else {
            printf("File %s successfully opened.\n", argv[1]);
            // continue...
        }
    }

    // parse file
    char line[256];                                                                         // line buffer

    while (fgets(line, sizeof(line), file)) {
        puts(instructions_decode(line));
    }

    return 0;
}
