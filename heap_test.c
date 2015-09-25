#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "pcg32.h"

#define E uint32_t
#include "heap.h"
#undef E

pcg32_random_t rng = {13, 17};

void fill_random(uint32_t *arr, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		arr[i] = pcg32_random0(&rng);
	}
}

bool isheap(uint32_t *arr, size_t len)
{
	size_t last_parent = (len - 2) / 2;
	for (size_t p = 0; p <= last_parent; p++) {
		size_t c = 2 * p + 1;
		if (c < len && arr[c] > arr[p]) {
			return false;
		}
		c++;
		if (c < len && arr[c] > arr[p]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char const *argv[])
{
	size_t len = 100;
	uint32_t *arr = malloc(len * sizeof(*arr));
	fill_random(arr, len);
	assert(isheap(arr, len) == false);
	heap_make(arr, len);
	assert(isheap(arr, len) == true);
	free(arr);
	printf("All Ok.\n");
	return 0;
}