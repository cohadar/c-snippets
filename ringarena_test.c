#include "ringarena.h"

int main(int argc, char const *argv[])
{
	RingArena *arena = ringarena_new(3);
	for (int i = 0; i < 100; i++) {
		char *temp = ringarena_next(arena, 100);
		sprintf(temp, "%d", i);
		printf("%s\n", temp);
	}
	ringarena_delete(arena);
	return 0;
}