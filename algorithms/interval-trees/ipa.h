#ifndef __IPA_H__
#define __IPA_H__

#include <stdlib.h>

#include "interval.h"

/** Interval pointer array */
typedef struct {
    size_t size;
    Interval ** v;
} IPA;

IPA * init_ipa();

void free_ipa(IPA * ipa);

#endif
