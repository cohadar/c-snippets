#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#include "stdmacro.h"
#include "pcg32.h"

#define E uint32_t
#include "insertionsort.h"
#include "merge.h"
#undef E

pcg32_random_t rng = {13, 17};



uint32_t *malloc_random_array(size_t length)
{
	uint32_t *arr = malloc(length * sizeof(*arr));
	assert(arr);
	for (size_t i = 0; i < length; i++) {
		arr[i] = pcg32_random0(&rng) % 10;
	}
	return arr;
}

bool uint32_gt(const uint32_t a, const uint32_t b)
{
	return a > b;
}

bool issorted(uint32_t *arr, size_t length, insertionsort_gt gt)
{
	for (size_t i = 1; i < length; i++) {
		if (gt(arr[i-1], arr[i])) {
			return false;
		}
	}
	return true;
}

int main(int argc, char const *argv[])
{
	rng.state = (uint32_t)&main;
	size_t length = KILO;
	uint32_t *arr = malloc_random_array(length);
	assert(issorted(arr, length, uint32_gt) == false);
	merge_sort(arr, length, uint32_gt);
	assert(issorted(arr, length, uint32_gt) == true);
	free(arr);
	printf("All Ok.\n");
	return 0;
}