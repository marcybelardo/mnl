/*
 *
 *      "Marcy's Nice Libs" v1.0.0
 *
 *      A friendly hash library. Easy and simple!
 *
 */

#ifndef NL_HASH_H
#define NL_HASH_H

#define NL_HASH_VERSION 1

#include <stdint.h>

const uint64_t FNV64_OFFSET_BASIS = 0xCBF29CE484222325;
const uint64_t FNV64_PRIME        = 0x00000100000001B3;

// Generates a 64-bit FNV-1a hash for string `data`
uint64_t nl_hash_fnv1a(const char *data);

#endif // NL_HASH_H
