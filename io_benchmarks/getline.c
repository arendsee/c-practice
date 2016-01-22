#include <stdlib.h>
#include <stdio.h>

int main(void){
    size_t n = 0;
    char * buffer = NULL;
    FILE * stream = fopen("test.txt", "r");        
    unsigned int i = 0;

    if(stream == 0){
       fprintf(stderr, "Could not read file\n"); 
       exit(EXIT_FAILURE);
    }

    while((getline(&buffer, &n, stream)) != EOF){
        i++;
    }
    printf("%d lines read\n", i);

    exit(EXIT_SUCCESS); 
}
