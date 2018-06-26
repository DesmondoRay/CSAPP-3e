/*
 * 对于浮点数 f, 这个函数计算 0.5 * f。如果 f 是 NaN，函数返回f。
 * 测试该函数，对参数 f 可以取的所有 2^32 个值求值，
 * 将结果与你使用机器的浮点运算得到的结果相比较。
 */

#include <stdio.h>
#include <assert.h>

typedef unsigned float_bits;

/* Compute 0.5*f. If f is NaN, then return f. */
float_bits float_half(float_bits f)
{
	float_bits sign, exp, frac, rest;
	
	sign = f >> 31;
	exp = f >> 23 & 0xff;
	frac = f & 0x7fffff;
	rest = f & 0x7FFFFFFF;
	
	if (exp == 0xff)
		return f;
	
	/* 向偶数舍入
	 * round to even, we care about last 2 bits of frac
	 *
	 * 00 => 0 just >>1
	 * 01 => 0 (round to even) just >>1
	 * 10 => 1 just >>1
	 * 11 => 1 + 1 (round to even) just >>1 and plus 1
	 */
	int addition = (frac & 0x3) == 0x3;

	if (exp == 0) {
		/* Denormalized */
		frac >>= 1;
		frac += addition;
	} else if (exp == 1) {
		/* Normalized to denormalized */
		rest >>= 1;
		rest += addition;
		exp = rest >> 23 & 0xFF;
		frac = rest & 0x7FFFFF;
	} else {
		/* Normalized */
		exp -= 1;
	}

	return (~sign << 31) | (exp << 23) | frac;
}