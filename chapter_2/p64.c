/*
	Return 1 when any odd bit of x equals 1; 0 otherwise.
*/

#include <stdio.h>

int any_odd_one(unsigned x)
{
	unsigned mask = 0x55555555;
	return (mask & x) != 0;
}

int main(void)
{
	unsigned x = 0xaaaaaaaa;
	unsigned y = 0x5;
	
	printf("%d\n", any_odd_one(x));
	printf("%d\n", any_odd_one(y));
	
	return 0;
}