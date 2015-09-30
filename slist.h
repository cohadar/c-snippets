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

// TODO: there is an error is here, tail is not updated but it should be.
SList* _SList_insertInSorted(SList *head, SList *tail, SList *toInsert)
{
	if (toInsert->data > head->data) {
		SList *l = head;
		SList *r = head->next;
		while (r != head) {
			if (toInsert->data > r->data) {
				l = r;
				r = r->next;
			} else {
				l->next = toInsert;
				toInsert->next = r;
				return head;
			}
		}
		l->next = toInsert;
		toInsert->next = head;
		return head;
	} else {
		toInsert->next = head;
		tail->next = toInsert;
		return toInsert;
	}
}

SList* SList_insertionSort(SList *o)
{
	assert(o);
	if (o->next == o) return o;
	SList *head = o;
	SList *tail = o;
	SList *p = o->next;
	head->next = head;
	while (p != o) {
		SList *toInsert = p;
		p = p->next;
		head = _SList_insertInSorted(head, tail, toInsert);
	}
	return head;
}
