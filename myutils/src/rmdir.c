#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc == 1){
        fprintf(stderr, "Usage: %s <directory>...\n", argv[0]);
        return 1;
    }
    int status = 0;
    for(int i = 1; i < argc; i++){
        int res = rmdir(argv[i]);
        if(res == -1){
            perror(argv[i]);
            status  = 1;
        }
    }
    return status;
}