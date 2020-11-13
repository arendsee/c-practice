// read a command and print all results

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char * argv[]){
    FILE *read_fp;
    int chars_read;
    char buffer[BUFFER_SIZE + 1]; // +1 so that the string is always NULL terminated
    memset(buffer, '\0', sizeof(buffer));

    printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);

    /* // open a command that writes to STDOUT, but does not read from STDIN */
    /* read_fp = popen("uname -a", "r");                                     */
    read_fp = popen("dmesg", "r");

    printf("Output was: \n", buffer);
    while(read_fp != NULL){
        chars_read = fread(buffer, sizeof(char), BUFFER_SIZE, read_fp);
        buffer[chars_read] = '\0'; // ensure final value is NULL, even if at the end
        if (chars_read > 0){
            printf(buffer);
        } else {
            break;
        }
    }
    pclose(read_fp);
    exit(EXIT_SUCCESS);
}
