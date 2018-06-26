/*
 * 对于浮点数 f, 这个函数计算 2.0 * f。如果 f 是 NaN，函数返回f。
 * 测试该函数，对参数 f 可以取的所有 2^32 个值求值，
 * 将结果与你使用机器的浮点运算得到的结果相比较。
 */

#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

/* Compute 2*f. If f is NaN, then return f. */
float_bits float_twice(float_bits f)
{
	float_bits sign, exp, frac;
	
	sign = f >> 31;
	exp = f >> 23 & 0xff;
	frac = f & 0x7fffff;
	
	if (exp == 0xff && frac)
		return f;
	
	if (exp == 0)  // 非规格化的值
		frac <<= 1;
	else if (exp == 0xff - 1)  //无穷大时
	{
		frac = 0;
		exp = 0xff;
	}
	else
		exp += 1;
	
	return (~sign << 31) | (exp << 23) | frac;
}