/*
 * p90.c
 * 编写一个函数来计算 2^x 的浮点表示，结果用IEEE单精度(float)表示。
 * 当 x 太小时，返回0.0，当 x 太大时放回 +oo。
 * 函数 u2f 返回的浮点值与它的无符号参数有相同的位表示。
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>

float u2f(unsigned u)
{
	return *(float *) &u;
}

float fpwr2(int x)
{
	/* Result exponent and fraction */
	unsigned exp, frac;
	unsigned u;
	
	if (x < -126 - 23)
	{
		/* Too small. Return 0.0 */
		exp = 0;
		frac = 0;
	}
	else if (x < -126)
	{
		/* Denormalized result */
		exp = 0;
		frac = 1 << (23 + x + 126);
	}
	else if (x < 128)
	{
		/* Normalized result. */
		exp = x + 127;
		frac = 0;
	}
	else
	{
		/* Too big. Return +oo */
		exp = 255;
		frac = 0;
	}
	
	/* Pack exp and frac into 32 bits */
	u = exp << 23 | frac;
	
	return u2f(u);
}

int main(void) 
{
  assert(fpwr2(-126 - 24) == powf(2, -126 - 24));
  assert(fpwr2(-126 - 24) == 0.0);
  assert(fpwr2(-126 - 23) == powf(2, -126 - 23));
  assert(fpwr2(127) == powf(2, 127));
  assert(fpwr2(10000) == powf(2,10000));
  
  return 0;
}