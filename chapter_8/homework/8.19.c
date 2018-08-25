/* homework 8.19 */

#include "../code/csapp.h"

void foo(int n)
{
	int i;
	for (i = 0; i < n; i++)
		Fork();
	printf("hello\n");
	exit(0);
}

int main(void)
{
	foo(3);
	exit(0);
}

/* output: 
hello
hello
hello
hello
hello
hello
hello
hello
*/

// 输出行数为 2^n 