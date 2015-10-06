/*
 * Simple HashMap implementation with C string keys, no auto resizing/rehashing.
 * Template letter: V
 */
typedef struct HashMapEntry {
	const char *key;
	V value;
	uint32_t hash;
	struct HashMapEntry *next;
} HashMapEntry;

typedef struct {
	uint32_t cap;
	uint32_t size;
	V default_value;
	HashMapEntry *data;
} HashMap;

typedef void (*HasMapEntry_func)(HashMapEntry *e, void *data);

uint32_t HashMap_hash(const char *key) {
	if (key == NULL) {
		return 0;
	}
	uint32_t h = 0;
	for (; *key; key++) {
		h = (31 * h) + (*key);
	}
	h ^= (h >> 20) ^ (h >> 12);
	return h ^ (h >> 7) ^ (h >> 4);
}

HashMap *HashMap_new(uint32_t cap, V default_value)
{
	assert(cap > 0);
	HashMap *o = malloc(sizeof(*o));
	assert(o);
	o->cap = cap;
	o->size = 0;
	o->default_value = default_value;
	o->data = calloc(cap, sizeof(*o->data));
	assert(o->data);
	for (uint32_t i = 0; i < cap; i++) {
		o->data[i].key = NULL;
		o->data[i].value = default_value;
		o->data[i].next = NULL;
	}
	return o;
}

void HashMap_delete(HashMap *o)
{
	assert(o);
	for (uint32_t i = 0; i < o->cap; i++) {
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
 * @returns old value on key if found else default_value.
 */
V HashMap_put(HashMap *o, const char *key, V value)
{
	assert(o);
	assert(key);
	uint32_t hash = HashMap_hash(key);
	uint32_t i = hash % o->cap;
	HashMapEntry *e = o->data + i;
	while (e) {
		if (e->key != NULL && strcmp(e->key, key) == 0) {
			V old = e->value;
			e->value = value;
			return old;
		} else {
			e = e->next;
		}
	}
	e = o->data + i;
	while (e) {
		if (e->key == NULL) {
			e->key = key;
			e->hash = hash;
			e->value = value;
			o->size++;
			return o->default_value;
		} else {
			e = e->next;
		}
	}
	e = malloc(sizeof(*e));
	assert(e);
	e->key = key;
	e->hash = hash;
	e->value = value;
	e->next = o->data[i].next;
	o->data[i].next = e;
	o->size++;
	return o->default_value;
}

/*
 * @returns value on key if found else default_value.
 */
V HashMap_get(HashMap *o, const char *key)
{
	assert(o);
	assert(key);
	uint32_t i = HashMap_hash(key) % o->cap;
	HashMapEntry *e = o->data + i;
	while (e) {
		if (e->key != NULL && strcmp(e->key, key) == 0) {
			return e->value;
		} else {
			e = e->next;
		}
	}
	return o->default_value;
}

/*
 * @returns removed value if key found else default_value.
 * remove does not release any entries, this keeps iterators safe.
 * if you need to reclaim bucket memory your capacity was not correct anyways.
 */
V HashMap_remove(HashMap *o, const char *key)
{
	assert(key);
	uint32_t i = HashMap_hash(key) % o->cap;
	HashMapEntry *e = o->data + i;
	while (e) {
		if (e->key != NULL && strcmp(e->key, key) == 0) {
			V removed = e->value;
			e->key = NULL;
			e->value = o->default_value;
			o->size--;
			return removed;
		} else {
			e = e->next;
		}
	}
	return o->default_value;
}

/*
 * Resizes HashMap to new capacity.
 * How people handle iterator invalidation on resize?
 */
void HashMap_resize(HashMap *o, uint32_t new_cap) {
	assert(o);
	assert(new_cap > 0);

	HashMap *temp = HashMap_new(new_cap, o->default_value);

	for (uint32_t i = 0; i < o->cap; i++) {
		HashMapEntry *e = o->data + i;
		while (e) {
			if (e->key != NULL) {
				HashMap_put(temp, e->key, e->value);
			}
			e = e->next;
		}
	}
	uint32_t temp_cap = o->cap;
	o->cap = temp->cap;
	temp->cap = temp_cap;

	uint32_t temp_size = o->size;
	o->size = temp->size;
	temp->size = temp_size;

	HashMapEntry *temp_data = o->data;
	o->data = temp->data;
	temp->data = temp_data;

	HashMap_delete(temp);
}

/***/
uint32_t HashMap_size(HashMap *o)
{
	return o->size;
}

/***/
void HashMap_clear(HashMap *o)
{
	assert(o);
	for (uint32_t i = 0; i < o->cap; i++) {
		HashMapEntry *e = o->data + i;
		while (e) {
			e->key = NULL;
			e = e->next;
		}
	}
	o->size = 0;
}

/***/
void HashMap_forAll(HashMap *o, HasMapEntry_func func, void *data)
{
	assert(o);
	for (uint32_t i = 0; i < o->cap; i++) {
		HashMapEntry *e = o->data + i;
		while (e) {
			if (e->key != NULL) {
				func(e, data);
				if (e->key == NULL) {
					o->size--;
				}
			}
			e = e->next;
		}
	}
}

