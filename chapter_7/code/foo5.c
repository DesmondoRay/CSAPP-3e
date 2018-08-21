#include <stdio.h>

void f(void);

int x = 15214;
int y = 15212;


int main()
{
	f();
	printf("x = %#x, y = %#x \n", x ,y);
	return 0;
}