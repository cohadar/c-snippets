/*
 *  Classic insertion sort algorithm, best used on small array sizes (0..20)
 *  Template letter: E
 */

/* returns true if a > b */
typedef bool (*insertionsort_gt)(const E a, const E b);

/***/
void insertionsort(E *arr, size_t length, insertionsort_gt gt)
{
	for (size_t i = 1; i < length; i++) {
		E x = arr[i];
		size_t j = i;
		while ((j > 0) && gt(arr[j-1], x)) {
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = x;
	}
}