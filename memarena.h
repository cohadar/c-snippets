/*
 * Memory arena. Single allocation - Mass dealocation.
 */

typedef struct {
	size_t len;
	size_t cap;
	char **data;
} MemArena;

// allocation offset to detect illegal free of arena strings.
// must be align friendly value.
#define MEMARENA_OFFSET 16

MemArena *MemArena_new()
{
	MemArena *o = malloc(sizeof(*o));
	assert(o);
	o->len = 0;
	o->cap = 256;
	o->data = malloc(o->cap * sizeof(*o->data));
	assert(o->data);
	return o;
}

void MemArena_delete(MemArena *o)
{
	assert(o);
	for (size_t i = 0; i < o->len; i++) {
		free(o->data[i]);
	}
	o->len = 0;
	o->cap = 0;
	free(o->data);
	free(o);
}

void *MemArena_alloc(MemArena *o, size_t size)
{
	if (o->len == o->cap) {
		o->cap *= 2;
		o->data = realloc(o->data, o->cap * sizeof(*o->data));
		assert(o->data);
	}
	char *temp = calloc(1, MEMARENA_OFFSET + size);
	o->data[o->len] = temp;
	o->len++;
	return temp + MEMARENA_OFFSET;
}

