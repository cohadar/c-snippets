#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stdmacro.h"
#include "pcg32.h"

#define E uint32_t
#include "insertionsort.h"
#undef E

pcg32_random_t rng = {13, 17};

bool issorted(uint32_t *arr, size_t length)
{
	for (size_t i = 1; i < length; i++) {
		if (arr[i-1] > arr[i]) {
			return false;
		}
	}
	return true;
}

uint32_t *malloc_random_array(size_t length)
{
	uint32_t *arr = malloc(length * sizeof(*arr));
	assert(arr);
	for (size_t i = 0; i < length; i++) {
		arr[i] = pcg32_random0(&rng);
	}
	return arr;
}

int main(int argc, char const *argv[])
{
	size_t length = KILO;
	uint32_t *arr = malloc_random_array(length);
	assert(issorted(arr, length) == false);
	insertionsort(arr, length);
	assert(issorted(arr, length) == true);
	free(arr);
	printf("All Ok.\n");
	return 0;
}

