/*
 * 对于浮点数 f, 这个函数计算 -f。如果 f 是 NaN，函数返回f。
 * 测试该函数，对参数 f 可以取的所有 2^32 个值求值，
 * 将结果与你使用机器的浮点运算得到的结果相比较。
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>  // 提供isnan()函数

typedef unsigned float_bits;
 
/* Compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f)
{
	float_bits sign, exp, frac;
	
	sign = f >> 31;
	exp = f >> 23 & 0xff;
	frac = f & 0x7fffff;
	
	if (exp == 0xff && frac)
		return f;
	else
		return (~sign << 31) | (exp << 23) | frac;
}

float u2f(unsigned x)
{
	return *(float *) &x;
}

unsigned f2u(float f)
{
	return *(unsigned *) &f;
}

/* test driver */
int main(void)
{
        float f = -0.0;
        unsigned uf = f2u(f);
		assert(-f == u2f(float_negate(uf)));

        f = 0.0;
        uf = f2u(f);
        assert(-f == u2f(float_negate(uf)));

        f = 1.0;
        uf = f2u(f);
        assert(-f == u2f(float_negate(uf)));

        f = -1.0;
        uf = f2u(f);
        assert(-f == u2f(float_negate(uf)));

        f = u2f(0x7F800000);    /* +oo */
        uf = f2u(f);
        assert(-f == u2f(float_negate(uf)));

        f = u2f(0xFF800000);    /* -oo */
        uf = f2u(f);
        assert(-f == u2f(float_negate(uf)));

        f = u2f(0x7F800001);    /* NaN */
        uf = f2u(f);
		assert(isnan(f) && isnan(u2f(float_negate(uf))));

        return 0;
}