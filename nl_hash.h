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

#define NL_HASH_VERSION 1

#include <stddef.h>
#include <stdint.h>

struct nl_hash_item {
	char *key;
	char *val;
};

struct nl_hash_tbl {
	size_t size;
	size_t count;
	struct nl_hash_item **items;
};

// Create a new hash table
struct nl_hash_tbl *nl_hash_tbl_new(void);

// Delete a hash table
void nl_hash_tbl_del(struct nl_hash_tbl *tbl);

// Insert a new key-value pair into the hash table
void nl_hash_tbl_insert(struct nl_hash_tbl *tbl, const char *key, const char *val);

// Get an item's value via its key
char *nl_hash_tbl_get(struct nl_hash_tbl *tbl, const char *key);

// Delete an item from the hash table
void nl_hash_tbl_del_item(struct nl_hash_tbl *tbl, const char *key);

// Generates a 64-bit FNV-1a hash for string `data`
uint64_t nl_hash_fnv1a(const char *data);

#endif // NL_HASH_H

#ifdef NL_HASH_IMPL

#include <string.h>
#include <stdlib.h>

// We're using the FNV-1a hash algorithm
static const uint64_t FNV64_OFFSET_BASIS = 0xCBF29CE484222325;
static const uint64_t FNV64_PRIME        = 0x00000100000001B3;

// static const uint32_t FNV32_OFFSET_BASIS = 0x811C9DC5;
// static const uint32_t FNV32_PRIME        = 0x01000193;

static struct nl_hash_item NL_ITEM_DELETED = { NULL, NULL };

static uint64_t fnv1a_64(const uint8_t *data, size_t len)
{
	uint64_t hash = FNV64_OFFSET_BASIS;

	for (size_t i = 0; i < len; i++) {
		hash ^= data[i];
		hash *= FNV64_PRIME;
	}

	return hash;
}

static struct nl_hash_item *item_new(const char *key, const char *val)
{
	struct nl_hash_item *item = malloc(sizeof(struct nl_hash_item));
	item->key = strdup(key);
	item->val = strdup(val);

	return item;
}

static void item_del(struct nl_hash_item *item)
{
	free(item->key);
	free(item->val);
	free(item);
}

struct nl_hash_tbl *nl_hash_tbl_new(void)
{
	struct nl_hash_tbl *tbl = malloc(sizeof(struct nl_hash_tbl));
	tbl->size = 53;
	tbl->count = 0;
	tbl->items = calloc((size_t)tbl->size, sizeof(struct nl_hash_item *));

	return tbl;
}

void nl_hash_tbl_del(struct nl_hash_tbl *tbl)
{
	for (size_t i = 0; i < tbl->size; i++) {
		struct nl_hash_item *item = tbl->items[i];
		if (item)
			item_del(item);
	}

	free(tbl->items);
	free(tbl);
}

void nl_hash_tbl_insert(struct nl_hash_tbl *tbl, const char *key, const char *val)
{
	struct nl_hash_item *item = item_new(key, val);
	size_t idx = nl_hash_fnv1a(item->key) % tbl->size;
	struct nl_hash_item *cur = tbl->items[idx];
	if (cur && cur != &NL_ITEM_DELETED)
		if (strcmp(cur->key, key) == 0) {
			item_del(cur);
			tbl->items[idx] = item;
			return;
		}

	tbl->items[idx] = item;
	tbl->count++;
}

char *nl_hash_tbl_get(struct nl_hash_tbl *tbl, const char *key)
{
	size_t idx = nl_hash_fnv1a(key) % tbl->size;
	struct nl_hash_item *item = tbl->items[idx];
	if (item && item != &NL_ITEM_DELETED)
		if (strcmp(item->key, key) == 0)
			return item->val;

	return NULL;
}

void nl_hash_tbl_del_item(struct nl_hash_tbl *tbl, const char *key)
{
	size_t idx = nl_hash_fnv1a(key) % tbl->size;
	struct nl_hash_item *item = tbl->items[idx];
	if (item && item != &NL_ITEM_DELETED)
		if (strcmp(item->key, key) == 0) {
			item_del(item);
			tbl->items[idx] = &NL_ITEM_DELETED;
		}

	tbl->count--;
}

uint64_t nl_hash_fnv1a(const char *data)
{
	size_t len = strlen(data);
	return fnv1a_64(data, len);
}

#endif // NL_HASH_IMPL
