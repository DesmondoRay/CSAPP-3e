/* homework 8.14 */

#include "../code/csapp.h"

void doit()
{
	if (Fork() == 0) {
		Fork();
		printf("hello\n");
		exit(0);
	}
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
*/