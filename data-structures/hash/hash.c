#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

void add(struct datum * key, struct datum * data, struct hashmap * map){
    size_t index = hash(key); 
    if(index < map->size){
        struct bin * b = init_bin(); 
        b->data = data;
        b->key = key;
        b->next = map->table[index];
        map->table[index] = b;
    } else {
        fprintf(stderr, "Hash key (%lu) is out of bounds\n", index);
        exit(EXIT_FAILURE);
    }
}

void get(struct datum * key, struct hashmap * map){}

void del(struct datum * key, struct hashmap * map){}

void dump(struct hashmap * map){}

struct bin * init_bin(){
    struct bin * b = (struct bin *)malloc(sizeof(struct bin));
    b->data = 0;
    b->key  = 0;
    b->next = 0;
    return(b);
}

void free_bin(struct bin * b){
    if(b){
        if(b->next)        
            free_bin(b->next);
        free(b);
    }
}

struct hashmap * init_hash(){
    struct hashmap * map = (struct hashmap *)malloc(sizeof(struct hashmap));
    map->size = HASH_SIZE;
    map->conflicts = 0;
    map->table = (struct bin **)malloc(map->size * sizeof(struct bin *));
    memset(map->table, 0, map->size);
    return map;
}

void free_hash(struct hashmap * map){
    if(map){
        if(map->table){
            for(int i = 0; i < map->size; i++){
                if(map->table[i])
                    free_bin(map->table[i]);
            }
            free(map->table);
        }
        free(map);
    }
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

byte xor_all(struct datum * d, byte hash){
    byte * v = (byte *) d->data;
    hash = 0;
    for(int i = 0; i < d->size; i++){
        hash ^= v[i];
    }
    return(hash); 
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

int main(int argc, char * argv[]){
    struct datum key;
    struct datum val;
    struct hashmap * map = init_hash();
    int k;
    int n = 10;
    if(argc > 1)
        srand(atoi(argv[1]));
    if(argc > 2)
        n = atoi(argv[2]);
    key.size = sizeof(int);
    val.size = sizeof(int);
    for(int i = 0; i < n; i++){
        k = rand();
        key.data = &k;
        val.data = &i;
        printf("%d\n", hash(&key));
        add(&key, &val, map);
    }
    return 0;
}
