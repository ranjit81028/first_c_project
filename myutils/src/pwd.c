#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int main(void){
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        perror("pwd failed\n");
        exit(1);
    }
    printf("%s\n", cwd);
    return 0;
}