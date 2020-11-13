#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
    FILE *read_fp;
    int chars_read;
    // The `BUFSIZ + 1` number sets the maximum size message we can handle
    // If this is smaller than the length of the message, the message will be truncated
    char buffer[BUFSIZ + 1];
    memset(buffer, '\0', sizeof(buffer));

    printf("BUFSIZ: %d\n", BUFSIZ);

    // open a command that writes to STDOUT, but does not read from STDIN
    read_fp = popen("uname -a", "r");
    if(read_fp != NULL){
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        if (chars_read > 0){
            printf("Output was: \n%s\n", buffer);
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
