#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "memarena.h"

int main(int argc, char const *argv[])
{
	MemArena *arena = MemArena_new();
	for (int i = 0; i < 1000; i++) {
		char *temp = MemArena_alloc(arena, 10 + i);
		temp[0] = 'c';
	}
	// This will free all allocated strings. This program does not leak memory.
	MemArena_delete(arena);
	return 0;
}


