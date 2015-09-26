#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stdmacro.h"
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

bool isheap(uint32_t *arr, size_t len, heap_gt gt)
{
	size_t last_parent = (len - 2) / 2;
	for (size_t p = 0; p <= last_parent; p++) {
		size_t c = 2 * p + 1;
		if (c < len && gt(arr[c], arr[p])) {
			return false;
		}
		c++;
		if (c < len && gt(arr[c], arr[p])) {
			return false;
		}
	}
	return true;
}

bool issorted(uint32_t *arr, size_t length)
{
	for (size_t i = 1; i < length; i++) {
		if (arr[i-1] > arr[i]) {
			return false;
		}
	}
	return true;
}

bool uint32_gt(uint32_t a, uint32_t b)
{
	return a > b;
}

int uint32_cmp(const void *a, const void *b)
{
	return CMP(*(uint32_t*)a, *(uint32_t*)b);
}

/*
 * On 100 * MEGA of uint32_t
 * qsort:     21.2s
 * heap_sort: 37.4s
 */
int main(int argc, char const *argv[])
{
	size_t len = MEGA;
	uint32_t *arr = malloc(len * sizeof(*arr));

	fill_random(arr, len);
	assert(isheap(arr, len, uint32_gt) == false);
	heap_make(arr, len, uint32_gt);
	assert(isheap(arr, len, uint32_gt) == true);

	fill_random(arr, len);
	assert(issorted(arr, len) == false);
	qsort(arr, len, sizeof(uint32_t), uint32_cmp);
	assert(issorted(arr, len) == true);

	fill_random(arr, len);
	assert(issorted(arr, len) == false);
	heap_sort(arr, len, uint32_gt);
	assert(issorted(arr, len) == true);

	free(arr);
	printf("All Ok.\n");
	return 0;
}