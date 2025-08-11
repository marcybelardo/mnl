#include <stdlib.h>
#include <string.h>

#include "nl_hash.h"
#include "nl_hash_tbl.h"

static struct nl_hash_item NL_ITEM_DELETED = { NULL, NULL };

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
