#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "registers.h"





int main(int argc, char* argv[]) {
    bool showContent;
    /**
     * read input file
     * user must enter 1 argument, the name of the file they wish to run
     */
    if (argc != 2) {
        printf("Error: expected single .asm file as input\n", argv[1]);
        exit(EXIT_FAILURE);
    } else {
        printf("Opening file...\n");
        FILE *file = fopen(argv[1], "r");                                                   // file ptr
        // attempt to open file - if failed, end program
        if (file == NULL) {
            printf("Error: file %s was not found or couldn't be opened\n", argv[1]);
            exit(EXIT_FAILURE);
        } else {
            printf("File %s successfully opened.\n", argv[1]);
        }
    }

    // parse file
    char line[256];                                                                         // buffer




    return 0;
}
