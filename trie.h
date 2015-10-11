/*
 * Simple char trie, memory wastefull.
 * Template letters: V, TRIE_ALPHABET_SIZE
 */

 typedef struct Trie {
 	V value;
 	struct Trie *children[TRIE_ALPHABET_SIZE];
 } Trie;

 Trie *Trie_new()
 {
 	Trie *o = malloc(sizeof(*o));
 	assert(o);
 	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
 		o->children[i] = NULL;
 	}
 	o->value = 0;
 	return o;
 }

 void Trie_delete(Trie *o)
 {
 	assert(o);
 	for (int i = 0; i < TRIE_ALPHABET_SIZE; i++) {
 		if (o->children[i] != NULL) {
 			Trie_delete(o->children[i]);
 		}
 	}
 	free(o);
 }

void Trie_add(Trie *o, const char *word, V value)
{
	assert(o);
	assert(word);
	size_t n = strlen(word);
	size_t i = 0;
	while (i < n) {
		unsigned char c = (unsigned char)word[i];
		assert(c < TRIE_ALPHABET_SIZE);
		if (o->children[c] == NULL) {
			o->children[c] = malloc(sizeof(*o->children[c]));
			assert(o->children[c]);
			o = o->children[c];
			o->value = 0;
		} else {
			o = o->children[c];
		}
		i++;
	}
	o->value = value;
}

bool Trie_hasprefix(Trie *o, const char *word)
{
	assert(o);
	assert(word);
	size_t n = strlen(word);
	size_t i = 0;
	while (i < n) {
		unsigned char c = (unsigned char)word[i];
		assert(c < TRIE_ALPHABET_SIZE);
		if (o->children[c] == NULL) {
			return false;
		} else {
			o = o->children[c];
		}
		i++;
	}
	return true;
}

V Trie_get(Trie *o, const char *word)
{
	assert(o);
	assert(word);
	size_t n = strlen(word);
	size_t i = 0;
	while (i < n) {
		unsigned char c = (unsigned char)word[i];
		assert(c < TRIE_ALPHABET_SIZE);
		if (o->children[c] == NULL) {
			break;
		} else {
			o = o->children[c];
		}
		i++;
	}
	if (i < n) {
		return 0;
	}
	return o->value;
}

