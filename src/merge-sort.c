#include "../include/ds2a.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void **split_dlist(void *dlist){
	void **split_nodes;
	u64 llen, r;

	if(!dlist) return NULL;
	llen = llist_len(dlist);
	if(!(split_nodes = calloc(1, (sizeof(void *)*(llen+1))))) return NULL;

	for(r = 0; r < llen && dlist; r++){
		split_nodes[r] = dlist;
		dlist = *(void **)dlist;
		*(void **)(split_nodes[r]) = NULL;
		*(void **)(split_nodes[r]+sizeof(void *)) = NULL;
	}

	return split_nodes;
}


void *msort_dlist(void *dlist_hd, int (*callback)(void *, void *)){
	void **split_nodes;
	dlist_t *left, *right, *fw_save, *bk_save, *left_save;
	u64 dlist_len, i, len_save;

	if(!dlist_hd || !callback) return NULL;
	dlist_len = llist_len(dlist_hd);
	len_save = dlist_len;	

	if(!(split_nodes = split_dlist(dlist_hd))) return NULL;
	while(dlist_len > 1){
		for(i = 0; i < dlist_len; i+=2){
				for(left = (dlist_t *)split_nodes[i]; left; left = (left) ? left->fw : NULL){
					for(right = (dlist_t *)split_nodes[i+1]; right; right = (right) ? right->fw : NULL){
						switch(callback(left, right)){
							case -1:
								fw_save = right->fw;
                    			bk_save = right->bk;
                    			if(right->fw) right->fw->bk = right->bk;
                    			if(right->bk) right->bk->fw = right->fw;

                    			left_save = left->fw;
                    			left->fw = right;
                    			left->fw->bk = left;
                    			left->fw->fw = left_save;
                    			if(left->fw->fw) left->fw->fw->bk = left->fw;

                    			if(split_nodes[i+1] == right) split_nodes[i+1] = fw_save;
                    			if(!split_nodes[i+1]){
                        			memmove(&split_nodes[i+1], &split_nodes[i+2], (sizeof(void *)*(dlist_len-i-1)));
                        			dlist_len--;
                    			}
								right = (bk_save) ? bk_save : fw_save;
								break;
							case 1:

								fw_save = right->fw;
                    			bk_save = right->bk;
                    			if(right->bk) right->bk->fw = right->fw;
                    			if(right->fw) right->fw->bk = right->bk;
                    
                    			left_save = left->bk;
                    			left->bk = right;
                    			left->bk->fw = left;
                    			left->bk->bk = left_save;
                			    if(left->bk->bk) left->bk->bk->fw = left->bk;
                    
    			                if(split_nodes[i] == left) split_nodes[i] = left->bk;

                    			if(split_nodes[i+1] == right) split_nodes[i+1] = fw_save;
                    			if(!split_nodes[i+1]){
                        			memmove(&split_nodes[i+1], &split_nodes[i+2], (sizeof(void *)*(dlist_len-i-1)));
                        			dlist_len--;
                    			}
								right = (bk_save) ? bk_save : fw_save;
								break;
							default:
								break;
						}
					}
				}
		}
	}
	
	dlist_hd = split_nodes[0];
	memset(split_nodes, 0, sizeof(void *)*(len_save+1));
	free(split_nodes);
	return dlist_hd;
}
