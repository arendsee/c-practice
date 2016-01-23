#include <stdio.h>

#define square(x) ((x)*(x))

int main(){
    printf("5 square is %d\n", square(5));
    printf("5 square twice is %d\n", square(square(5)));
    return(0);
}
