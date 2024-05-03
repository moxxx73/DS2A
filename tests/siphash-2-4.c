#include "../include/ds2a.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	u64 hash = 0;
	u64 key[2] = {0xdeadbeef, 0xcafebabe};

	if(argc < 2){
		printf("Usage: %s <String>\n", argv[0]);
		return 0;
	}

	siphash(argv[1], strlen(argv[1]), (u8 *)key, 16, &hash);
	printf("siphash-2-4(%s): %lx\n", argv[1], hash);
	return 0;
}
