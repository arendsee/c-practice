#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

void add(datum key, datum data, hashmap map){}

void get(datum key, hashmap map){}

void del(datum key, hashmap map){}

void dump(hashmap map){}

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

void print_binary(datum d){
    byte * v = (byte *) d.data;
    for(int i = d.size - 1; i > -1; i--){
        for(byte mask = 128; mask != 0; mask >>= 1){
            printf("%d", v[i] & mask ? 1 : 0);
        }
        printf(" ");
    }
    printf("\n");
}

byte xor_all(datum d, byte hash){
    byte * v = (byte *) d.data;
    hash = 0;
    for(int i = 0; i < d.size; i++){
        hash ^= v[i];
    }
    return(hash); 
}

ushort hash(datum key){
    ushort * k = (ushort *) key.data;
    ushort hash;
    size_t size = key.size;
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

int main(int argc, char * argv[]){
    datum r;
    int val;
    int n = 10;
    if(argc > 1)
        srand(atoi(argv[1]));
    if(argc > 2)
        n = atoi(argv[2]);
    r.size = sizeof(int);
    for(int i = 0; i < n; i++){
        val = rand();
        r.data = &val;
        printf("%d\n", hash(r));
    }
    return 0;
}
