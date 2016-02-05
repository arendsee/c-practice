#ifndef __INTERVAL_H__
#define __INTERVAL_H__

typedef struct {
    uint start;
    uint stop;
} Interval;

/* compare intervals by stop */
int cmp_stop(const void *, const void *);

/* compare intervals by start */
int cmp_start(const void *, const void *);

#endif
