#include <stdio.h>

int main()  {

    // Simple declation of a constant length variable
    int a[] = {1, 2, 3};
    printf("array a: {%d, %d, %d}\n", a[0], a[1], a[2]);

    // Print addresses
    printf("%x, {%x, %x, %x}\n", a, &a[0], &a[1], &a[2]);

    printf("\n");

    // Dereference with *
    printf("&a[0] -> *&a[0] = a[0]\n");
    printf("%x -> %d = %d\n", &a[0], *&a[0], a[0]);

    int *b = a;
    printf("b=%x, b->%x\n", &b, b);

    printf("\n");
    printf("b[2] = %d\n", b[2]);
    printf("%x, {%x, %x, %x}\n", b, &b[0], &b[1], &b[2]);

    return(0);
}
