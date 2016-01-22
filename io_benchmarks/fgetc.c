#include <stdio.h>

int main(){
    FILE * f = fopen("test.txt", "r");
    char c;
    size_t i = 0;

    /* iterate through a file by printing one character at a time*/
    while((c = fgetc(f)) != EOF){ }
    
    return(0);
}
