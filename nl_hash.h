/*
 *      "Marcy's Nice Libs" v1.0.0
 *
 *      A friendly hash library. Easy and simple!
 *
 *      To use:
 *          #define NL_HASH_IMPL
 *      before including the header file, like so
 *
 *      #include ...
 *      #define NL_HASH_IMPL
 *      #include "nl_hash.h"
 */

#ifndef NL_HASH_H
#define NL_HASH_H

#include <string.h>
#include <stddef.h>
#include <stdint.h>

// Generates a 64-bit FNV-1a hash for string `data`
uint64_t nl_hash_64(char *data);

#endif // NL_HASH_H

#ifdef NL_HASH_IMPL

#include <stdio.h>

// We're using the FNV-1a hash algorithm
static const uint64_t FNV64_OFFSET_BASIS = 0xCBF29CE484222325;
static const uint64_t FNV64_PRIME        = 0x00000100000001B3;

// static const uint32_t FNV32_OFFSET_BASIS = 0x811C9DC5;
// static const uint32_t FNV32_PRIME        = 0x01000193;

static uint64_t fnv1a_64(const uint8_t *data, size_t len)
{
	uint64_t hash = FNV_OFFSET_BASIS;

	for (size_t i = 0; i < len; i++) {
		hash ^= data[i];
		hash *= FNV_PRIME;
	}

	return hash;
}

uint64_t nl_hash_64(const char *data)
{
	size_t len = strlen(data);
	return fnv1a_64(data, len);
}

#endif // NL_HASH_IMPL
