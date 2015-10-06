#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef int V;
#include "hashmap.h"

bool strz_eq(char *a, char *b) {
	return strcmp(a, b) == 0;
}

void putget_test() {
	HashMap *map = HashMap_new(1024, 0);

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
	char keys2[4096][32];
	for (size_t i = 0; i < 4096; i++) {
		sprintf(keys[i], "%zd", 13579 + i);
		sprintf(keys2[i], "%zd", 13579 + i);
	}

	HashMap *map = HashMap_new(1024, 0);

	for (size_t k = 1; k <= 10; k++) {
		// put all
		for (size_t i = 0; i < 4096; i++) {
			HashMap_put(map, keys[i], i);
			assert(HashMap_size(map) == i + 1);
		}
		// get all (note we use same keys, but different string instances)
		for (size_t i = 0; i < 4096; i++) {
			assert(HashMap_get(map, keys2[i]) == i);
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

void sum_values(HashMapEntry *e, void *suma)
{
	*(int *)suma += e->value;
}

void filter_odd(HashMapEntry *e, void *data)
{
	if (e->value % 2 == 1) {
		e->key = NULL;
	}
}

void assert_even(HashMapEntry *e, void *count)
{
	assert(e->value % 2 == 0);
	*(int *)count += 1;
}

void assert_none(HashMapEntry *e, void *data)
{
	assert(0);
}

void iteration_test() {
	char keys[4096][32];
	for (size_t i = 0; i < 4096; i++) {
		sprintf(keys[i], "%zd", 13579 + i);
	}

	HashMap *map = HashMap_new(1024, 0);

	// put all
	for (size_t i = 0; i < 4096; i++) {
		HashMap_put(map, keys[i], i);
		assert(HashMap_size(map) == i + 1);
	}

	// sum all
	int suma = 0;
	HashMap_forAll(map, sum_values, &suma);
	assert(suma == (4095 * 4096 / 2));

	// filter odd
	HashMap_forAll(map, filter_odd, NULL);
	assert(HashMap_size(map) == 2048);

	// assert all even
	int count = 0;
	HashMap_forAll(map, assert_even, &count);
	assert(count == 2048);

	// clear
	HashMap_clear(map);
	assert(HashMap_size(map) == 0);
	HashMap_forAll(map, assert_none, NULL);

	HashMap_delete(map);
}

void accordion_test() {
	char keys[4096][32];
	for (size_t i = 0; i < 4096; i++) {
		sprintf(keys[i], "%zd", 13579 + i);
	}

	HashMap *map = HashMap_new(1024, 0);

	for (size_t k = 0; k < 10; k++) {
		// put all
		for (size_t i = 0; i < 4096; i++) {
			HashMap_put(map, keys[i], i);
		}
		assert(HashMap_size(map) == 4096);
		// get all
		for (size_t i = 0; i < 4096; i++) {
			assert(HashMap_get(map, keys[i]) == i);
		}
		// remove all
		for (size_t i = 0; i < 4096; i++) {
			HashMap_remove(map, keys[i]);
		}
		assert(HashMap_size(map) == 0);
	}

	HashMap_delete(map);
}

int main(int argc, char const *argv[])
{
	putget_test();
	saturation_test();
	iteration_test();
	accordion_test();
	printf("All Ok.\n");
	return 0;
}