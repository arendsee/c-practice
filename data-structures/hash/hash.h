#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>

#define SALT 18747
#define HASH_SIZE 65536

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
    size_t size;
} datum;

typedef struct {
    datum * data;
    datum * key;
    struct bin * next;
} bin;

typedef struct {
    size_t size;
    uint conflicts; // Number of conflicting key hashes
    bin * table;
} hashmap;

void free_bin(bin *);

bin * init_bin();

void free_hash(hashmap * map);

hashmap * init_hash();

/* Add an entry to a hashmap
 *
 * Get the hashmap table index via the hash function and the given key
 *
 * Create a new bin structure from the key and data.
 *
 * Add the new bin the to beginning of the list. If there was already a bin at
 * this index, increment the conflict count. 
 *
 */
void add(datum * key, datum * data, hashmap * map);

void get(datum * key, hashmap * map);

void del(datum * key, hashmap * map);

void dump(hashmap * map);

/* Swap two bits in an unsigned short */
ushort swap(ushort x, size_t a, size_t b);

/* Print data in binary, bytes separated by spaces */
void print_binary(datum *);

/* XOR all byte together and return */
byte xor_all(datum *, byte hash);

/* Make a 16 bit hash of a key
 *
 * The hash is initialized to a salt value. This reduces the danger of an
 * attacker feeding many conflicting values into input, which would slow down
 * the loopups. I suppose this isn't a terribly critical problem, but the cost
 * of implementing it is trivial.
 *
 * Next each consecutive 16-bit block in the key is XORed against the hash with
 * the two bytes reversed.
 *
 * Finally, each 16-bit block i is XORed against block (n-i-1).
 *
 * This is probably an excessively heavy hash function for a hashmap.
 *
 */
ushort hash(datum * key);

#endif
