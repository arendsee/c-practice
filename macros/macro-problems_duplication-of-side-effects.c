#include <stdio.h>

#define square(x) ((x)*(x))

int main(){
    int x = 4;
    printf("x=4; square(++x) -> %d\n", square(++x));
    return(0);
}
