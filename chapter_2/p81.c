/*
 * 编写 C 表达式产生如下位模式，其中 a^k 表示符号 a 重复 k 次。假设一个 w 位的
 * 数据类型。你的代码可以包含对参数 k 和 j 的引用，它们分别表示 k 和 j 的值，但
 * 是不能使用表示 w 的参数。
 *
 * A. 1^(w-k)0^k
 * B. 0^(w-k-j)1^k0^j
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int exp_A(int k)
{
	int x = -1;
	
	return x << k;
}

int exp_B(int k, int j)
{
	int x = -1;
	
	int temp1 = x << (k + j);
	int temp2 = x << j;
	
	return ~(temp1 | ~temp2);
}

int main(void)
{
	char binary[(sizeof(int) << 3) + 1];
	
	itoa(exp_A(4), binary, 2);
	printf("%s\n", binary);
	
	itoa(exp_B(4, 3), binary, 2);
	printf("%s\n", binary);
	
	return 0;
}