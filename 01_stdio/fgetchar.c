#include <stdio.h>

int main(){
    char c;

    /* get user input */
    printf("press x to exit\n");
    while(c = getchar()){
        if(c == 'x')
            break;
    }
    return(0);
}
