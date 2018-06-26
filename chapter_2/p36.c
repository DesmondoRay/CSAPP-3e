#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int tmult_ok(int x, int y);

int main(void)
{
	int x, y;
	
	x = 100;
	y = INT_MAX;
	
	printf("%d\n", tmult_ok(x, y));
	
	return 0;
}

int tmult_ok(int x, int y)
{
	int64_t p = (int64_t) x * y;
	return p == (int) p;
}