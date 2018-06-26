/*
	函数srl用算术右移来完成逻辑右移；
	函数sra用逻辑右移来完成算术右移。
*/

#include <stdio.h>

unsigned srl(unsigned x, int k);
unsigned sra(int x, int k);


int main(void)
{
	int x = 0x12345678;
	int y = -1;
	printf("%#x\n", srl((unsigned) x, 8));
	printf("%#x\n", sra(x, 8));
	printf("%#x\n", srl((unsigned) y, 8));
	printf("%#x\n", sra(y, 8));
	return 0;
}

unsigned srl(unsigned x, int k)
{
	/* perform shift arithmetically */
	unsigned xsra = (int) x >> k;
	
	int mask = -1;
	
	mask = mask << ((sizeof(int) << 3) - k);
	return ~mask & xsra;
}

unsigned sra(int x, int k)
{
	/* perform shift logically */
	int xsrl = (unsigned) x >> k;
	
	unsigned mask = 1;
	int *p = &x;
	char *temp = (void *) p;
	
	// 判断x的最高位是否为1
	int h = (((mask << 7) & temp[sizeof(int) - 1]) == 128);
	
	h = (-h) << ((sizeof(int) << 3) - k);
	return h | xsrl;
}