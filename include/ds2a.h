#ifndef DS2A_H
#define DS2A_H

#include "ints.h"

int siphash(u8 *in, u64 inlen, u8 *key, u64 keylen, u64 *out);

typedef struct __attribute__((__packed__)) generic_llist_node {
	struct generic_llist_node *fw;
	u64 dlen;
}llist_t;
#define LL_HDRSZ (sizeof(void *)+8)

typedef struct __attribute__((__packed__)) generic_dlist_node {
	struct generic_dlist_node *fw;
	struct generic_dlist_node *bk;
	u64 dlen;
}dlist_t;
#define DL_HDRSZ (sizeof(void *)*2)+8

void *alloc_llnode(u64 dlen, int (*callback)(void *));
void *alloc_dlnode(u64 dlen, int (*callback)(void *));
void free_llnode(void *node, void (*callback)(void *));
u64 llist_len(void *list);
void *alloc_dlist(u64 dlen, u64 nsize, int (*callback)(void *));
void *msort_dlist(void *dlist_hd, int (*callback)(void *, void *));

#endif
