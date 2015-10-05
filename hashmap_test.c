#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char *K;
typedef int V;
#include "hashmap.h"

size_t hash1024(char *key) {
	size_t ret = 1;
	while (*key) {
		ret = 31 * ret + (*key);
		key++;
	}
	return ret % 1024;
}

void putget_test() {
	HashMap *map = HashMap_new(1024, hash1024, NULL, -1);

	HashMap_put(map, "januar", 1);
	HashMap_put(map, "februar", 2);
	HashMap_put(map, "mart", 3);

	assert(HashMap_get(map, "januar") == 1);
	assert(HashMap_get(map, "februar") == 2);
	assert(HashMap_get(map, "mart") == 3);

	HashMap_delete(map);
}

void saturation_test() {
	char keys[4096][32];
	for (size_t i = 0; i < 4096; i++) {
		sprintf(keys[i], "%zd", 13579 + i);
	}

	HashMap *map = HashMap_new(1024, hash1024, NULL, -1);

	for (size_t k = 1; k <= 10; k++) {
		// put all
		for (size_t i = 0; i < 4096; i++) {
			HashMap_put(map, keys[i], i);
			assert(HashMap_size(map) == i + 1);
		}
		// get all
		for (size_t i = 0; i < 4096; i++) {
			assert(HashMap_get(map, keys[i]) == i);
		}
		// update all
		for (size_t i = 0; i < 4096; i++) {
			HashMap_put(map, keys[i], i + k);
			assert(HashMap_size(map) == 4096);
		}
		// get all
		for (size_t i = 0; i < 4096; i++) {
			assert(HashMap_get(map, keys[i]) == i + k);
		}
		// delete all
		for (size_t i = 0; i < 4096; i++) {
			assert(HashMap_remove(map, keys[i]) == i + k);
			assert(HashMap_size(map) == 4096 - 1 - i);
		}
	}

	HashMap_delete(map);
}

int main(int argc, char const *argv[])
{
	putget_test();
	saturation_test();
	printf("All Ok.\n");
	return 0;
}