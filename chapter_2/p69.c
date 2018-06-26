/*
 * Do rotating left shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32:
 *		n = 4 -> 0x23456781, n = 20 -> 0x67812345
 */

#include <stdio.h> 
#include <assert.h>


unsigned rotate_left(unsigned x, int n)
{
	int w = sizeof(int) << 3;
	unsigned temp = x >> (w - n - 1) >> 1;
	
	return (x << n) + temp;
}

int main(void)
{
	assert(rotate_left(0x12345678, 4) == 0x23456781);
	assert(rotate_left(0x12345678, 20) == 0x67812345);
	
	return 0;
}