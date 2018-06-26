/*
 * 写出函数 threefourths 的代码，对于整数参数x，计算3/4x, 向零舍入。不会溢出。
 */
 
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <inttypes.h>

int threefourths(int x)
{
	int64_t result = ((int64_t) x << 1) + x;
	
	int sign = (x & INT_MIN) == INT_MIN;
	int mask = (1 << 2) - 1;
	int bias = -sign & mask;
	
	return (result + bias) >> 2;
}

int main(void)
{
	int x = INT_MIN;
	int y = INT_MAX;
	int m = 3;
	int n = -3;
	
	assert(threefourths(x) != 3 * x / 4);
	assert(threefourths(y) != 3 * y / 4);
	assert(threefourths(m) == 3 * m / 4);
	assert(threefourths(n) == 3 * n / 4);
	
	return 0;
}