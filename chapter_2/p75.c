/* 
	使用
		int signed_high_prod(int x, int y);
	编写
		unsigned unsigned_high_prod(unsigned x, unsigned y);
	该函数计算无符号变量x * y的高w位。
 */

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

int signed_high_prod(int x, int y) 
{
  int64_t mul = (int64_t) x * y;
  return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
	int w = sizeof(int) << 3;
	int x_highest_bit = x >> w - 1;
	int y_highest_bit = y >> w - 1;
	return signed_high_prod(x, y) + (-y_highest_bit & x) + (-x_highest_bit & y);
}

unsigned anthoer_unsigned_high_prod(unsigned x, unsigned y)
{
	uint64_t mul = (uint64_t) x * y;
	return mul >> 32;
}

int main(void)
{
	unsigned x = 0x12345678;
	unsigned y = 0xFFFFFFFF;
	
	assert(unsigned_high_prod(x, y) == anthoer_unsigned_high_prod(x, y));
	
	return 0;
}