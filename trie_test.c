#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define TRIE_ALPHABET_SIZE 128
typedef int V;
#include "trie.h"

int main(int argc, char const *argv[])
{
	Trie *t = Trie_new();
	Trie_delete(t);
	Trie_add(t, "abc", 1);
	Trie_add(t, "abd", 1);
	Trie_add(t, "bcd", 1);
	Trie_add(t, "bfg", 1);
	Trie_add(t, "bfz", 1);
	assert(Trie_hasprefix(t, "a"));
	assert(Trie_hasprefix(t, "ab"));
	assert(Trie_hasprefix(t, "abd"));
	assert(Trie_hasprefix(t, "abz") == false);
	assert(Trie_get(t, "abd"));
	assert(Trie_get(t, "bfg"));
	assert(Trie_get(t, "abx") == 0);
	assert(Trie_get(t, "a") == 0);
	assert(Trie_get(t, "") == 0);
	Trie_add(t, "", 5);
	assert(Trie_get(t, "") == 5);
	return 0;
}
