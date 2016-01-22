#include <stdio.h>
#include <stdlib.h>

int main(void) {
    float  a = 97.1; 
    double b = 97.1;

    printf("%d %d\n", sizeof(a), sizeof(b));

    printf("%f %e\n", a, b);

    // If the type doesn't match the format, your memory can get corrupted
    // Here I am trying to type (on my system) 8 bytes (double) into a 4 byte (float) position.
    printf("%f %e\n", b, a);

    // Adding the gcc or cc option -WFormat warns of this behavior.

    exit(EXIT_SUCCESS);
}
