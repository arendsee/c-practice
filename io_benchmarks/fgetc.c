#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * f = fopen("test.txt", "r");
    char c;
    size_t i = 0;
    
    if(f == 0){
       fprintf(stderr, "Could not read file\n"); 
       exit(EXIT_FAILURE);
    }

    /* iterate through a file by printing one character at a time*/
    while((c = fgetc(f)) != EOF){ }
    
    exit(EXIT_SUCCESS);
}
