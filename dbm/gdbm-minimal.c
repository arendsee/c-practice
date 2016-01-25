// For full documentation, see *info gdbm*

// Compile command
// $ gcc gdbm-simple.c -lgdbm

#include <gdbm.h>

int main(){
    GDBM_FILE db;

    // Unlike ndbm, this is the WHOLE name of the file, no extensions are added
    // and the .pag and .dir files are not separated.
    const char * NAME = "gdbm_database.db";

    // let OS choose blocksize, minimum is 512
    int BLOCK_SIZE = 0;

    // options for the FLAGS parameter are
    // - GDBM_READER  - read only, may be many readers concurrently
    // - GDBM_WRITER  - read and write, exclusive access
    // - GDBM_WRCREAT - read and write, create if necessary
    // - GDBM_NEWDB   - read and write, overwrite if exists
    int FLAGS = GDBM_NEWDB;

    // permissions
    int MODE = 0644;

    // a function to handle errors, if NULL, use the default function
    void (*FATAL_FUNC)(const char *) = NULL;

    db = gdbm_open(NAME, BLOCK_SIZE, FLAGS, MODE, FATAL_FUNC);

    gdbm_close(db);

    return(0);
}
