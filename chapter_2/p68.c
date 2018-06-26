/*
 * Mask with least signficant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */

#include <stdio.h>
#include <assert.h>

int lower_one_mask(int n)
{
	int w = sizeof(int) << 3;
	int x = -1;
	
	return (unsigned) x >> (w - n - 1) >> 1;
}

int main(void)
{
	assert(lower_one_mask(6) == 0x3F);
	assert(lower_one_mask(17) == 0x1FFFF);
	
	return 0;
}