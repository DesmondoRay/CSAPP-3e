/*
	编写一个C表达式，生成一个字，由x的最低有效字节和y中剩下的字节组成。
	对于运算数x = 0x89ABCDEF 和 y = 0x76543210，就得到0x765432EF.
*/

#include <stdio.h>

int procedure(int x, int y);

int main(void)
{
	printf("%#x\n", procedure(0x89ABCDEF, 0x76543210));
	return 0;
}

int procedure(int x, int y)
{
	int mask = 0xFF;
	
	return (~mask & y) | (mask & x);
}