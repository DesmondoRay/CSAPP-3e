/* homewrok 8.11 */

#include "../code/csapp.h"

int main()
{
	int i;
	for (i = 0; i < 2; i++)
		Fork();
	printf("hello\n");
	exit(0);
}

/* output:
hello
hello
hello
hello
*/