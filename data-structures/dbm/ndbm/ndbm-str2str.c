/* This program opens a dbm database and inserts the key/value pair provided as
 * arguments. It then dumps the entire database.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ndbm.h>
#include <fcntl.h>
#include <string.h>

void dump(DBM *db){
    datum key;
    datum val;
    char * key_str;
    char * val_str;
    // iterate through all keys
    for(key = dbm_firstkey(db); key.dptr != NULL; key = dbm_nextkey(db)){
        val = dbm_fetch(db, key);
        key_str = (char*)key.dptr;
        val_str = (char*)val.dptr;
        printf("%s\t%s\n", key_str, val_str);
    }
}

int main(int argc, char * argv[]){
    if(argc != 3){
        fprintf(stderr, "USAGE: ./a.out <key> <val>\n");
        exit(EXIT_FAILURE);
    }
    DBM * db;
    datum key; // key to stored data
    datum val; // stored data
    datum ret; // retrieved datum

    key.dptr = (void*) argv[1];
    key.dsize = sizeof(argv[1]);

    val.dptr = (void*) argv[2];
    val.dsize = sizeof(char) * (strlen(argv[2]) + 1);

    // open a new database
    db = dbm_open("database",
                  O_CREAT | O_EXCL | O_RDWR,
                  0666);

    // insert a value
    dbm_store(db, key, val, DBM_REPLACE);

    // fetch the value that was just inserted
    ret = dbm_fetch(db, key);
    
    // write TAB delimited key-val pairs
    dump(db);

    dbm_close(db);

    exit(EXIT_SUCCESS);
}
