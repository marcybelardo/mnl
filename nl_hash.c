#include <string.h>
#include <stdlib.h>

#include "nl_hash.h"

static uint64_t fnv1a_64(const uint8_t *data, size_t len)
{
	uint64_t hash = FNV64_OFFSET_BASIS;

	for (size_t i = 0; i < len; i++) {
		hash ^= data[i];
		hash *= FNV64_PRIME;
	}

	return hash;
}

uint64_t nl_hash_fnv1a(const char *data)
{
	size_t len = strlen(data);
	return fnv1a_64((uint8_t *)data, len);
}
