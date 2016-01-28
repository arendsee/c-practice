#include <stdlib.h>
#include <stdio.h>

int main(){
    size_t n = 4;
    char buffer[n];
    char * readin;
    FILE * stream = fopen("sample.txt", "r");        
    
    // fgets stops when ...
    // 1) the n-1 character is encountered
    fgets(buffer, n, stream);
    printf("print to buffer of size 4: '%s'\n", buffer);

    // 2) a newline is encountered
    //    this will overflow the buffer only if you tell it to
    fgets(buffer, 100, stream);
    printf("print up to newline: '%s'\n", buffer);

    // 3) an EOF is encounrered
    printf("print to end (buffer blocks in <>)\n--------\n");
    while(fgets(buffer, n, stream) != NULL){
        printf("<%s>", buffer); 
    }

    exit(EXIT_SUCCESS); 
}
