/*
 * Divide by power of 2. Assume 0 <= k < w-1.
 * 对于整数除法，结果应该是向零舍入。而对于右移运算，结果是向下舍入。
 * 对于 x >= 0 的情况，简单的右移运算的结果也是整数除法的结果。而对于 x < 0 的情
 * 况，因为结果是向下舍入的，而我们需要的是向上舍入的结果。这样子，当 x < 0 时，
 * 我们为 x 加上一个偏置值 (1<<k)-1 就可以使右移的结果向上舍入了。
 */

#include <stdio.h>
#include <limits.h>
#include <assert.h>

int divide_power2(int x, int k)
{
	int sign = (x & INT_MIN) == INT_MIN;
	int mask = (1 << k) - 1;
	int bias = -sign & mask;
	
	return (x + bias) >> k;
}

/*
int main(void)
{
	int x = 0x80000007;
	
	assert(divide_power2(x, 1) == x / 2);
	assert(divide_power2(x, 2) == x / 4);
	
	return 0;
}
*/