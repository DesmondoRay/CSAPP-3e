/*
	编写过程is_little_endian，当在小端法机器上编译和运行时返回1，
	在大端法机器上编译运行时则返回0。
	这个过程应该可以运行在任何机器上，无论机器的字长是多少。
*/

#include <stdio.h>

/*
int is_little_endian(void);

int main(void)
{
	printf("%d\n", is_little_endian());
	return 0;
}
*/

int is_little_endian(void)
{
	int n = 1;
	int *p = &n;
	int *v = (void *) p;
	
	if (*v == 0x01)
		return 1;
	else
		return 0;
}