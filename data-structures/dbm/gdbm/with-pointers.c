/* How do pointers work inside a gdbm database?  */

// This code is totally broken

#include <stdio.h>
#include <stdlib.h>
#include <gdbm.h>
#include <assert.h>

#define SIZE 3

struct Pair {
    int index;
    char hand;
    struct Pair * other;
};

struct Pair * create_Pair(int index){
    struct Pair * left  = malloc(sizeof(struct Pair));
    struct Pair * right = malloc(sizeof(struct Pair));

    left->index = index;
    left->hand = 'L';
    left->other = right;

    right->index = index;
    right->hand = 'R';
    right->other = left;

    return left;
}

void free_Pair(struct Pair * pair){
    free(pair->other);
    free(pair);
}

void print_Pair(struct Pair * pair){
    printf("Printing pair (%d, %d)\n", pair->index, pair->other->index);
    printf("  %c %c\n", pair->hand, pair->other->hand);
    printf("  %lx %lx\n", (unsigned long)pair, (unsigned long)pair->other);
    printf("\n");
}

void print_datum(datum d){
    assert(d.dptr != NULL); 
    assert(d.dsize != 0);
    for(int i = 0; i < d.dsize; i++){
        printf("%x ", d.dptr[i]);
    }
    printf("\n");
}

void build_db(GDBM_FILE db){
    datum key; // key to stored data
    datum val; // stored data
    struct Pair * pair;
    //size_t ichar = sizeof(int) + 1;

    // insert a value
    for(int k = 0; k < SIZE; k++){
        //char keystr[ichar];
        //sprintf(keystr, "%d", k); 
        //key.dptr = (void*)keystr;
        //key.dsize = ichar;
        key.dptr = (void*)&k;
        key.dsize = sizeof(int);
        
        pair = create_Pair(k);
        val.dptr = (void*)pair;
        val.dsize = sizeof(struct Pair);

        print_Pair(pair);

        gdbm_store(db, key, val, GDBM_REPLACE);
        free_Pair(pair);
    }
}

void dump(GDBM_FILE db){
    datum key;
    datum val;
    struct Pair * pair;
    // iterate through all keys
    key = gdbm_firstkey(db);
    
    while(key.dptr){
        datum nextkey;

        val = gdbm_fetch(db, key);

        pair = (struct Pair*)val.dptr;

        print_Pair(pair);

        nextkey = gdbm_nextkey(db, key);
        free(key.dptr);
        free_Pair(pair);

        key = nextkey;
    }
}

int main(){
    GDBM_FILE db;

    db = gdbm_open("database.db", 0, GDBM_WRCREAT, 0666, NULL);

    build_db(db);

    //dump(db);

    gdbm_close(db);

    exit(EXIT_SUCCESS);
}
