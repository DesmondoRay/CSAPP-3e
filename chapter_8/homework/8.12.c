/* homework 8.12 */

#include "../code/csapp.h"

void doit()
{
	Fork();
	Fork();
	printf("hello\n");
	return;
}

int main()
{
	doit();
	printf("hello\n");
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