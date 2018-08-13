/**
 * homework 4.48
 * 现实冒泡排序，在交换数组元素值时，不使用跳转，最多使用3次条件传送。
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
			int less = (*(i+1) < *i);
			long t = less ? *(i+1) : 0;
			*(i+1) = less ? *i : *(i+1);
			*i = less ? t : *i;
		}
	}
}

/* test result:
1
2
3
4
*/