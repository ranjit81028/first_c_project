
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

size_t count_lines(FILE *file) {
    size_t lines = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lines++;
        }
    }

    return lines;
}

size_t count_bytes(FILE *file) {
    size_t bytes = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        bytes++;
    }

    return bytes;
}

size_t count_words(FILE *file) {
    size_t words = 0;
    bool in_word = false;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (isspace((unsigned char)c)) {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            words++;
        }
    }

    return words;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <-l|-w|-c> <filename>\n",
                argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-l") != 0 &&
        strcmp(argv[1], "-w") != 0 &&
        strcmp(argv[1], "-c") != 0) {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        return 1;
    }

    FILE *file = fopen(argv[2], "rb");

    if (file == NULL) {
        perror(argv[2]);
        return 1;
    }

    size_t count;

    if (strcmp(argv[1], "-l") == 0) {
        count = count_lines(file);
    } else if (strcmp(argv[1], "-w") == 0) {
        count = count_words(file);
    } else {
        count = count_bytes(file);
    }

    if (ferror(file)) {
        perror("wc: read error");
        fclose(file);
        return 1;
    }

    if (fclose(file) == EOF) {
        perror("wc: close error");
        return 1;
    }

    printf("%zu %s\n", count, argv[2]);

    return 0;
}
