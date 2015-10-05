/*
 * Simple HashMap implementation, no auto resizing/rehashing.
 * Template letters: K, V
 */
typedef struct HashMapEntry {
	K key;
	V value;
	struct HashMapEntry *next;
} HashMapEntry;

typedef size_t (*HashMapKey_hash)(K key);
typedef bool (*HashMapKey_eq)(K a, K b);  // TODO: use this, first check why this works without it!
typedef void (*HasMapEntry_func)(HashMapEntry *e, void *data);

typedef struct {
	size_t cap;
	size_t size;
	HashMapKey_hash hash;
	K null_key;
	V null_value;
	HashMapEntry *data;
} HashMap;

HashMap *HashMap_new(size_t cap, HashMapKey_hash hash, K null_key, V null_value)
{
	assert(cap > 0);
	assert(hash);
	HashMap *o = malloc(sizeof(*o));
	assert(o);
	o->cap = cap;
	o->size = 0;
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
		HashMapEntry *e = o->data[i].next;
		while (e) {
			HashMapEntry *t = e->next;
			free(e);
			e = t;
		}
	}
	free(o->data);
	o->cap = 0;
	o->size = 0;
	free(o);
}

/*
 * @returns old value on key if found else null_value.
 */
V HashMap_put(HashMap *o, K key, V value)
{
	assert(key != o->null_key);
	size_t i = o->hash(key) % o->cap;
	HashMapEntry *e = o->data + i;
	while (e) {
		if (e->key == key) {
			V old = e->value;
			e->value = value;
			return old;
		} else {
			e = e->next;
		}
	}
	while (e) {
		if (e->key == o->null_key) {
			e->value = value;
			o->size++;
			return o->null_value;
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
	o->size++;
	return o->null_value;
}

/*
 * @returns value on key if found else null_value.
 */
V HashMap_get(HashMap *o, K key)
{
	assert(key != o->null_key);
	size_t i = o->hash(key) % o->cap;
	HashMapEntry *e = o->data + i;
	while (e) {
		if (e->key == key) {
			return e->value;
		} else {
			e = e->next;
		}
	}
	return o->null_value;
}

/*
 * @returns removed value if key found else null_value.
 * remove does not release any entries, this keeps iterators safe.
 * if you need to reclaim bucket memory your capacity was not correct anyways.
 */
V HashMap_remove(HashMap *o, K key)
{
	assert(key != o->null_key);
	size_t i = o->hash(key) % o->cap;
	HashMapEntry *e = o->data + i;
	while (e) {
		if (e->key == key) {
			V removed = e->value;
			e->key = o->null_key;
			e->value = o->null_value;
			o->size--;
			return removed;
		} else {
			e = e->next;
		}
	}
	return o->null_value;
}

/***/
size_t HashMap_size(HashMap *o)
{
	return o->size;
}


/***/
void HashMap_clear(HashMap *o)
{
	assert(o);
	for (size_t i = 0; i < o->cap; i++) {
		HashMapEntry *e = o->data + i;
		while (e) {
			e->key = o->null_key;
			e = e->next;
		}
	}
	o->size = 0;
}

/***/
void HashMap_forAll(HashMap *o, HasMapEntry_func func, void *data)
{
	assert(o);
	for (size_t i = 0; i < o->cap; i++) {
		HashMapEntry *e = o->data + i;
		while (e) {
			if (e->key != o->null_key) {
				func(e, data);
				if (e->key == o->null_key) {
					o->size--;
				}
			}
			e = e->next;
		}
	}
}

