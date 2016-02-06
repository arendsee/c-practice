#ifndef __IPA_H__
#define __IPA_H__

#include <stdlib.h>

#include "interval.h"

/** Interval pointer array */
typedef struct {
    size_t size;
    Interval * v;
} IPA;

/* initialize to {.size=0, .v=NULL} */
IPA * init_ipa();

/* initialize to a size, allocate memory to v */
IPA * init_set_ipa(size_t size);

void free_ipa(IPA * ipa);

#endif
