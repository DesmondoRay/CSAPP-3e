/**
 * homework 4.49
 */

#include <stdio.h>

void bubble_sort(long *data, long *data_last);

// test
int main(void)
{
	long data[4] = {3, 1, 4, 2};
	bubble_sort(data, data+3);
	for (size_t i = 0; i < 4; i++)
		printf("%ld\n", data[i]);
	return 0;
}

void bubble_sort(long *data, long *data_last)
{
	long *i, *last;
	for (last = data_last; last > data; last--) {
		for (i = data; i < last; i++) {
			long bigger = (*(i+1) < *i) ? *i : *(i+1);
			*i = *i ^ bigger ^ *(i+1);
			*(i+1) = bigger;
		}
	}
}

/* test results:
1
2
3
4
*/