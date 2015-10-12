#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stdmacro.h"
#include "fixedarena.h"

#define FIXED 15

int main(int argc, char const *argv[])
{
	FixedArena *arena = FixedArena_new(FIXED, 16);
	for (size_t i = 0; i < MEGA; i++) {
		char *temp = FixedArena_alloc(arena);
		for (int i = 0; i < FIXED; i++) {
			assert(temp[i] == 0);
			temp[i] = i;
		}
	}
	FixedArena_delete(arena);
	arena = FixedArena_new(FIXED, 16);
	for (size_t i = 0; i < MEGA; i++) {
		char *temp = FixedArena_alloc(arena);
		for (int i = 0; i < FIXED; i++) {
			assert(temp[i] == 0);
			temp[i] = i;
		}
	}
	FixedArena_delete(arena);
	return 0;
}

