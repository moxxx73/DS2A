#include "../include/ds2a.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LENGTH 10
#define DATASIZE 4
#define TOTAL_SIZE (sizeof(void *)*2)+sizeof(u64)+DATASIZE
#define MAX_NUM 100
#define MIN_NUM 1

typedef struct __attribute__((__packed__)){
	dlist_t hdr;
	int value;
}custom_node;

int compare_nodes(void *l, void *r){
	custom_node *left = l, *right = r;
	custom_node *next;

	assert(l && r);
	if(left->value > right->value){
		next = (custom_node *)left->hdr.bk;
		if(!next || (next && next->value <= right->value)){
			return 1;
		}
	}else{
		next = (custom_node *)left->hdr.fw;
		if(!next || (next && next->value >= right->value)){
			return -1;
		}
	}

	return 0;
}

int insert_randint(void *node){
	custom_node *cast = node;
	if(node) cast->value = ((int)random())%(((MAX_NUM+1)-MIN_NUM)+MIN_NUM);
	return 0;
}

int main(int argc, char **argv){
	(void)argc;
	(void)argv;

	void *hd;
	custom_node *ptr;
	u64 i, l;

	srand(time(NULL));
	hd = alloc_dlist(LENGTH, DATASIZE, insert_randint);
	if(!hd){
		fprintf(stderr, "uh oh :(\n");
		return 1;
	}
	printf("Allocated double linked list of length %lu\nNode Size: %lu\n", llist_len(hd), TOTAL_SIZE);
	puts("[UNSORTED LIST]");
	for(ptr = (custom_node *)hd; ptr; ptr = (custom_node *)ptr->hdr.fw) printf("%d ", ptr->value);
	printf("\n");

	hd = msort_dlist(hd, compare_nodes);
	puts("[SORTED LIST]");
	for(ptr = (custom_node *)hd; ptr; ptr = (custom_node *)ptr->hdr.fw) printf("%d ", ptr->value);
	printf("\n");

	return 0;
}
