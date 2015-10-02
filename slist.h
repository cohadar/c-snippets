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
	struct SNode *head;
	struct SNode *tail;
	size_t len;
} SList;

SList *SList_new() {
	SList *o = malloc(sizeof(*o));
	assert(o);
	SNode *dummy = malloc(sizeof(*dummy));
	assert(dummy);
	o->head = dummy;
	o->tail = dummy;
	o->len = 0;
	dummy->next = NULL;
	return o;
}

void SList_delete(SList *o)
{
	SNode *p = o->head;
	while (p) {
		SNode *tmp = p->next;
		// paranoid nulling
		p->next = NULL;
		free(p);
		p = tmp;
	}
	// paranoid nulling
	o->head = NULL;
	o->tail = NULL;
	o->len = 0;
	free(o);
}

void SList_verify(SList *o)
{
	assert(o);
	assert(o->head);
	assert(o->tail);
	size_t count = 0;
	SNode *p = o->head;
	while (p->next) {
		p = p->next;
		count++;
	}
	assert(count == o->len);
	assert(p == o->tail);
}

void SList_appendArray(SList *o, E *arr, size_t len)
{
	assert(len >= 0);
	SNode *p = o->tail;
	for (size_t i = 0; i < len; i++) {
		p->next = malloc(sizeof(*p->next));
		assert(p->next);
		p = p->next;
		p->data = arr[i];
		o->len++;
	}
	p->next = NULL;
	o->tail = p;
}

E *SList_mallocArray(SList *o, size_t *len)
{
	assert(o);
	assert(len);
	*len = o->len;
	E *arr = NULL;
	if (o->len > 0) {
		arr = malloc(o->len * sizeof(*arr));
	}
	SNode *p = o->head->next;
	size_t i = 0;
	while (p) {
		arr[i++] = p->data;
		p = p->next;
	}
	assert(i == o->len);
	return arr;
}

void SList_insertionSort(SList *o)
{
	if (o->len < 2) return;
	SNode *t = o->head->next->next;
	o->head->next->next = NULL;
	o->tail = o->head->next;
	while (t) {
		SNode *l = o->head;
		while (l->next && t->data > l->next->data) {
			l = l->next;
		}
		SNode *tn = t->next;
		SNode *ln = l->next;
		l->next = t;
		t->next = ln;
		if (ln == NULL) {
			o->tail = t;
		}
		t = tn;
	}
}
