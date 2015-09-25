/*
 * Shuffle array with uniform permutation.
 * Template letter: E
 */

// return random index in range [0, n)
typedef size_t (*shuffle_random_index)(size_t n);

// shuffle array
void shuffle(E *arr, size_t length, shuffle_random_index rnd)
{
	if (length < 2) {
		return;
	}
	for (size_t i = length - 1; i > 0; i--) {
		size_t j = rnd(i + 1);
		E tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
}