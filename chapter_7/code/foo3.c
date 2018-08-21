#include <stdio.h>

int x = 15213;

void f();

int main(void) 
{
	//f();
	printf("x = %d\n", x);
	return 0;
}

int x;

void f()
{
	x = 1222;
}