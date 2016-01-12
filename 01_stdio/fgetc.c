#include <stdio.h>

int main(){
    FILE * f = fopen("sample.txt", "r");
    char c;

    /* iterate through a file by printing one character at a time*/
    while(1){
        /* fgetc returns the next byte from a filestream */
        c = fgetc(f);
        if(feof(f))
            break;
        if(ferror(f)){
            printf("Error in reading file\n");
            return(1);
        }

        printf("%c.", c);
    }
    
    return(0);
}
