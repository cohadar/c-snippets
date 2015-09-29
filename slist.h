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
	SList *pivot = malloc(sizeof(*pivot));
	assert(pivot);
	// Data is uninitialized in pivot.
	// Empty list is pivot pointing to itself.
	pivot->next = pivot;
	return pivot;
}

void SList_delete(SList *lst)
{
	assert(lst);
	SList *pivot = lst;
	lst = pivot->next;
	while (pivot != lst) {
		SList *tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	free(pivot);
}

void SList_appendArray(SList *pivot, E *arr, size_t len)
{
	assert(len >= 0);
	assert(pivot);
	SList *l = pivot;
	for (size_t i = 0; i < len; i++) {
		l->next = malloc(sizeof(*l->next));
		assert(l->next);
		l = l->next;
		l->data = arr[i];
	}
	l->next = pivot;
}

E *SList_mallocArray(SList *lst, size_t *len)
{
	*len = 0;
	E *arr = NULL;
	SList *pivot = lst;
	lst = pivot->next;
	while (lst != pivot) {
		arr = realloc(arr, ++(*len));
		assert(arr);
		arr[*len - 1] = lst->data;
		lst = lst->next;
	}
	return arr;
}
