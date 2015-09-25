/*
 * Heap, implicit heap in array.
 * Template letter: E
 */

typedef int (*heap_cmp)(const E a, const E b);

void heap_make(E *arr, size_t len)
{
	if (len < 2) {
		return;
	}
	size_t last_parent = (len - 1 - 1) / 2;
	for (size_t pp1 = last_parent + 1; pp1 > 0; pp1--) {
		size_t p = pp1 - 1;
		size_t imax = p;
		for(;;) {
			size_t c = 2 * p + 1;
			if (c < len && arr[c] > arr[imax]) {
				imax = c;
			}
			c++;
			if (c < len && arr[c] > arr[imax]) {
				imax = c;
			}
			if (imax == p) {
				break;
			}
			E tmp = arr[imax];
			arr[imax] = arr[p];
			arr[p] = tmp;
			p = imax;
		}
	}
}
