/*
	Return 1 when x contains an odd number of 1s; 0 otherwise.
	Assume w = 32
*/

#include <stdio.h>

int odd_ones(unsigned x)
{
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x & 0x1;
}

int main(void)
{
	unsigned x = 0x01010111;
	unsigned y = 0x01010101;
	
	printf("%d\n", odd_ones(x));
	printf("%d\n", odd_ones(y));
	return 0;
}