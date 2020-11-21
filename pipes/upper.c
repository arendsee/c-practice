#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// read from STDIN, convert to uppercase
int main(int argc, char * argv[]){
    fprintf(stderr, "  --- IN UPPER CASE ---  \n");
    int ch;
    while((ch = getchar()) != EOF){
        if (ch == '9') {
            // this is a feature, not a bug
            exit(1);
        }
        putchar(toupper(ch));
    }
    exit(0);
}
