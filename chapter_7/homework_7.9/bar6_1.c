/* bar6_1.c */
#include <stdio.h>

char main;

void p2()
{
	printf("0x%x\n", *(&main+1));
}