#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include "datum.h"
#include "global.h"

struct bucket {
    struct datum * val;
    struct datum * key;
    struct bucket * next;
};

void free_bucket(struct bucket *);

struct bucket * init_bucket();

struct hashmap {
    size_t index_size;
    size_t size;
    struct bucket ** table;
};

/* Recursively free
 *  - all buckets (but not their contents)
 *  - the bucket array,
 *  - hashmap struct itself
 */
void free_hashmap(struct hashmap * map);

struct hashmap * init_hash();

/* Add an entry to a hashmap
 *
 * Get the hashmap table index via the hash function and the given key
 *
 * Create a new bucket structure from the key and data.
 *
 * Add the new bucket the to beginning of the list. If there was already a bucket at
 * this index, increment the conflict count. 
 */
void add(struct datum * key, struct datum * data, struct hashmap * map);

struct datum * get(struct datum * key, struct hashmap * map);

/* Remove an entry, free the bucket, rewire the linked list */
void del(struct datum * key, struct hashmap * map);

void dump(struct hashmap * map);

#endif
