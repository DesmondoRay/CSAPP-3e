/*
	编写一个函数int_shifts_are_arithmetic(),在对int类型的数使用
	算术右移的机器上运行这个函数生成1，而其他情况下生成0。
*/

#include <stdio.h>

int int_shifts_are_arithmetic();

int main(void)
{
	printf("%d\n", int_shifts_are_arithmetic());
	return 0;
}

int int_shifts_are_arithmetic()
{
	int n = -1;
	int shifts = (n>>2);
	
	// printf("%#x, %#x\n", n, shifts);
	
	return shifts == n;
}