/* Declaration of data type where 4 bytes are packed into an unsigned. */

#include <stdio.h>
#include <assert.h>


typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
	unsigned temp = word >> (bytenum << 3) & 0xFF;
	int n = (sizeof(int) - 1) >> 3;
	temp = temp << n;
	return (int) temp >> n;
}

int main(void)
{
	unsigned x = 0xFF11;
	
	assert(xbyte(x, 0) == 0x11);
	assert(xbyte(x, 1) == -1);
	
	return 0;
}