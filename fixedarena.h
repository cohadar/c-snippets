/*
 * Memory arena for allocating fixed size chunks. Single allocations - Mass deallocation.
 * Guaranteed zeroed memory.
 */

typedef struct FixedArenaPage {
	size_t index;
	char *data;
	struct FixedArenaPage *next;
} FixedArenaPage;

typedef struct {
	size_t page_size;
	size_t fixed_size;
	size_t max_intances; // per page
	FixedArenaPage *head;
} FixedArena;

FixedArenaPage *FixedArenaPage_new(size_t page_size)
{
	FixedArenaPage *node = malloc(sizeof(*node));
	assert(node);
	// zero index is reserved to detect bad free calls
	node->index = 1;
	node->data = calloc(1, page_size);
	node->next = NULL;
	assert(node->data);
	return node;
}

// returns next node or NULL
FixedArenaPage *FixedArenaPage_delete(FixedArenaPage *node)
{
	assert(node);
	free(node->data);
	node->data = NULL;
	FixedArenaPage *next = node->next;
	free(node);
	return next;
}

FixedArena *FixedArena_new(size_t fixed_size, size_t alignment)
{
	FixedArena *o = malloc(sizeof(*o));
	assert(o);
	// min 1K instances per page, or min page size 8K
	o->page_size = (1024 * fixed_size < 8192) ? 8192 : 1024 * fixed_size;
	o->fixed_size = (fixed_size / alignment + 1) * fixed_size;
	o->max_intances = o->page_size / o->fixed_size;
	o->head = FixedArenaPage_new(o->page_size);
	return o;
}

void *FixedArena_alloc(FixedArena *o)
{
	if (o->head->index >= o->max_intances) {
		FixedArenaPage *newpage = FixedArenaPage_new(o->page_size);
		newpage->next = o->head;
		o->head = newpage;
	}
	void *ret = o->head->data + (o->head->index * o->fixed_size);
	o->head->index++;
	return ret;
}

void FixedArena_delete(FixedArena *o)
{
	FixedArenaPage *curr = o->head;
	while (curr) {
		curr = FixedArenaPage_delete(curr);
	}
	o->head = NULL;
	free(o);
}

// I had a FixedArena_clear function here that just zeroed out pages but it turned out slower than FixedArena_delete.
