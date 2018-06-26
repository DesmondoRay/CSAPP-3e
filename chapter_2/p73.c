/* 
	Addition that saturates to TMin or TMax. 
	同正常的补码加法溢出的方式不同，当正溢出时，饱和加法返回TMax， 
	负溢出时，返回TMin。
 */


#include <stdio.h>
#include <assert.h>
#include <limits.h>

int asturating_add(int x, int y)
{
	int sum = x + y;
	int w = sizeof(int) << 3;
	
	// x, y, sum的最高位
	int h_x = (unsigned) x >> (w - 1);
	int h_y = (unsigned) y >> (w - 1);
	int h_sum = (unsigned) sum >> (w - 1);
	
	// neg = 1 表示负溢出， pos = 1 表示正溢出
	int neg = h_x && h_y && !h_sum;
	int pos = !h_x && !h_y && h_sum;
	
	return (-neg & INT_MIN) + (-pos & INT_MAX);
}

/*
int main(void)
{
	int x = INT_MAX;
	int y = INT_MIN;
	
	assert(asturating_add(x, x) == INT_MAX);
	assert(asturating_add(y, y) == INT_MIN);
	
	return 0;
}
*/
