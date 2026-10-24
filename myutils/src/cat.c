#include <stdio.h>


int main(int argc, char *argv[]) {
    if(argc!=2){
        fprintf(stderr, "usage: %s <filname>\n", argv[0]);
        return 1;
    }    
    FILE *file = fopen(argv[1], "rb");
    if(file == NULL){
        perror(argv[1]);
        return 1;
    }
    char buffer[4096];
    size_t buffer_read = 0;
    while((buffer_read = fread(buffer, 1, sizeof buffer, file)) > 0){
        size_t totol_writen = 0;
        while(totol_writen < buffer_read){
            size_t buffer_written = fwrite(buffer+totol_writen,1,buffer_read-totol_writen,stdout);
            if(buffer_written == 0){
                perror("cat: stdout");
                fclose(file);
                return 1;
            }
            totol_writen+=buffer_read;
        }
    }
    if(ferror(file)){
        perror("cat: read error");
        fclose(file);
        return 1;
    }
    if(fclose(file) == EOF) {
        perror("cat: close error");
        return 1;
    }
    return 0;
}
