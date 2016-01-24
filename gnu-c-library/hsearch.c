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
    ENTRY *enter_p;
    ENTRY *find_p

    Data a = {5};
    Data * ret;

    // There can be only one hash in memory at a time
    hcreate(nel);

    // create an entry to add
    enter_p->key = "datum";
    enter_p->data = (Data *) &a;

    // add entry to hash table
    hsearch(*enter_p, ENTER);

    // retrieve entry from hash table
    find_p->key = "datum";
    find_p = hsearch(*find_p, FIND);

    printf("%s -> %d\n", find_p->key, ((Data *)(find_p->data))->x);

    // Free all memmory used by whataever hash is currently in use
    hdestroy();

    exit(EXIT_SUCCESS);
}
