/*
 * 写出函数 mul3div4 的代码，对于整数参数x，计算3*x/4。可能会产生溢出。
 */
 
// 与p78.c 一起编译
 
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int divide_power2(int x, int k);  // p78.c

int mul3div4(int x)
{
	int result = (x << 1) + x;
	
	return divide_power2(result, 2);
}

int main(void)
{
	int x = INT_MIN;
	int y = INT_MAX;
	int m = 3;
	int n = -3;
	
	assert(mul3div4(x) == 3 * x / 4);
	assert(mul3div4(y) == 3 * y / 4);
	assert(mul3div4(m) == 3 * m / 4);
	assert(mul3div4(n) == 3 * n / 4);
	
	return 0;
}