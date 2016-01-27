#include <stdio.h>

int main(){
    int arr[] = {1, 2, 3};
    printf("iterating through an array via addition to the pointer\n");
    printf("%x %d\n", &arr[0], *(arr+0));
    printf("%x %d\n", &arr[1], *(arr+1));
    printf("%x %d\n\n", &arr[2], *(arr+2));

    // Addition is always in multiples of the size
    printf("arithemtic with an int array\n");
    printf("%d + 1 = %d\n", arr, arr+1);
    printf("%d - 1 = %d\n\n", arr, arr-1);

    // arithmetic with a void pointer
    void * a;
    printf("unitialized void pointer:\n   %d + 1 = %d\n\n", a, a+1);

    // arithmetic with an uninitialized pointer
    int * b;
    printf("uninitialized int pointer:\n   %d + 1 = %d\n\n", b, b+1);

    // adding to a void pointer increases it by 1
    a = (void *) b;
    printf("void pointer:\n   %d + 1 = %d\n", a, a+1);
}
