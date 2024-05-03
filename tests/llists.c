#include "../include/ds2a.h"
#include <stdio.h>
#include <stdlib.h>

struct __attribute__((__packed__)) node_data {
	char buf[64];
};

struct __attribute__((__packed__)) node {
	llist_t *hdr;
	struct node_data data;
};

int main(int argc, char **argv){
	(void)argc;
	(void)argv;
	
	int i;
	void *hd, *cur;

	if(!(hd = alloc_llnode(sizeof(struct node_data), NULL))){
		fprintf(stderr, "we fucked up :(\n");
		return 1;
	}
	cur = hd;

	for(i = 0; i < 3; i++){
		if(!(((llist_t *)cur)->fw = alloc_llnode(sizeof(struct node_data), NULL))){
			fprintf(stderr, "uhoh fucky wucky\n");
			break;
		}
		cur = *(void **)cur;
	}

	printf("Linked list length: %lu\n", llist_len(hd));

	for(i = 0; i < 3 && hd; i++){
		cur = *(void **)(hd);
		free_llnode(hd, NULL);
		hd = cur;
	}
	
}
