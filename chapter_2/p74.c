/* 
	Determine whether arguments can be subtracted without overflow.
	如果计算x-y不溢出，则返回1。
 */

// 与p73.c一起编译
 
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int asturating_add(int x, int y);

int tsub_ok(int x, int y)
{
	int temp = asturating_add(x, -y);
	return temp != INT_MIN && temp != INT_MAX;
}

int main(void)
{
	int x = INT_MIN;
	int y = INT_MAX;
	
	assert(tsub_ok(x, 1) == 0);
	assert(tsub_ok(x, -1));
	
	assert(tsub_ok(y, 1));
	assert(tsub_ok(y, -1) == 0);
	
	printf("ok\n");
	return 0;
}