/*
 * Simple HashMap implementation, no auto resizing/rehashing.
 * Template letters: K, V
 */
typedef struct HashEntry {
	K key;
	V value;
	struct HashEntry *next;
} HashEntry;

typedef size_t (*HashMap_hash)(K key);

typedef struct {
	size_t cap;
	HashMap_hash hash;
	K null_key;
	V null_value;
	HashEntry *data;
} HashMap;

HashMap *HashMap_new(size_t cap, HashMap_hash hash, K null_key, V null_value)
{
	assert(cap > 0);
	assert(hash);
	HashMap *o = malloc(sizeof(*o));
	assert(o);
	o->cap = cap;
	o->hash = hash;
	o->null_key = null_key;
	o->null_value = null_value;
	o->data = calloc(cap, sizeof(*o->data));
	assert(o->data);
	for (size_t i = 0; i < cap; i++) {
		o->data[i].key = null_key;
		o->data[i].value = null_value;
		o->data[i].next = NULL;
	}
	return o;
}

void HashMap_delete(HashMap *o)
{
	assert(o);
	for (size_t i = 0; i < o->cap; i++) {
		HashEntry *p = o->data[i].next;
		while (p) {
			HashEntry *t = p->next;
			free(p);
			p = t;
		}
	}
	free(o->data);
	o->cap = 0;
	free(o);
}

V HashMap_put(HashMap *o, K key, V value)
{
	assert(key != o->null_key);
	size_t i = o->hash(key);
	assert(i < o->cap);
	if (o->data[i].key == key) {
		V old = o->data[i].value;
		o->data[i].value = value;
		return old;
	} else if (o->data[i].key == o->null_key) {
		o->data[i].key = key;
		o->data[i].value = value;
		return o->null_value;
	} else {
		HashEntry *e = o->data[i].next;
		while (e) {
			if (e->key == key) {
				V old = e->value;
				e->value = value;
				return old;
			} else {
				e = e->next;
			}
		}
		e = malloc(sizeof(*e));
		assert(e);
		e->key = key;
		e->value = value;
		e->next = o->data[i].next;
		o->data[i].next = e;
		return o->null_value;
	}
}

V HashMap_get(HashMap *o, K key)
{
	assert(key != o->null_key);
	size_t i = o->hash(key);
	assert(i < o->cap);
	if (o->data[i].key == key) {
		return o->data[i].value;
	} else if (o->data[i].key == o->null_key) {
		return o->null_value;
	} else {
		HashEntry *e = o->data[i].next;
		while (e) {
			if (e->key == key) {
				return e->value;
			} else {
				e = e->next;
			}
		}
		return o->null_value;
	}
}
