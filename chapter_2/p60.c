/*
	假设将一个w位的字中的字节从0(最低位)到w/8 - 1(最高位)编号。
	编写c函数
		unsigned replace_byte(unsigned x, int i, unsigned char b);
	以下为示例：
		replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
		replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB
*/

// 与 p58.c 一起编译

#include <stdio.h>

/*
unsigned replace_byte(unsigned x, int i, unsigned char b);
int is_little_endian(void);

int main(void)
{
	printf("%#x\n", replace_byte(0x12345678, 2, 0xAB));
	printf("%#x\n", replace_byte(0x12345678, 0, 0xAB));
	
	return 0;
}
*/

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	unsigned int *p = &x;
	unsigned char *v = (unsigned char *) p;
	
	if (is_little_endian())
		v[i] = b;
	else 
		v[sizeof(unsigned) - i - 1] = b;
	
	return *p;
}