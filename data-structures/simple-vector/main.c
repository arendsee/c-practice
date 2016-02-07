#include <stdio.h>

#include "ivector.h"

int main(void){
    ivector * a = ivector_init(1);
    Interval v1 = {.a = 1, .b = 2};
    Interval v2 = {.a = 4, .b = 5};
    ivector_add(a, v1);
    ivector_add(a, v2);
    printf("v1.a=%d, v2.a=%d\n", a->data[0].a, a->data[1].a);
    ivector_free(a);
}
