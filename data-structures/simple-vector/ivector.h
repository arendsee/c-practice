#ifndef __IVECTOR_H__
#define __IVECTOR_H__

#include <stdlib.h>

/* sample data type */
typedef struct {
    size_t a;
    size_t b;
} Interval;

typedef struct {
    size_t available; /* total allocated memory */
    size_t size;      /* memory used */
    Interval * data;
} ivector;

ivector * ivector_init(size_t);

void ivector_add (ivector *, Interval);

Interval * ivector_get (ivector *, size_t);

void ivector_free(ivector *);

#endif
