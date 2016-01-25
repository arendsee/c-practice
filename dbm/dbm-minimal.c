#include <stdio.h>
#include <ndbm.h>
#include <fcntl.h>

// Compile command
// $ gcc dbm-simple.c -lgdbm -lgdbm_compat

int main(){
    DBM * db;

    db = dbm_open("database",       // base filename
                  O_CREAT | O_RDWR, // open flags
                  0666);            // permissions

    dbm_close(db);

    return(0);
}
