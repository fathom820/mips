#include <stdio.h>

int main(int argc, char* argv[]) {

    /**
     * read input file
     */
    if (argc != 2) {
        printf("Error: expected single .asm file as input\n found %d\n", argv[1]);
        return 1;
    } else {
        printf("Opening file...\n");
        FILE *file = fopen(argv[1], "r");
        if (file == 0) {
            printf("Error: file %s could not be opened");
        }
    }

    return 0;
}
