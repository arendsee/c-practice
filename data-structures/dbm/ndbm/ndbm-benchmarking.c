/* This program builds a large database and tests the time required for various
 * operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <ndbm.h>
#include <fcntl.h>
#include <time.h>

#define SIZE 100000

// A function for timing functions
int time_function(DBM * db, void(*fun)(DBM *)){
    clock_t start;
    clock_t stop;
    start = clock();
    fun(db);
    stop = clock();
    return((stop - start) * 1000 / CLOCKS_PER_SEC);
}


// Build a big db, it will hold int keys and int values
void build_db(DBM *db){
    datum key; // key to stored data
    datum val; // stored data

    // insert a value
    int k,v;
    for(k = 0; k < SIZE; k++){
        key.dptr = (void*)&k;
        key.dsize = sizeof(int);

        v = k % 3;
        val.dptr = (void*)&v;
        val.dsize = sizeof(int);

        dbm_store(db, key, val, DBM_REPLACE);
    }
}

void random_access(DBM *db){
    int keyval;
    datum key;
    key.dsize = sizeof(int);
    for(int i = 0; i < SIZE; i++){
        keyval = rand() % SIZE;
        key.dptr = (void*)&keyval;
        dbm_fetch(db, key);
    }
}


void count_keys(DBM *db){
    // iterate through all keys
    int n = 0;
    for(datum key = dbm_firstkey(db); key.dptr != NULL; key = dbm_nextkey(db)){
        n++;
    }
}

void dump(DBM *db){
    datum key;
    datum val;
    int * key_int;
    int * val_int;
    // iterate through all keys
    for(key = dbm_firstkey(db); key.dptr != NULL; key = dbm_nextkey(db)){
        val = dbm_fetch(db, key);
        key_int = (int*)key.dptr;
        val_int = (int*)val.dptr;
        printf("%d\t%d\n", *key_int, *val_int);
    }
}

int main(){
    DBM * db;
    int ms;

    // open a new database
    db = dbm_open("database",
                  O_CREAT | O_EXCL | O_RDWR,
                  0666);

    ms = time_function(db, build_db);
    printf("Added %d entries in %d ms\n", SIZE, ms);

    ms = time_function(db, count_keys);
    printf("Counted %d keys in %d ms\n", SIZE, ms);

    ms = time_function(db, random_access);
    printf("Randomly accessed %d keys in %d ms\n", SIZE, ms);

    dbm_close(db);

    exit(EXIT_SUCCESS);
}
