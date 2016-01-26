/* This program builds a large database and tests the time required for various
 * operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <gdbm.h>
#include <time.h>

#define SIZE 1000000

// A function for timing functions
int time_function(GDBM_FILE db, void(*fun)(GDBM_FILE)){
    clock_t start;
    clock_t stop;
    start = clock();
    fun(db);
    stop = clock();
    return((stop - start) * 1000 / CLOCKS_PER_SEC);
}


// Build a big db, it will hold int keys and int values
void build_db(GDBM_FILE db){
    datum key; // key to stored data
    datum val; // stored data

    // insert a value
    int k,v;
    for(k = 0; k < SIZE; k++){
        key.dptr = (void*)&k;
        key.dsize = sizeof(int);

        v = k % 5;
        val.dptr = (void*)&v;
        val.dsize = sizeof(int);

        gdbm_store(db, key, val, GDBM_REPLACE);
    }
}

void random_access(GDBM_FILE db){
    int keyval;
    datum key;
    datum val;
    key.dsize = sizeof(int);
    for(int i = 0; i < SIZE; i++){
        keyval = rand() % SIZE;
        key.dptr = (void*)&keyval;
        val = gdbm_fetch(db, key);
        free(val.dptr);
    }
}


void count_keys(GDBM_FILE db){
    datum key = gdbm_firstkey(db);
    // iterate through all keys
    while(key.dptr){
        datum nextkey;
        nextkey = gdbm_nextkey(db, key);
        free(key.dptr);
        key = nextkey;
    }
}

void dump(GDBM_FILE db){
    datum key;
    datum val;
    int key_int;
    int val_int;
    // iterate through all keys
    key = gdbm_firstkey(db);
    while(key.dptr){
        datum nextkey;

        val = gdbm_fetch(db, key);

        key_int = *(int*)key.dptr;
        val_int = *(int*)val.dptr;

        printf("%d\t%d\n", key_int, val_int);

        nextkey = gdbm_nextkey(db, key);
        free(key.dptr);
        key = nextkey;
    }
}

int main(){
    GDBM_FILE db;
    int ms;

    // open a new database
    db = gdbm_open("database.db", 0, GDBM_WRCREAT, 0666, NULL);

    ms = time_function(db, build_db);
    printf("Added %d entries in %d ms\n", SIZE, ms);

    ms = time_function(db, count_keys);
    printf("Counted %d keys in %d ms\n", SIZE, ms);

    ms = time_function(db, random_access);
    printf("Randomly accessed %d keys in %d ms\n", SIZE, ms);

    gdbm_close(db);

    exit(EXIT_SUCCESS);
}
