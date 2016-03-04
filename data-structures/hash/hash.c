#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "datum.h"

byte xor_all(struct datum * d, byte hash){
    byte * v = (byte *) d->data;
    hash = 0;
    for(int i = 0; i < d->size; i++){
        hash ^= v[i];
    }
    return(hash); 
}

ushort swap(ushort x, size_t a, size_t b){
    size_t size = sizeof(ushort);
    if(a < b){
        size_t tmp = a;
        a = b;
        b = tmp; 
    }
    if(a >= size || b >= size){
        fprintf(stderr, "Swap positions must be between 0 and size - 1\n");
        exit(1);
    }
    if(a == b)
        return x;
    return (x & (1 << a)) >> (a - b) |
           (x & (1 << b)) << (a - b) | x;
}

ushort hash(struct datum * key){
    ushort * k = (ushort *) key->data;
    ushort hash;
    size_t size = key->size;
    size_t pad_length = size % sizeof(ushort);
    int give_me_freedom = 0;
    // If the input is not a multiple of the hash block size pad with 0s
    if(pad_length != 0){
        size += pad_length;
        k = (ushort *)realloc(k, size * sizeof(ushort));
        for(int i = size - pad_length; i < size; i++){
            k[i] = 0;
        }
        give_me_freedom++;
    }
    hash = SALT;
    for(int i = 0; i < size; i++){
        hash ^= k[i] << sizeof(byte);
        hash ^= k[i] >> sizeof(byte);
        hash ^= k[size - i - 1];
    }
    if(give_me_freedom)
        free(k);
    return hash; 
}
