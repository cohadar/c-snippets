#include <stdio.h>
#include <assert.h>
#include "asrt/asrt.h"

#define E int
#include "vector.h"
#undef E

#define MEGA (1024 * 1024)

int main(int argc, char const *argv[])
{
	Vector *vec = Vector_new();
	for (int i = 0; i < 10 * MEGA; i++) {
		Vector_push(vec, i);
	}
	for (int i = 10 * MEGA - 1; i >= 0; i--) {
		int e = Vector_pop(vec);
		ASRT_int(i, e);
	}
	Vector_delete(vec);
	printf("All Ok.\n");
	return 0;
}