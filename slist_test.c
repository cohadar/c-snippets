#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define E char
#include "SList.h"
#undef E

int main(int argc, char const *argv[])
{
	char *hello = "Hello World!";
	size_t len = strlen(hello) + 1;
	SList *lst = SList_new();
	SList_appendArray(lst, hello, len);
	char *world = SList_mallocArray(lst, &len);
	assert(strcmp(hello, world) == 0);
	free(world);
	SList_delete(lst);
	printf("All Ok.\n");
	return 0;
}