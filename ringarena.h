/*
 * Circular list of memory segments that are reused and reallocated after some time.
 * Best used for temporary buffers, the main advantage is that you do not need to manually free memory.
 */
#define _RING_ARENA_MAX_ALIGN 16

typedef struct {
	size_t _size;
	size_t _last;
	void** _ring;
} RingArena;

RingArena *ringarena_new(size_t _size)
{
	assert(_size > 0);
	RingArena *o = malloc(sizeof(*o));
	assert(o);
	o->_size = _size;
	o->_ring = malloc(_size * sizeof(*o->_ring));
	assert(o->_ring);
	for (size_t i = 0; i < _size; i++) {
		o->_ring[i] = NULL;
	}
	o->_last = 0;
	return o;
}

void ringarena_delete(RingArena *o)
{
	for (size_t i = 0; i < o->_size; i++) {
		if (o->_ring[i] != NULL) {
			free(o->_ring[i]);
		}
	}
	free(o->_ring);
	o->_ring = NULL;
	o->_size = 0;
	free(o);
}

void *ringarena_next(RingArena *o, size_t _size)
{
	assert(_size > 0);
	o->_last = (o->_last + 1) % o->_size;
	void *p = realloc(o->_ring[o->_last], _RING_ARENA_MAX_ALIGN + _size);
	assert(p);
	o->_ring[o->_last] = p;
	return ((char *)p) + _RING_ARENA_MAX_ALIGN;
}
