#include <stdio.h>
#include "pcg32.h"
#include "asrt/asrt.h"
#include "stdmacro.h"

void test_random0(pcg32_random_t *rng, size_t count) {
	uint32_t min = UINT32_MAX;
	uint32_t max = 0;
	for (size_t i = 0; i < count; i++) {
		uint32_t x = pcg32_random0(rng);
		min = MIN(min, x);
		max = MAX(max, x);
	}
	printf("min=%" PRIu32 ", max=%" PRIu32 "\n", min, max);
}

void test_random1(pcg32_random_t *rng, size_t count)
{
	uint32_t *hundred = calloc(100, sizeof(*hundred));
	for (int i = 0; i < count; i++) {
		uint32_t x = pcg32_random1(rng, 100);
		ASRT_true(x >= 0);
		ASRT_true(x < 100);
		hundred[x]++;
	}
	for (int i = 0; i < 100; i++) {
		ASRT_true(hundred[i] > 0);
	}
	printf("All in range1.\n");
}

void test_random2(pcg32_random_t *rng, size_t count)
{
	uint32_t *buff = calloc(300, sizeof(*buff));
	for (int i = 0; i < count; i++) {
		uint32_t x = pcg32_random2(rng, 100, 200);
		ASRT_true(x >= 100);
		ASRT_true(x <= 200);
		buff[x]++;
	}
	for (int i = 100; i <= 200; i++) {
		ASRT_true(buff[i] > 0);
	}
	printf("All in range2.\n");
}

int main(int argc, char const *argv[])
{
	// use fixed seed
	pcg32_random_t rng = {13, 17};

	// discard first value, it is always zero
	pcg32_random_r(&rng);

	// find out min and max integers we get in lots of random0 samples
	test_random0(&rng, GIGA);

	// find out if bounded random covers all values in range [0..100)
	test_random1(&rng, MEGA);

	// find out if bounded random covers all values in range [100..200]
	test_random2(&rng, MEGA);

	return 0;
}