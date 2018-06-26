/*
	编写一个过程int_size_is_32(),当一个int是32位的机器上运行时，该程序产生1，
	而其他情况则产生0.
	不允许使用sizeof运算符。
*/

#include <stdio.h>
#include <assert.h>

int int_size_is_32()
{
	int set_msb = 1 << 31;
	int beyond_msb = set_msb << 1;
	
	return set_msb && !beyond_msb;
}

int int_size_is_16()
{
	int set_msb = 1 << 15;
	int beyond_msb = set_msb << 1;
	int big_than_16 = (beyond_msb == (set_msb + set_msb));
	
	return set_msb && (!beyond_msb || big_than_16);
}

int main(void)
{
	assert(int_size_is_32());
	assert(int_size_is_16());
	
	return 0;
}

