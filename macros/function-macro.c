#include <stdio.h>

#define bad_square(x) (x*x)
#define good_square(x) ((x)*(x))

int main(){
    printf("5 square is %d\n", bad_square(5));
    printf("5 square twice is %d\n", bad_square(bad_square(5)));

    printf("4+1 square is %d?\n", bad_square(4+1));
    printf("This goes to: '4+1 * 4+1 = 9', we want: '(4+1)*(4+1)=%d'\n", good_square(4+1));

    return(0);
}
