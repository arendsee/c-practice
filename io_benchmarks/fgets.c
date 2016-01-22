#include <stdlib.h>
#include <stdio.h>

int main(){
    size_t n = 100;
    char buffer[n];
    FILE * stream = fopen("test.txt", "r");        
    unsigned int i = 0;

    while(fgets(buffer, n, stream) != NULL){
        i++;
    }
    printf("%d lines read\n", i);

    exit(EXIT_SUCCESS); 
}
