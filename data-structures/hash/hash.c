#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

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

void print_binary(void * data, size_t size){
    byte * v = (byte *) data;
    for(int i = size - 1; i > -1; i--){
        for(byte mask = 128; mask != 0; mask >>= 1){
            printf("%d", v[i] & mask ? 1 : 0);
        }
        printf(" ");
    }
    printf("\n");
}

byte xor_all(void * data, size_t size, byte hash){
    byte * v = (byte *) data;
    hash = 0;
    for(int i = 0; i < size; i++){
        hash ^= v[i];
    }
    return(hash); 
}

ushort hash(void * key, size_t size){
    ushort * k = (ushort *) key;
    ushort hash = SALT;
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
    for(int i = 0; i < size; i++){
        hash ^= k[i] << sizeof(byte);
        hash ^= k[i] >> sizeof(byte);
        hash ^= k[size - i - 1];
    }
    if(give_me_freedom)
        free(k);
    return hash; 
}

int main(int argc, char * argv[]){
    int r;
    int n = 10;
    if(argc > 1)
        srand(atoi(argv[1]));
    if(argc > 2)
        n = atoi(argv[2]);
    for(int i = 0; i < n; i++){
        r = rand();
        printf("%d\n", hash(&r, sizeof(int)));
    }
    return 0;
}
