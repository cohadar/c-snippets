/*
 * Heap, implicit heap in array.
 * Template letter: E
 *
 * On 100 * MEGA of uint32_t
 * qsort:     21.2s
 * heap_sort: 37.4s
 */

/* returns true if a > b */
typedef bool (*heap_gt)(const E a, const E b);

/* root of a heap is not max, sink it down until heap is restored */
void heap_sinkroot(E *arr, size_t len, heap_gt gt, size_t r)
{
	size_t m = r;
	for(;;) {
		size_t c = 2 * r + 1;
		if (c < len && gt(arr[c], arr[m])) {
			m = c;
		}
		c++;
		if (c < len && gt(arr[c], arr[m])) {
			m = c;
		}
		if (m == r) {
			break;
		}
		E tmp = arr[m];
		arr[m] = arr[r];
		arr[r] = tmp;
		r = m;
	}
}

/* make a heap from random array, arr[0] is max element according to gt */
void heap_make(E *arr, size_t len, heap_gt gt)
{
	if (len < 2) {
		return;
	}
	size_t last_parent = (len - 1 - 1) / 2;
	for (size_t pp1 = last_parent + 1; pp1 > 0; pp1--) {
		heap_sinkroot(arr, len, gt, pp1 - 1);
	}
}

/* sort array using implicit heap structure */
void heap_sort(E *arr, size_t len, heap_gt gt)
{
	heap_make(arr, len, gt);
	for (size_t i = len - 1; i > 0; i--) {
		E max = arr[0];
		arr[0] = arr[i];
		arr[i] = max;
		heap_sinkroot(arr, i, gt, 0);
	}
}
