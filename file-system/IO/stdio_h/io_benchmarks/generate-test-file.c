#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE * out;
    char * line = "aaaaaa aaaaaa aaaaaa aaaaaa aaaaaa aaaaaa\n";
    size_t size = sizeof(char);
    size_t nitems = strlen(line);

    out = fopen("test.txt", "w");
    for(int i = 0; i < 10000000; i++){
        fwrite(line, size, nitems, out);
    }
    exit(EXIT_SUCCESS);
}
