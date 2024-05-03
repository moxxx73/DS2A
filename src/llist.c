#include "../include/ds2a.h"

#include <stdlib.h>

void *alloc_llnode(u64 dlen, int (*callback)(void *)){
	void *node;
	if(!(node = calloc(1, sizeof(llist_t)+dlen))){
		return NULL;
	}
	*(u64 *)(node+sizeof(void *)) = dlen;
	if(callback && callback(node) < 0){
		free(node);
		node = NULL;
	}
	return node;
}

void *alloc_dlnode(u64 dlen, int (*callback)(void *)){
	void *node = alloc_llnode(dlen+sizeof(void *), callback);
	if(node){
		*(u64 *)(node+sizeof(void *)) = 0;
		*(u64 *)(node+(sizeof(void *)*2)) = dlen;
	}
	return node;
}

void free_llnode(void *node, void (*callback)(void *)){
	if(callback) callback(node);
	if(node) free(node);
	return;
}

u64 llist_len(void *list){
	register u64 r;
	for(r = 0; list; r++, list = *(void **)list) ;
	return r;
}

void *alloc_dlist(u64 dlen, u64 nsize, int (*callback)(void *)){
	void **r, **save;
	u64 cur;

	if(!dlen || !nsize) return NULL;
	r = alloc_dlnode(nsize, callback);
	dlen--;

	save = r;
	for(cur = 0; cur < dlen; cur++){
		if(!(*(void **)(r) = alloc_dlnode(nsize, callback))){
			break;
		}
		*(void **)(*(void **)(r)+sizeof(void *)) = r;
		r = *(void **)(r);
	}
	return save;
}
