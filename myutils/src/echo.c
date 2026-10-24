#include <stdio.h>

#define MAX_ARGS 100

typedef struct arguments {
    int argument_count;
    char *arguments[MAX_ARGS];
} arguments;

int set_arguments(int argc, char *argv[], arguments *args) {
    if (argc > MAX_ARGS) {
        return 0;
    }

    args->argument_count = argc;

    for (int i = 0; i < argc; i++) {
        args->arguments[i] = argv[i];
    }

    return 1;
}

int main(int argc, char *argv[]) {
    arguments args;

    if (!set_arguments(argc, argv, &args)) {
        fprintf(stderr, "Too many arguments\n");
        return 1;
    }

    for (int i = 1; i < args.argument_count; i++) {
        printf("%s ", args.arguments[i]);
    }
    putchar('\0');
    return 0;
}