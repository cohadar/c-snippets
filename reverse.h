/*
 * Reverse an array of elements.
 * Template letter: E
 */
void reverse(E *arr, const size_t length)
{
	for (size_t i = 0; i < length / 2; i++) {
		E tmp = arr[i];
		arr[i] = arr[length - i - 1];
		arr[length - i - 1] = tmp;
	}
}
