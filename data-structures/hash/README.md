# Hash

This is own personal hash map implementation. I've built it purely for my own
edification with no intention of using it in production.

# Operations

The hash has the following prototypes:

 * struct hashmap * init\_hash()

 * void add(struct datum * key, struct datum * data, struct hashmap * map)

 * struct datum * get(struct datum * key, struct hashmap * map);

 * void del(struct datum * key, struct hashmap * map);

 * void dump(struct hashmap * map);

# Implementation

## Datum structures

The Datum structures include a pointer to arbitrary data and a size\_t value
specifying the number of bytes in the data.

```
struct datum {
    void * data;
    size_t size; # number of bytes
};
```

## Hashing function

The purpose of the hashing function is to take an input key of arbitrary type
and size (as a Datum struct) and convert it to a valid index in the hash table
array. If the index is already used, the new value will be added to the
beginning of a linked list. For this reason, if the number of entries is much
greater than the length of the array, or if entries are mapped with bias to
certain hashes, lookup becomes linear. The former problem can be addressed by
dynamically resizing the array. The latter is solved by ensuring the has
function produces a uniformly random output.

Pseudocode:

```
SALT = random 16-bit integer 
hash(key, key_size, table_size)
    pad key with 0's s.t. length in bytes is even
    cast key as array of 16-bit integers
    hash = SALT
    for(i in 1:key_size)
        hash = hash XOR key[i] << 8
        hash = hash XOR key[i] >> 8
        hash = hash XOR key[key_size - i - 1]
    hash = hash / table_size
    return hash
```

Currently, actually, the hash table is always the length of a short. But I will
generalize it at some point.
