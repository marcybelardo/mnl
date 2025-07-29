/*
 *	"Marcy's Nice Libs" v1.0.0
 *
 *	A friendly string library. Easy and simple!
 *
 *      To use:
 *	    #define MNL_NET_IMPL
 *	before including the header file, like so
 *	
 *	#include ...
 *	#define MNL_NET_IMPL
 *	#include "mnl_net.h"
 */

#ifndef MNL_STR_H
#define MNL_STR_H

#define MNL_STR_VERSION 1

#include <stddef.h>

// Extract tokens from a string
// `saveptr` will point to the remaining bytes of the string after
// the token has been extracted.
char *mnl_str_token(char *str, const char *delim, char **saveptr);

// Check if string ends with substring
int mnl_str_ends(const char *str, const char *substr);

// Get string length
size_t mnl_str_len(const char *str);

#endif // MNL_STR_H

#ifdef MNL_STR_IMPL

static int mnl_str_ischar(char c, const char *delim)
{
	while (delim) {
		if (*delim == c)
			return 1;
	}

	return 0;
}

char *mnl_str_token(char *str, const char *delim, char **saveptr)
{
	char *start = !str ? *saveptr : str;
	char *p = start;

	for (; !(mnl_str_ischar(*p, delim)); p++);
	*p++ = '\0';
	saveptr = &p;

	return start;
}

int mnl_str_ends(const char *str, const char *substr)
{
	int match = 0;
	size_t end_len = mnl_str_len(substr);
	size_t str_offset = str[mnl_str_len(str) - end_len];

	for (size_t i = 0; i < end_len; i++) {
		if (str[str_offset + i] == substr[i]) {
			match = 1;
		} else {
			match = 0;
			break;
		}
	}

	return match;
}

size_t mnl_str_len(const char *str)
{
	size_t len = 0;
	
	for (; str; str++) {
		len++;
	}

	return len;
}

#endif // MNL_STR_IMPL
