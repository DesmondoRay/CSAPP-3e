/*
 * 对于浮点数 f, 这个函数计算 |f|。如果 f 是 NaN，函数返回f。
 * 测试该函数，对参数 f 可以取的所有 2^32 个值求值，
 * 将结果与你使用机器的浮点运算得到的结果相比较。
 */

#include <stdio.h>
#include <assert.h>
// #include <math.h>  // 提供isnan()函数

typedef unsigned float_bits;
 
/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f)
{
	float_bits exp, frac;
	
	exp = f >> 23 & 0xff;
	frac = f & 0x7fffff;
	
	if (exp == 0xff && frac)
		return f;
	else
		return 0 << 31 | (exp << 23) | frac;
}