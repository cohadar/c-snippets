#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


#define E int
#include "vector.h"
#undef E

#define MEGA (1024 * 1024)

void *box_int(int x)
{
	int *ret = malloc(sizeof(*ret));
	assert(ret);
	*ret = x;
	return ret;
}

int unbox_int(int *i)
{
	int ret = *i;
	free(i);
	return ret;
}

void *square(void *e, void *closure)
{
	return box_int((*(int*)e) * (*(int*)e));
}

int main(int argc, char const *argv[])
{
	Vector *vec = Vector_new();
	for (int i = 0; i < 10 * MEGA; i++) {
		Vector_append(vec, box_int(i));
	}
	Vector *temp = vec;
	vec = Vector_map(vec, square, NULL);
	Vector_delete(temp, free);
	for (int i = 10 * MEGA - 1; i >= 0; i--) {
		int e = unbox_int(Vector_pop(vec));
		assert(i * i == e);
	}
	Vector_delete(vec, free);
	printf("All Ok.\n");
	return 0;
}
