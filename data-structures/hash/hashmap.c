#include <stdio.h>
#include <stdbool.h>

#include "hashmap.h"
#include "hash.h"
#include "datum.h"

struct bucket * init_bucket(){
    struct bucket * b = (struct bucket *)malloc(sizeof(struct bucket));
    b->val  = 0;
    b->key  = 0;
    b->next = 0;
    return(b);
}

void free_bucket(struct bucket * b){
    if(b){
        if(b->next)        
            free_bucket(b->next);
        free(b);
    }
}

struct hashmap * init_hash(){
    struct hashmap * map = (struct hashmap *)malloc(sizeof(struct hashmap));
    map->size = HASH_SIZE;
    map->conflicts = 0;
    map->table = (struct bucket **)malloc(map->size * sizeof(struct bucket *));
    // This is essential: checks for missing keys require NULL if unset
    for(size_t i = 0; i < map->size; i++)
        map->table[i] = NULL;
    return map;
}

void free_hashmap(struct hashmap * map){
    if(map){
        if(map->table){
            for(int i = 0; i < map->size; i++){
                if(map->table[i])
                    free_bucket(map->table[i]);
            }
            free(map->table);
        }
        free(map);
    }
}

void add(struct datum * key, struct datum * data, struct hashmap * map){
    size_t index = hash(key); 
    //bool conflict;
    if(index < map->size){
        struct bucket * b = init_bucket(); 
        b->val = data;
        b->key = key;
        b->next = map->table[index];
        map->table[index] = b;
    } else {
        fprintf(stderr, "Hash key (%lu) is out of bounds\n", index);
        exit(EXIT_FAILURE);
    }
}

struct datum * get(struct datum * key, struct hashmap * map){
    size_t index = hash(key); 
    if(index < map->size){
        struct bucket * b = map->table[index];
        while(true){
            if(!b)
                return NULL;      
            if(key_matches_bucket(key, b)){
                return b->val; 
            }
            b = b->next;
        }
    } else {
        fprintf(stderr, "Something is wrong with the hashing algorithm");
        exit(EXIT_FAILURE);
    }
}

void del(struct datum * key, struct hashmap * map){}

void dump(struct hashmap * map){}
