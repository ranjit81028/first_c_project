
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source>... <destination>\n", argv[0]);
        return 1;
    }

    int ft = open(argv[argc - 1],
                  O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (ft == -1) {
        perror(argv[argc - 1]);
        return 1;
    }

    int status = 0;

    for (int i = 1; i < argc - 1; i++) {
        int fd = open(argv[i], O_RDONLY);

        if (fd == -1) {
            perror(argv[i]);
            status = 1;
            continue;
        }

        char buffer[4096];
        ssize_t n;

        while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
            ssize_t written = 0;

            while (written < n) {
                ssize_t w = write(ft, buffer + written,
                                  (size_t)(n - written));

                if (w == -1) {
                    perror("write");
                    status = 1;
                    break;
                }

                written += w;
            }

            if (status != 0) {
                break;
            }
        }

        if (n == -1) {
            perror(argv[i]);
            status = 1;
        }

        if (close(fd) == -1) {
            perror(argv[i]);
            status = 1;
        }

        if (status != 0) {
            break;
        }
    }

    if (close(ft) == -1) {
        perror(argv[argc - 1]);
        status = 1;
    }

    return status;
}
