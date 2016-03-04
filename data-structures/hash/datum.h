#ifndef __DATUM_H__
#define __DATUM_H__

#include <stdlib.h>

struct datum {
    void * data;
    size_t size;
};

/* Print data in binary, bytes separated by spaces */
void print_binary(struct datum *);

#endif
