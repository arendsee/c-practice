#include <stdlib.h>

char * make_str(size_t size){
    char * str = (char*)malloc(size * sizeof(char) + 1);
    return(str);
error:
    if(str) free(str);
}

int main(){
    char * str = make_str(5);
    free(str)
    return 0;
}
