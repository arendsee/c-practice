#include <stdlib.h>

#include "interval.h"

/* compare Intervals by stop */
int cmp_stop(const void *ap, const void *bp){
    Interval a = ** (Interval **) ap;
    Interval b = ** (Interval **) bp;
    return((a.stop > b.stop) - (b.stop > a.stop));
}

/* compare Intervals by start */
int cmp_start(const void *ap, const void *bp){
    Interval a = ** (Interval **) ap;
    Interval b = ** (Interval **) bp;
    return((a.start > b.start) - (b.start > a.start));
}
