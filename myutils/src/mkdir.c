
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    int res = mkdir(argv[1], 0755);

    if (res == -1) {
        perror(argv[1]);
        return 1;
    }

    return 0;
}
