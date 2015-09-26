#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

#include "stdmacro.h"
#include "pcg32.h"

#define E uint32_t
#include "insertionsort.h"
#include "merge.h"
#undef E

pcg32_random_t rng = {13, 17};

void fill_random_array(uint32_t *arr, size_t length)
{
	for (size_t i = 0; i < length; i++) {
		arr[i] = pcg32_random0(&rng) % 10;
	}
}

bool uint32_gt(const uint32_t a, const uint32_t b)
{
	return a > b;
}

int uint32_cmp(const void *a, const void *b)
{
	return CMP(*(uint32_t*)a, *(uint32_t*)b);
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
	size_t length = MEGA;
	uint32_t *arr = malloc(length * sizeof(*arr));
	assert(arr);
	fill_random_array(arr, length);
	assert(issorted(arr, length, uint32_gt) == false);
	merge_sort(arr, length, uint32_gt);
	// mergesort(arr, length, sizeof(*arr), uint32_cmp); // from stdlib
	assert(issorted(arr, length, uint32_gt) == true);
	free(arr);
	printf("All Ok.\n");
	return 0;
}