/*
	生成一段代码，将整数变量 x 乘以不同的常数因子K。
	为了提高效率，只使用 +、- 和 << 运算符。
	对于下列K的值，写出执行乘法运算的C表达式，每个表达式中最多使用3个运算符。
		A. K = 17
		B. K = -7
		C. K = 60
		D. K = -112
 */
 
#include <stdio.h>
#include <assert.h>

int main(void)
{
	int x = 5;
	int k1 = 17, k2 = -7, k3 = 60, k4 = -112;
	int exp1, exp2, exp3, exp4;
	
	exp1 = (x << 4) + x;
	exp2 = x - (x << 3);
	exp3 = (x << 6) - (x << 2);
	exp4 = (x << 4) - (x << 7);
	
	assert(exp1 == x * k1);
	assert(exp2 == x * k2);
	assert(exp3 == x * k3);
	assert(exp4 == x * k4);
	
	return 0;
}