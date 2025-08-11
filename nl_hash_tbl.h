/*
 *
 *      "Marcy's Nice Libs" v1.0.0
 *
 *      A friendly hash table library. Easy and simple!
 *
 */

#ifndef NL_HASH_TBL_H
#define NL_HASH_TBL_H

#define NL_HASH_TBL_VERSION 1

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

#endif // NL_HASH_TBL_H
