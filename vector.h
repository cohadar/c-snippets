/*
 * Resizeable array.
 * Template letter: E
 */
#include <stdlib.h>
#include <assert.h>

typedef struct {
	E *data;
	size_t length;
} Vector;

Vector *vector_new()
{
	Vector *o = malloc(sizeof(*o));
	assert(o);
	o->length = 0;
	o->data = NULL;
	return o;
}

void vector_delete(Vector *o)
{
	if (o->data) {
		free(o->data);
		o->data = NULL;
	}
	free(o);
}

void vector_push(Vector *o, E element)
{
	o->data = realloc(o->data, ++o->length * sizeof(E));
	assert(o->data);
	o->data[o->length - 1] = element;
}

E vector_pop(Vector *o)
{
	assert(o->length > 0);
	E ret = o->data[--o->length];
	if (o->length > 0) {
		o->data = realloc(o->data, o->length * sizeof(E));
		assert(o->data);
	}
	return ret;
}

