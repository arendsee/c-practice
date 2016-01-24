/*
 * Here I compare the usage of two GNU C Library hash implementations. The
 * POSIX compatible is unfortunately specified as being global, allowing only
 * one hashtable to be used at a time in a program. The GNU extension bypasses
 * this problem.
 *
 * POSIX:
 *  int hcreate(size_t nel);
 *  ENTRY *hsearch(ENTRY item, ACTION action);
 *  void hdestroy(void);
 *
 * GNU extension:
 *  int hcreate_r(size_t nel, struct hsearch_data *htab);
 *  int hsearch_r(ENTRY item, ACTION action, ENTRY **retptr, struct hsearch_data *htab);
 *  void hdestroy_r(struct hsearch_data *htab);
*/

#define _GNU_SOURCE
#include <search.h>
#include <stdio.h>
#include <stdlib.h>

//  A stub structure
typedef struct Data {
    int x;
} Data;

int main(void){

    // estimate the maximum size, will be adjusted if needed
    size_t nel = 10;

    // a container for entries in the table
    ENTRY ent, *entptr;
    ENTRY src, *srcptr;
    ENTRY ret, *retptr;
    entptr = &ent;
    srcptr = &src;
    retptr = &ret;

    Data a = {5};


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // POSIX: There can be only one hash in memory at a time
    hcreate(nel);

    // GNU:
    struct hsearch_data *htab;
    hcreate_r(nel, htab);
    //----------------------------------------------------------------


    // create an entry to add
    entptr->key = "datum";
    entptr->data = (Data *) &a;


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // add entry to hash table
    // POSIX:
    hsearch(ent, ENTER);

    // GNU:
    hsearch_r(ent, ENTER, &retptr, htab);
    //----------------------------------------------------------------


    // retrieve entry from hash table
    srcptr->key = "datum";


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // POSIX: returns retptr
    retptr = hsearch(*srcptr, FIND);
    printf("POSIX: %s -> %d\n", retptr->key, ((Data *)(retptr->data))->x);

    // GNU: sets retptr
    hsearch_r(*srcptr, FIND, &retptr, htab);
    printf("GNU: %s -> %d\n", retptr->key, ((Data *)(retptr->data))->x);
    //----------------------------------------------------------------


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Free all memmory used by whataever hash is currently in use
    // POSIX:
    hdestroy();
    // GNU:
    hdestroy_r(htab);
    //----------------------------------------------------------------

    exit(EXIT_SUCCESS);
}
