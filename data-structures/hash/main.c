#include <stdio.h>
#include <stdlib.h>

#include "datum.h"
#include "hashmap.h"
#include "hash.h"

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
    free_hashmap(map);
    return 0;
}
