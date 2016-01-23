#include <search.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){

    // describe the minimum
    size_t nel = 1e6;
    // There can be only one hash in memory at a time
    int state = hcreate(nel);

    // Free all memmory used by whataever hash is currently in use
    hdestroy();
    exit(EXIT_SUCCESS);
}
