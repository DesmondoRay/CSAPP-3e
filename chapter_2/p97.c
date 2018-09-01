/*
 * 对于整数i，这个函数计算(float) i的位级表示。
 * 测试该函数，对参数 f 可以取的所有 2^32 个值求值，
 * 将结果与你使用机器的浮点运算得到的结果相比较。
 */

// 未考虑舍入问题，正确答案见 p97_correct.c

#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>

typedef unsigned float_bits;

/* 
 * Compute (float) f. 
 */
float_bits float_i2f(int i)
{
	float_bits sign, exp, frac, bias;
	float_bits abs_i, mask, shift, temp;
	int bit;
	
	bias = 0x7f;
	
	if (i < 0){
		sign = 1;
		abs_i = -i;
	} else {
		sign = 0;
		abs_i = i;
	}
	
	temp = abs_i;
	// 找出i不为0的最高位
	for (bit = 0; bit <= 32; bit++) {
		temp >>= 1;
		if (temp == 0) {
			exp = bit + bias;
			mask = ~(0x1 << bit);
			break;
		}
	}
	
	// printf("i = %d, abs_i = %u, bit = %d\n", i, abs_i, bit);
	// printf("%u\n", mask & abs_i);
	if (i == 0) {
		return 0;
	} if (bit < 23){
		shift = 23 - bit;
		return sign << 31 | exp << 23 | (abs_i & mask) << shift;
	} else {
		shift = bit - 23;
		return sign << 31 | exp << 23 | (abs_i & mask) >> shift;
	}
}

int main(void)
{
	for (int64_t i = INT_MIN; i <= INT_MAX; i = i + 0x1000000)
	{
		unsigned f_i = float_i2f((int) i);
		// printf("%f %f\n", (float) i, *(float *) &f_i);
		assert((float) i == *(float *) &f_i);
	}
	
	return 0;
}