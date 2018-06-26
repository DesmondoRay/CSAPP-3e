/*
	写一个C表达式，在下列描述的条件下产生1，而在其他情况下得到0。
	假设x是int类型。
		A. x的任何位都等于1
		B. x的任何位都等于0
		C. x的最低有效字节中的位都等于1
		D. x的最高有效字节中的位都等于0
*/

#include <stdio.h>

int expression(int x);
int xor(unsigned int a, unsigned int b);

int main(void)
{
	printf("0xffffffff, %d\n", expression(0xffffffff));  // 情况A
	printf("0x00000000, %d\n", expression(0x00000000));  // 情况B
	printf("0x0000000f, %d\n", expression(0x0000000f));  // 情况C
	printf("0x0fffffff, %d\n", expression(0x0fffffff));  // 情况D
	printf("0x0f0f0f0f, %d\n", expression(0x0f0f0f0f));  // 情况C D
	printf("0xfffffff0, %d\n", expression(0xfffffff0));  // 返回0
	return 0;
}

int expression(int x)
{
	int result1, result2, result3, result4;
	unsigned int mask1 = 0xffffffff, mask3 = 0xf, mask4 = 0xf0000000;
	
	result1 = !(xor(x, mask1));
	result2 = !(xor(x, ~mask1));
	result3 = !(xor((x & mask3), mask3));
	result4 = !(xor((x & mask4), 0x0));
	// printf("%d %d %d %d\n", result1, result2, result3, result4);
	
	return result1 || result2 || result3 || result4;
}

int xor(unsigned int a, unsigned int b)
{
	return ((a & ~b) | (~a & b));
}