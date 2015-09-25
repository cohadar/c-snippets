#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "asrt/asrt.h"

#define E char
#include "reverse.h"
#undef E

void test_reverse(char *a, const char *b)
{
	size_t la = strlen(a);
	char *c = malloc(la + 1);
	strcpy(c, a);
	reverse(c, la);
	ASRT_strz(c, b);
	free(c);
}

int main(int argc, char const *argv[])
{
	test_reverse("", "");
	test_reverse("ab", "ba");
	test_reverse("abc", "cba");
	test_reverse("abcd", "dcba");
	test_reverse("accde", "edcca");
	test_reverse("Hello World!", "!dlroW olleH");
	printf("All Ok.\n");
	return 0;
}