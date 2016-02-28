#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>

#define SALT 18747

#define byte unsigned char
#define uint unsigned int
#define ushort unsigned short

// Rotate one byte left
#define byte_rotl(x) (x) << 1 ^ (x) >> 7
// Rotate one byte right
#define byte_rotr(x) (x) >> 1 ^ (x) << 7

#define rotl(x,n,k) (x) << (k) ^ (x) >> ((n) - (k))
#define rotr(x,n,k) (x) >> (k) ^ (x) << ((n) - (k))

// Rotate k places on a block n bit long
#define grotl(x,n,k) (x) << ((k) % (n)) ^ (x) >> ((n) - ((k) % (n)))
#define grotr(x,n,k) (x) >> ((k) % (n)) ^ (x) << ((n) - ((k) % (n)))

typedef struct {
    void * data;
    struct bin * next;
} bin;

typedef struct {
    size_t size;
    bin * table[65536];
} hashmap;

/* Add an entry to a hashmap */
void add(void * data, hashmap map);
void get(void * key, hashmap map);
void del(void * key, hashmap map);
void dump(hashmap map);

/* Swap two bits in an unsigned short */
ushort swap(ushort x, size_t a, size_t b);

/* Print data in binary, bytes separated by spaces */
void print_binary(void * data, size_t size);

/* XOR all byte together and return */
byte xor_all(void * data, size_t size, byte hash);

/* Hash a key into an unsigned short index for the hash table */
ushort hash(void * key, size_t size);

#endif
