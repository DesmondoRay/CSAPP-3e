/*
 * Return 1 when x can be represented as an n-bit, 2's-complement number;
 * 0 otherwise.
 * Assume 1 <= n <= w
 */
 
#include <stdio.h>
#include <assert.h>

int fits_bits(int x, int n)
{
	int neg = x >> (n - 1);
	int pos = x >> (n - 1);
	return neg == -1 || pos == 0;
}

int main(void)
{
	assert(fits_bits(2, 2) == 0);
	assert(fits_bits(-2, 2));
	assert(fits_bits(2, 3));
	assert(fits_bits(-129, 8) == 0);
	assert(fits_bits(-128, 8));
	assert(fits_bits(128, 8) == 0);
	
	return 0;
}