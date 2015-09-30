/*
 * Singly linked list. (with dummy head)
 * Template letter: E
 * TODO: Storm.dll lists
 */
typedef struct SNode {
	E data;
	struct SNode *next;
} SNode;

typedef struct {
	struct SNode *_head;
	struct SNode *_tail;
	size_t _len;
} SList;

SList *SList_new() {
	SList *o = malloc(sizeof(*o));
	assert(o);
	SNode *dummy = malloc(sizeof(*dummy));
	assert(dummy);
	o->_head = dummy;
	o->_tail = dummy;
	o->_len = 0;
	dummy->next = NULL;
	return o;
}

void SList_delete(SList *o)
{
	SNode *p = o->_head;
	while (p) {
		SNode *tmp = p->next;
		// paranoid nulling
		p->next = NULL;
		free(p);
		p = tmp;
	}
	// paranoid nulling
	o->_head = NULL;
	o->_tail = NULL;
	o->_len = 0;
	free(o);
}

void SList_appendArray(SList *o, E *arr, size_t len)
{
	assert(len >= 0);
	SNode *p = o->_tail;
	for (size_t i = 0; i < len; i++) {
		p->next = malloc(sizeof(*p->next));
		assert(p->next);
		p = p->next;
		p->data = arr[i];
		o->_len++;
	}
	p->next = NULL;
	o->_tail = p;
}

E *SList_mallocArray(SList *o, size_t *len)
{
	assert(o);
	assert(len);
	*len = o->_len;
	E *arr = NULL;
	if (o->_len > 0) {
		arr = malloc(o->_len * sizeof(*arr));
	}
	SNode *p = o->_head->next;
	size_t i = 0;
	while (p) {
		arr[i++] = p->data;
		p = p->next;
	}
	assert(i == o->_len);
	return arr;
}

// SList* SList_insertionSort(SList *o)
// {
// 	if (o->_len < 2) return o;
// 	SNode *h = o->_head;
// 	SNode *t = o->_head->next;
// }
