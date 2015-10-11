#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stdmacro.h"
#include "RingArena.h"

int main(int argc, char const *argv[])
{
	RingArena *arena = RingArena_new(3);
	for (int i = 0; i < MEGA; i++) {
		char *temp = RingArena_next(arena, 100);
		sprintf(temp, "%d", i);
		//printf("%s\n", temp);
	}
	RingArena_delete(arena);
	return 0;
}