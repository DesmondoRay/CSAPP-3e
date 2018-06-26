/*
 * 对于浮点数 f, 这个函数计算 (int) f。如果 f 是 NaN，函数应该向零舍入。
 * 如果 f 不能用整数表示（例如：超出表示范围，或这NaN），返回0x80000000。
 * 测试该函数，对参数 f 可以取的所有 2^32 个值求值，
 * 将结果与你使用机器的浮点运算得到的结果相比较。
 */

#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

typedef unsigned float_bits;

/* 
 * Compute (int) f. 
 * If conversion causes overflow or f is NaN, return 0x80000000.
 */
int float_f2i(float_bits f)
{
	float_bits sign, exp, frac;
	float_bits M, E, bias;
	
	sign = f >> 31;
	exp = f >> 23 & 0xff;
	frac = f & 0x7fffff;
	bias = 0x7f;
	
	if (exp>= 31 + bias || exp == 0xff)  // overflow or f is NaN
		return 0x80000000;
	else if (exp < bias)  // 结果小于1
		return 0;
	else
	{
		M = frac | 0x800000;
		E = exp - bias;
		if (E > 23)
			return pow(-1, sign) * (M << (E - 23));
		else
			return pow(-1, sign) * (M >> (23 - E));
	}
}

int main(void)
{
	for (unsigned long i = 0; i < 0xff000000; i = i + 0x1000000){
		float f_i = *(float *) &i;
		printf("%#x %d %d\n", i, float_f2i(i), (int) f_i);
		assert(float_f2i(i) == (int) f_i);
	}
	
	return 0;
}