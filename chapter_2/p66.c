/*
	Generate mask indicating leftmost 1 in x. Assume w=32.
	For example, 0xFF00 -> 0x8000 (0xFF00: 1111 1111 0000 0000);
			     0x6600 -> 0x4000 (0x6600: 0110 0110 0000 0000).
	If x = 0, then return 0.
*/

#include <stdio.h>
#include <assert.h>

int leftmost_one(unsigned x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return (x & (~(x >> 1)));
}

int main(void)
{
	assert(leftmost_one(0x0) == 0x0);
	assert(leftmost_one(0xFF00) == 0x8000);
	assert(leftmost_one(0x6600) == 0x4000);
	assert(leftmost_one(0x6000) == 0x4000);
	assert(leftmost_one(0xffffffff) == 0x80000000);
	
	return 0;
}
