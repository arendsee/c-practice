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

    /*
    // Overflow, printing past the length of an array
    for(int i = 0; i < 10000; i++){
        printf("%d\t%x\n", i, b[i]);
    }
    */

    printf("\n");
    char d[] = {'a', 'b', 'c'};
    printf("array d: {%d, %d, %d}\n", d[0], d[1], d[2]);
    // As expected, char only requires 1 byte
    printf("%x, {%x, %x, %x}\n", d, &d[0], &d[1], &d[2]);


    printf("\n");
    int e[3];
    printf("array e: {%x, %x, %x, %x}\n", e[0], e[1], e[2], e[3]);
    printf("%x, {%x, %x, %x}\n", e, &e[0], &e[1], &e[2]);

    return(0);
}
