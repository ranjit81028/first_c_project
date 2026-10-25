
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <filename>...\n", argv[0]);
        return 1;
    }

    int status = 0;

    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_WRONLY | O_CREAT, 0644);

        if (fd == -1) {
            perror(argv[i]);
            status = 1;
        } else {
            if (close(fd) == -1) {
                perror(argv[i]);
                status = 1;
            }
        }
    }

    return status;
}
