/*
 * Singly linked list. (circular, with head pivot)
 * Template letter: E
 * TODO: Storm.dll lists
 */
typedef struct SList {
	E data;
	struct SList *next;
} SList;

SList *SList_new() {
	SList *o = malloc(sizeof(*o));
	assert(o);
	// Data is uninitialized in pivot.
	// Empty list is represented as a pivot pointing to itself.
	o->next = o;
	return o;
}

void SList_delete(SList *o)
{
	assert(o);
	SList *p = o->next;
	while (p != o) {
		SList *tmp = p->next;
		free(p);
		p = tmp;
	}
	free(o);
}

void SList_appendArray(SList *o, E *arr, size_t len)
{
	assert(len >= 0);
	assert(o);
	SList *p = o;
	for (size_t i = 0; i < len; i++) {
		p->next = malloc(sizeof(*p->next));
		assert(p->next);
		p = p->next;
		p->data = arr[i];
	}
	p->next = o;
}

E *SList_mallocArray(SList *o, size_t *len)
{
	assert(o);
	assert(len);
	*len = 0;
	E *arr = NULL;
	SList *p = o->next;
	while (p != o) {
		arr = realloc(arr, ++(*len));
		assert(arr);
		arr[*len - 1] = p->data;
		p = p->next;
	}
	return arr;
}
