#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define E char
#include "SList.h"
#undef E

void testToFromArray()
{
	char *hello = "Hello World!";
	size_t len = strlen(hello) + 1;
	SList *lst = SList_new();
	SList_appendArray(lst, hello, len);
	char *world = SList_mallocArray(lst, &len);
	assert(strcmp(hello, world) == 0);
	free(world);
	SList_delete(lst);
}

void testInsertionSort() {
	char *arr = "2578419063";
	size_t len = strlen(arr);
	SList *lst = SList_new();
	SList_appendArray(lst, arr, len);
	lst = SList_insertionSort(lst);
	char *actual = SList_mallocArray(lst, &len);
	for (int i = 0; i < 10; i++) {
		assert(i + '0' == actual[i]);
	}
	free(actual);
	SList_delete(lst);
}

int main(int argc, char const *argv[])
{
	testToFromArray();
	testInsertionSort();
	printf("All Ok.\n");
	return 0;
}