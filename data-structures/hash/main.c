#include <stdio.h>
#include <stdlib.h>

#include "datum.h"
#include "hashmap.h"
#include "hash.h"

int main(int argc, char * argv[]){
    struct hashmap * map = init_hash();
    /* TODO - write more rigorous test
    struct datum key;
    struct datum val;
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
        key.data = &i;
        val.data = &k;
        //printf("%d\n", hash(&key));
        add(&key, &val, map);
    }
    if(argc > 1)
        srand(atoi(argv[1]));
    for(int i = 0; i < n; i++){
        k = rand() + (i % 5 == 0);
        key.data = &i;
        val.data = &k;
        del(&key, map);
    }
    */
    free_hashmap(map);
    return 0;
}
