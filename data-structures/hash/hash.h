#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "datum.h"

// Rotate one byte left
#define byte_rotl(x) (x) << 1 ^ (x) >> 7
// Rotate one byte right
#define byte_rotr(x) (x) >> 1 ^ (x) << 7

#define rotl(x,n,k) (x) << (k) ^ (x) >> ((n) - (k))
#define rotr(x,n,k) (x) >> (k) ^ (x) << ((n) - (k))

// Rotate k places on a block n bit long
#define grotl(x,n,k) (x) << ((k) % (n)) ^ (x) >> ((n) - ((k) % (n)))
#define grotr(x,n,k) (x) >> ((k) % (n)) ^ (x) << ((n) - ((k) % (n)))

/* Swap two bits in an unsigned short */
ushort swap(ushort x, size_t a, size_t b);

/* XOR all byte together and return */
byte xor_all(struct datum *, byte hash);

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
ushort hash(struct datum * key);

#endif
