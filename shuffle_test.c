#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcg32.h"

#define E char
#include "shuffle.h"
#undef E

pcg32_random_t rng = {13, 17};

// does not work if sizeof(size_t) != sizeof(uint32_t) and you use large arrays
// but who cares, this is only a test.
// TODO: made random_size_t functions?
static size_t random_range(size_t n)
{
	return pcg32_random1(&rng, n);
}

int main(int argc, char const *argv[])
{
	char arr[] = "ABCDEF";
	for (size_t i = 0; i < 10; i++) {
		shuffle(arr, strlen(arr), random_range);
		printf("%s\n", arr);
	}
	printf("The End.\n");
	return 0;
}