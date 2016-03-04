#include <stdio.h>

#include "datum.h"
#include "global.h"

void print_binary(struct datum * d){
    byte * v = (byte *) d->data;
    for(int i = d->size - 1; i > -1; i--){
        for(byte mask = 128; mask != 0; mask >>= 1){
            printf("%d", v[i] & mask ? 1 : 0);
        }
        printf(" ");
    }
    printf("\n");
}
