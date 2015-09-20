#include <stdio.h>
#include "asrt/asrt.h"

#define E int
#include "vector.h"
#undef E

#define MEGA (1024 * 1024)

int main(int argc, char const *argv[])
{
	Vector *vector = vector_new();
	for (int i = 0; i < 10 * MEGA; i++) {
		vector_push(vector, i);
	}
	for (int i = 10 * MEGA - 1; i >= 0; i--) {
		int e = vector_pop(vector);
		ASRT_int(i, e);
	}
	vector_delete(vector);
	printf("All Ok.\n");
	return 0;
}