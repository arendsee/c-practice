#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// read from STDIN, convert to uppercase
int main(int argc, char * argv[]){
    int ch;
    while((ch = getchar()) != EOF){
        putchar(toupper(ch));
    }
    exit(0);
}
