#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct arguments{
    int files_count;
    char **files;
}arguments;

void parse_arguments(int argc, char **argv, arguments *args){
    args->files = malloc(argc*sizeof(char*));
    int index = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--help") == 0){
            printf("./main<files>[--help]\n");
            exit(0);
        }else{
            args->files[index++] = argv[i];
        }
    }
    args->files_count = index;
}
#define MAX_LEN 128
void read_file(char *path, char **buffer, int ** buffer_size){
    int tmp_capacity = MAX_LEN;
    char *tmp = malloc(tmp_capacity*sizeof(char));
    if(tmp == NULL){
        perror("malloc failed\n");
        exit(1);
    }
    int tmp_size = 0;
    FILE *f = fopen(path, "r");
    if (f == NULL) {
    perror("fopen failed");
    free(tmp);
    exit(1);
}
    int size = 0;
    do{
        if(tmp_size + MAX_LEN > tmp_capacity){
            tmp_capacity *= 2;
            tmp = realloc(tmp,tmp_capacity*sizeof(char));
            if(tmp == NULL){
                perror("realloc failed\n");
                exit(1);
            }
        }
        size = fread(tmp+tmp_size, sizeof(char), MAX_LEN, f);
        tmp_size+=size;

    }while(size > 0);
    fclose(f);
    tmp[tmp_size] = '\0';
    *buffer_size = &tmp_size;
    *buffer = tmp;
}
int main(int argc, char **argv){
    arguments args = {0};
    parse_arguments(argc, argv, &args);
    printf("%d\n", args.files_count);
    char* buffer = NULL;
    int* buffer_size = NULL;
    read_file("main.c", &buffer, &buffer_size);
    printf("%s\n", buffer);
    printf("%d\n", *buffer_size);
    free(buffer);
    return 0;
}