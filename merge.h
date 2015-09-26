/*
 *  Classic merge sort algorithm, uses insertionsort for small chunks
 *  Template letter: E
 */

/* empiric value that determines when we switch from merge to insertion sort */
#define _MERGE_INSERTION_BORDER 48

/*
 * merge adjoining array segments [l..m) [m..r)
 * we replaced two loops with memcpy because it is faster when sizeof(E) > sizeof(intmax_t)
 */
 void merge_segments(E *arr, size_t l, size_t m, size_t r, insertionsort_gt gt)
 {
 	E *buf = malloc((r - l) * sizeof(*buf));
 	assert(buf);
 	size_t il = l;
 	size_t ir = m;
 	size_t ib = 0;
 	while (il < m && ir < r) {
 		if (gt(arr[il], arr[ir])) {
 			buf[ib++] = arr[ir++];
 		} else {
 			buf[ib++] = arr[il++];
 		}
 	}
 	// while (il < m) {
 	// 	arr[il + r - m] = arr[il];
 	// 	il++;
 	// }
 	memcpy(&arr[il + r - m], &arr[il], (m - il) * sizeof(E)); // same as while above
 	// for (size_t i = 0; i < ib; i++) {
 	// 	arr[l + i] = buf[i];
 	// }
 	memcpy(arr + l, buf, ib * sizeof(E)); // same as for above
 	free(buf);
 }

/* mergesort an open segment [l..r) */
void merge_sort2(E *arr, size_t l, size_t r, insertionsort_gt gt)
{
	if (r - l <= _MERGE_INSERTION_BORDER) {
		insertionsort(arr + l, r - l, gt);
	} else {
		size_t m = (l + r) / 2;
		merge_sort2(arr, l, m, gt);
		merge_sort2(arr, m, r, gt);
		merge_segments(arr, l, m, r, gt);
	}
}

/* nice public interface */
void merge_sort(E *arr, size_t length, insertionsort_gt gt)
{
	merge_sort2(arr, 0, length, gt);
}
