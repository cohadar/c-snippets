/*
 * Resizeable array. Interface based on Python list.
 */
typedef struct {
	void **data;
	size_t len;
	size_t cap;
} Vector;

typedef void* (*Vector_mapfunc)(void *element, void *closure);
typedef void (*Vector_freefunc)(void *element);

Vector *Vector_new()
{
	Vector *o = malloc(sizeof(*o));
	assert(o);
	o->len = 0;
	o->cap = 0;
	o->data = NULL;
	return o;
}

void Vector_clear(Vector *o, Vector_freefunc func) {
	assert(o);
	if (o->data) {
		if (func) {
			for (size_t i = 0; i < o->len; i++) {
				func(o->data[i]);
			}
		}
		free(o->data);
		o->data = NULL;
	}
	o->len = 0;
	o->cap = 0;
}

void Vector_delete(Vector *o, Vector_freefunc func)
{
	assert(o);
	Vector_clear(o, func);
	free(o);
}

void Vector_append(Vector *o, void *element)
{
	assert(o);
	if (o->len == o->cap) {
		o->cap = (o->cap == 0) ? 256 : o->cap * 2;
		o->data = realloc(o->data, o->cap * sizeof(*o->data));
		assert(o->data);
	}
	o->data[o->len] = element;
	o->len++;
}

void Vector_extend(Vector *o, Vector *v)
{
	assert(o);
	for (size_t i = 0; i < v->len; i++) {
		Vector_append(o, v->data[i]);
	}
}

void *Vector_pop(Vector *o)
{
	assert(o);
	assert(o->len > 0);
	void *ret = o->data[--o->len];
	if (o->len > 0 && 2 * o->len < o->cap) {
		o->cap /= 2;
		o->data = realloc(o->data, o->cap * sizeof(*o->data));
		assert(o->data);
	}
	return ret;
}

size_t Vector_length(Vector *o)
{
	assert(o);
	return o->len;
}

void *Vector_map(Vector *o, Vector_mapfunc func, void *closure)
{
	assert(o);
	Vector *ret = Vector_new();
	for (size_t i = 0; i < o->len; i++) {
		void *mapped = func(o->data[i], closure);
		if (mapped) {
			Vector_append(ret, mapped);
		}
	}
	return ret;
}
