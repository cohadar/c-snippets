/*
 *  Mostly junk here, this file does not even compile properly.
 */

// clever random seed
srand( time(NULL) ^ (int)&main );

// Returns an uniform random integer in the range [0, n).
int random_int( int n ) {
	assert ( n > 0 );
	int cutoff = RAND_MAX % n;
	int ret;
	do ret = rand(); while ( ret <= cutoff );
	return ret % n;
}

// Returns an integer in the range [low, high].
int random_int2( int low, int high ) {
	assert ( low >= 0 && high >= 0 && low <= high );
	return low + random_int( high - low + 1 );
}


// num_switches -  num_ prefix for simple integer values
// engines_length - _length postfix for array lengths

int read_int() {
	int ret;
	scanf("%d\n", &ret);
	return ret;
}

char* read_string() {
	char* ret = malloc(MAX_NAME_LEN + 10);
	fgets(ret, MAX_NAME_LEN, stdin);
	ret[strcspn(ret, "\r\n")] = 0;
	return ret;
}


// fast array init
memset(used, 0, sizeof(used));

// part of stddef.h
offsetof(struct njak, x);